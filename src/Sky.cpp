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

        inline Color4f Scale(const Color4f &c, float s)
        {
            return Color4f(c.r * s, c.g * s, c.b * s, c.a * s);
        }

        inline int DayOfYear(int year, int month, int day)
        {
            static const int mdays_norm[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
            auto is_leap = [](int y){ return (y%4==0 && y%100!=0) || (y%400==0); };
            int doy = 0;
            for (int m=1; m<month; ++m)
            {
                if (m==2 && is_leap(year)) doy += 29; else doy += mdays_norm[m-1];
            }
            doy += day;
            return doy;
        }

        inline float solar_declination_from_doy(int day_of_year)
        {
            return 23.45f * DEG2RAD * std::sin(2.0f * PI * (284 + day_of_year) / 365.0f);
        }

        inline float hour_angle(float hour, float longitude_deg)
        {
            float solar_time = hour + longitude_deg / 15.0f;
            return (solar_time - 12.0f) * 15.0f * DEG2RAD;
        }

        inline float solar_elevation(float latitude_rad, float declination_rad, float hour_angle_rad)
        {
            return std::asin(std::sin(latitude_rad) * std::sin(declination_rad) + 
                            std::cos(latitude_rad) * std::cos(declination_rad) * std::cos(hour_angle_rad));
        }

        inline float solar_azimuth(float latitude_rad, float declination_rad, float hour_angle_rad, float elevation_rad)
        {
            float denom = std::max(1e-6f, std::cos(elevation_rad));
            float cos_azimuth = (std::sin(declination_rad) * std::cos(latitude_rad) - 
                                std::cos(declination_rad) * std::sin(latitude_rad) * std::cos(hour_angle_rad)) / denom;
            float azimuth = std::acos(std::clamp(cos_azimuth, -1.0f, 1.0f));
            if (hour_angle_rad > 0) azimuth = 2.0f * PI - azimuth;
            return azimuth;
        }

        inline float Luminance(const Color4f &c)
        {
            return 0.2126f*c.r + 0.7152f*c.g + 0.0722f*c.b;
        }
    } // anon

    // ---- EnvironmentProfile implementation ----
    Color4f EnvironmentProfile::SkyTint() const
    {
        // 典型色：
        const Color4f sea_col       (0.35f, 0.55f, 0.95f, 1.0f);
        const Color4f shore_col     (0.55f, 0.70f, 0.95f, 1.0f);
        const Color4f desert_col    (0.95f, 0.70f, 0.30f, 1.0f);
        const Color4f desert_sea_col(0.75f, 0.70f, 0.55f, 1.0f);
        const Color4f forest_col    (0.40f, 0.65f, 0.60f, 1.0f);
        const Color4f city_col      (0.45f, 0.55f, 0.65f, 1.0f);
        const Color4f snow_col      (0.85f, 0.90f, 1.00f, 1.0f); // 亮、偏冷
        const Color4f grassland_col (0.50f, 0.75f, 0.60f, 1.0f); // 绿中偏蓝
        const Color4f hills_col     (0.55f, 0.70f, 0.70f, 1.0f); // 柔和灰青
        const Color4f mountain_col  (0.60f, 0.75f, 0.85f, 1.0f); // 高海拔偏冷

        float wsum = sea + shore + desert + desert_sea + forest + city + snow + grassland + hills + mountain;
        if (wsum <= 1e-6f) return Color4f(0.5f, 0.6f, 1.0f, 1.0f); // 默认
        float inv = 1.0f / wsum;

        Color4f out = Color4f(0.0f);
        out += Scale(sea_col,        sea        * inv);
        out += Scale(shore_col,      shore      * inv);
        out += Scale(desert_col,     desert     * inv);
        out += Scale(desert_sea_col, desert_sea * inv);
        out += Scale(forest_col,     forest     * inv);
        out += Scale(city_col,       city       * inv);
        out += Scale(snow_col,       snow       * inv);
        out += Scale(grassland_col,  grassland  * inv);
        out += Scale(hills_col,      hills      * inv);
        out += Scale(mountain_col,   mountain   * inv);
        return out;
    }

    float EnvironmentProfile::Humidity() const
    {
        // 海/海岸湿度最高，森林次之；雪地、山地较冷但湿度可中等；草原中等；城市中等；沙漠最低
        float wsum = sea + shore + desert + desert_sea + forest + city + snow + grassland + hills + mountain;
        if (wsum <= 1e-6f) return 0.3f;
        float inv = 1.0f / wsum;
        float h = 0.0f;
        h += sea        * inv * 0.90f;
        h += shore      * inv * 0.85f;
        h += forest     * inv * 0.70f;
        h += grassland  * inv * 0.60f;
        h += city       * inv * 0.50f;
        h += mountain   * inv * 0.45f;
        h += hills      * inv * 0.45f;
        h += snow       * inv * 0.55f;
        h += desert_sea * inv * 0.50f;
        h += desert     * inv * 0.10f;
        return clamp01(h);
    }

    float EnvironmentProfile::Aerosol() const
    {
        // 城市/沙漠气溶胶高；草原/丘陵中等；海/雪地/高山较低；森林偏低
        float wsum = sea + shore + desert + desert_sea + forest + city + snow + grassland + hills + mountain;
        if (wsum <= 1e-6f) return 0.2f;
        float inv = 1.0f / wsum;
        float a = 0.0f;
        a += city       * inv * 0.80f;
        a += desert     * inv * 0.65f;
        a += desert_sea * inv * 0.55f;
        a += grassland  * inv * 0.40f;
        a += hills      * inv * 0.40f;
        a += shore      * inv * 0.30f;
        a += forest     * inv * 0.25f;
        a += mountain   * inv * 0.20f;
        a += snow       * inv * 0.15f;
        a += sea        * inv * 0.15f;
        return clamp01(a);
    }

    // ---- SkyInfo implementation ----
    void SkyInfo::SetLocation(float latitude_deg, float longitude_deg)
    {
        this->latitude_deg  = latitude_deg;
        this->longitude_deg = longitude_deg;
    }

    void SkyInfo::SetAltitude(float altitude_m)
    {
        this->altitude_m = altitude_m;
    }

    void SkyInfo::SetDate(int year, int month, int day)
    {
        this->year  = year;
        this->month = month;
        this->day   = day;
    }

    void SkyInfo::SetByTimeOfDay(float hour, float minute, float second)
    {
        const float h = frac_day(hour, minute, second);
        const float latitude_rad = this->latitude_deg * DEG2RAD;

        const int day_of_year = DayOfYear(this->year, this->month, this->day);
        const float declination = solar_declination_from_doy(day_of_year);
        const float hour_angle_rad = hour_angle(h, this->longitude_deg);

        // 计算太阳高度角和方位角
        const float elevation_rad = solar_elevation(latitude_rad, declination, hour_angle_rad);
        const float azimuth_rad = solar_azimuth(latitude_rad, declination, hour_angle_rad, elevation_rad);

        const bool is_day = elevation_rad > 0.0f;

        // 时间/仰角色调
        const Color4f day_sky_tint  (0.45f, 0.60f, 1.00f, 1.0f);
        const Color4f dusk_sky_tint (1.00f, 0.55f, 0.25f, 1.0f);
        const Color4f night_sky_tint(0.08f, 0.10f, 0.18f, 1.0f);

        // elev01 表示太阳仰角归一化，0..1
        const float elev01 = clamp01(elevation_rad / (PI * 0.5f));
        const float warm   = smoothstep(0.0f, 0.35f, 1.0f - elev01); // 仰角越低越暖

        // 环境相关：地表色调、湿度、气溶胶（海拔修正）
        const Color4f env_tint = environment.SkyTint();
        float humidity   = environment.Humidity();
        float aerosol    = environment.Aerosol();

        // 海拔影响：海拔越高，湿度/气溶胶下降，天空更清透、偏冷
        const float alt_km = std::max(0.0f, this->altitude_m) * 0.001f;
        const float humidity_factor = clamp01(1.0f - 0.08f * alt_km);  // 1km ~ -8%
        const float aerosol_factor  = clamp01(1.0f - 0.15f * alt_km);  // 1km ~ -15%
        humidity *= humidity_factor;
        aerosol  *= aerosol_factor;

        if (is_day) {
            const float cos_e = std::cos(elevation_rad);
            const float sin_e = std::sin(elevation_rad);

            // 太阳方向
            const float dx = std::sin(azimuth_rad) * cos_e;
            const float dy = sin_e;
            const float dz = std::cos(azimuth_rad) * cos_e;
            this->sun_direction = Vector4f(-dx, dy, -dz, 0.0f);

            // 太阳颜色/强度
            const Color4f day_color(1.0f, 0.95f, 0.90f, 1.0f);
            const Color4f dusk_color(1.0f, 0.60f, 0.30f, 1.0f);
            this->sun_color     = Lerp(day_color, dusk_color, warm);
            this->sun_intensity = std::pow(elev01, 1.25f);

            // 地平线附近加入地表反照影响
            const float horizon_mix = smoothstep(0.0f, 0.4f, 1.0f - elev01);
            const float ground_factor = clamp01(0.10f + 0.50f * humidity);
            const Color4f time_tint = Lerp(day_sky_tint, dusk_sky_tint, warm);
            // 高海拔轻微偏冷：向 day_sky_tint 再靠一些
            const float high_alt_cool = clamp01(0.05f * alt_km);
            const Color4f time_alt_tint = Lerp(time_tint, day_sky_tint, high_alt_cool);
            this->base_sky_color = Lerp(time_alt_tint, env_tint, horizon_mix * ground_factor);

            // 光晕：海拔高空气稀薄 -> 湿度/气溶胶都低，光晕更小、更清晰
            const float halo_base = this->sun_intensity * (0.35f + 0.45f * humidity + 0.25f * aerosol);
            this->halo_intensity = clamp01(halo_base);

            // 白天月亮忽略
            this->moon_intensity = 0.0f;
        } else {
            // 夜晚
            this->sun_intensity = 0.0f;

            // 简化的月亮方位（太阳对面）
            const float moon_azimuth = azimuth_rad + PI;
            const float moon_elevation = std::abs(elevation_rad) * 0.8f;
            const float cos_e = std::cos(moon_elevation);
            const float sin_e = std::sin(moon_elevation);
            const float dx = std::sin(moon_azimuth) * cos_e;
            const float dy = sin_e;
            const float dz = std::cos(moon_azimuth) * cos_e;
            this->sun_direction = Vector4f(-dx, dy, -dz, 0.0f);

            this->sun_color = this->moon_color;
            // 海拔高夜空更通透，光晕扩散降低（通过湿度/气溶胶修正）
            this->moon_intensity = 0.3f * std::max(0.0f, sin_e) * (1.0f - 0.2f * humidity);

            const Color4f night_sky_tint(0.08f, 0.10f, 0.18f, 1.0f);
            Color4f night_base = night_sky_tint;
            const Color4f env_tint = environment.SkyTint();
            const float env_lum = Luminance(env_tint);
            float night_boost = 0.05f + 0.25f * humidity + 0.10f * clamp01(env_lum);
            night_boost = clamp01(night_boost);
            night_base.r = night_base.r * (1.0f - night_boost) + env_tint.r * 0.2f * night_boost;
            night_base.g = night_base.g * (1.0f - night_boost) + env_tint.g * 0.3f * night_boost;
            night_base.b = night_base.b * (1.0f - night_boost) + env_tint.b * 0.5f * night_boost;
            this->base_sky_color = night_base;

            const float halo_base = this->moon_intensity * (0.25f + 0.50f * humidity + 0.15f * aerosol);
            this->halo_intensity = clamp01(halo_base);
        }
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
        // 默认不覆盖 SkyInfo 中的 year/month/day，如需跟随系统可在外部调用 SetDate
        this->SetByLocalTime(lt);
    }
} // namespace hgl::graph
