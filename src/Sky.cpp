#include <hgl/graph/Sky.h>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <cmath>

namespace hgl::graph
{
    namespace
    {
        constexpr float PI      = 3.14159265358979323846f;
        constexpr float DEG2RAD = PI / 180.0f;

        inline float clamp01(float v) { return std::clamp(v, 0.0f, 1.0f); }

        inline float smoothstep(float e0, float e1, float x)
        {
            float t = clamp01((x - e0) / (e1 - e0));
            return t * t * (3.0f - 2.0f * t);
        }

        inline float frac_day(float h, float m, float s)
        {
            float th = h + m / 60.0f + s / 3600.0f;
            th = std::fmod(th, 24.0f);
            if (th < 0.0f) th += 24.0f;
            return th;
        }

        inline Color4f Lerp(const Color4f &a, const Color4f &b, float t)
        {
            return Color4f(
                a.r + (b.r - a.r) * t,
                a.g + (b.g - a.g) * t,
                a.b + (b.b - a.b) * t,
                a.a + (b.a - a.a) * t
            );
        }

        // 计算太阳赤纬角（简化模型）
        inline float solar_declination(int day_of_year)
        {
            return 23.45f * DEG2RAD * std::sin(2.0f * PI * (284 + day_of_year) / 365.0f);
        }

        // 计算时角
        inline float hour_angle(float hour, float longitude_deg)
        {
            float solar_time = hour + longitude_deg / 15.0f; // 经度转换为时间偏移
            return (solar_time - 12.0f) * 15.0f * DEG2RAD;  // 小时角（弧度）
        }

        // 计算太阳高度角
        inline float solar_elevation(float latitude_rad, float declination_rad, float hour_angle_rad)
        {
            return std::asin(std::sin(latitude_rad) * std::sin(declination_rad) + 
                            std::cos(latitude_rad) * std::cos(declination_rad) * std::cos(hour_angle_rad));
        }

        // 计算太阳方位角
        inline float solar_azimuth(float latitude_rad, float declination_rad, float hour_angle_rad, float elevation_rad)
        {
            float cos_azimuth = (std::sin(declination_rad) * std::cos(latitude_rad) - 
                                std::cos(declination_rad) * std::sin(latitude_rad) * std::cos(hour_angle_rad)) / 
                                std::cos(elevation_rad);
            
            float azimuth = std::acos(std::clamp(cos_azimuth, -1.0f, 1.0f));
            
            // 调整方位角的象限
            if (hour_angle_rad > 0) {
                azimuth = 2.0f * PI - azimuth;
            }
            
            return azimuth;
        }
    } // anon

    void SkyInfo::SetByTimeOfDay(float hour, float minute, float second, 
                                float latitude_deg, float longitude_deg)
    {
        // 存储传入的经纬度
        this->latitude_deg = latitude_deg;
        this->longitude_deg = longitude_deg;

        const float h = frac_day(hour, minute, second);
        const float latitude_rad = latitude_deg * DEG2RAD;
        
        // 简化：假设一年中的第100天（4月10日左右）用于赤纬角计算
        const int day_of_year = 100;
        const float declination = solar_declination(day_of_year);
        const float hour_angle_rad = hour_angle(h, longitude_deg);
        
        // 计算太阳高度角和方位角
        const float elevation_rad = solar_elevation(latitude_rad, declination, hour_angle_rad);
        const float azimuth_rad = solar_azimuth(latitude_rad, declination, hour_angle_rad, elevation_rad);
        
        const bool is_day = elevation_rad > 0.0f;
        
        if (is_day) {
            // 太阳在地平线上
            const float cos_e = std::cos(elevation_rad);
            const float sin_e = std::sin(elevation_rad);
            
            // 计算太阳方向向量
            const float dx = std::sin(azimuth_rad) * cos_e;
            const float dy = sin_e;
            const float dz = std::cos(azimuth_rad) * cos_e;
            
            this->sun_direction = Vector4f(-dx, dy, -dz, 0.0f); // 从太阳指向场景
            
            // 根据高度角计算颜色和强度
            const Color4f day_color(1.0f, 0.95f, 0.90f, 1.0f);
            const Color4f dusk_color(1.0f, 0.60f, 0.30f, 1.0f);
            
            const float elev_normalized = elevation_rad / (PI * 0.5f); // 归一化到 [0,1]
            const float warm = smoothstep(0.0f, 0.3f, 1.0f - elev_normalized);
            
            this->sun_color = Lerp(day_color, dusk_color, warm);
            this->sun_intensity = std::pow(elev_normalized, 1.25f);
            
            // 月亮在白天时强度为0
            this->moon_intensity = 0.0f;
        } else {
            // 夜晚：太阳在地平线下
            this->sun_intensity = 0.0f;
            
            // 简化的月亮计算：假设月亮在太阳对面
            const float moon_azimuth = azimuth_rad + PI;
            const float moon_elevation = std::abs(elevation_rad) * 0.8f; // 月亮高度角
            
            const float cos_e = std::cos(moon_elevation);
            const float sin_e = std::sin(moon_elevation);
            
            const float dx = std::sin(moon_azimuth) * cos_e;
            const float dy = sin_e;
            const float dz = std::cos(moon_azimuth) * cos_e;
            
            // 月亮方向存储在sun_direction中（夜晚时）
            this->sun_direction = Vector4f(-dx, dy, -dz, 0.0f);
            
            // 设置月亮颜色和强度
            this->sun_color = this->moon_color;
            this->moon_intensity = 0.3f * std::max(0.0f, sin_e);
        }
        
        // 光晕强度基于太阳/月亮的可见性
        this->halo_intensity = is_day ? this->sun_intensity * 0.5f : this->moon_intensity * 0.3f;
    }

    void SkyInfo::SetByTimeOfDay(float hour, float minute, float second)
    {
        // 使用存储的经纬度调用完整版本
        SetByTimeOfDay(hour, minute, second, this->latitude_deg, this->longitude_deg);
    }

    void SkyInfo::SetByLocalTime(const std::tm &local_tm)
    {
        const float hour   = static_cast<float>(local_tm.tm_hour);
        const float minute = static_cast<float>(local_tm.tm_min);
        const float second = static_cast<float>(local_tm.tm_sec);

        this->SetByTimeOfDay(hour, minute, second);
    }

    void SkyInfo::SetBySystemClock()
    {
        using clock = std::chrono::system_clock;
        const auto now = clock::now();
        const std::time_t tt = clock::to_time_t(now);

        std::tm lt{};
        #if defined(_WIN32)
            localtime_s(&lt, &tt);
        #else
            localtime_r(&tt, &lt);
        #endif

        this->SetByLocalTime(lt);
    }
} // namespace hgl::graph
