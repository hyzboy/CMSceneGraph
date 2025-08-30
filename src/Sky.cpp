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
    } // anon

    void SkyInfo::SetByTimeOfDay(float hour, float minute, float second)
    {
        const float h = frac_day(hour, minute, second);

        // 昼夜与仰角：6:00->18:00 之间可见，正午（12:00）仰角最大
        const float a = (h - 6.0f) / 12.0f * PI;                   // 昼间映射到 [0, π]
        const bool  is_day = (h >= 6.0f && h <= 18.0f);

        const float elev_norm     = is_day ? std::sin(std::clamp(a, 0.0f, PI)) : 0.0f; // 0..1..0
        const float max_elev_rad  = std::max(0.0f, this->max_elevation_deg) * DEG2RAD;
        const float elev_rad      = elev_norm * max_elev_rad;

        // 方位角：正午指向 sun_path_azimuth_deg，随时间从东到西移动（±90°）
        const float azimuth_noon  = this->sun_path_azimuth_deg * DEG2RAD;
        const float azimuth_rad   = azimuth_noon - (h - 12.0f) / 12.0f * (PI);

        const float cos_e = std::cos(elev_rad);
        const float sin_e = std::sin(elev_rad);

        // 地平面方向（右手系，Y 向上）
        const float gx = std::cos(azimuth_rad);
        const float gz = std::sin(azimuth_rad);

        // 从太阳指向场景的方向
        const float dx = gx * cos_e;
        const float dy = sin_e;
        const float dz = gz * cos_e;

        const float len = std::max(1e-6f, std::sqrt(dx*dx + dy*dy + dz*dz));
        this->sun_direction = Vector4f(dx/len, dy/len, dz/len, 0.0f);

        // 颜色：仰角越低越偏暖；中午接近白色
        const Color4f day_color  (1.0f, 0.95f, 0.90f, 1.0f);
        const Color4f dusk_color (1.0f, 0.60f, 0.30f, 1.0f);

        const float elev01 = (max_elev_rad > 1e-6f) ? (elev_rad / max_elev_rad) : 0.0f; // 0..1
        const float warm   = smoothstep(0.0f, 0.6f, 1.0f - elev01); // 仰角越低越暖

        this->sun_color     = Lerp(day_color, dusk_color, warm);
        this->sun_intensity = is_day ? std::pow(elev01, 1.25f) : 0.0f;
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
