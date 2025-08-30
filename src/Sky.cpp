#include <hgl/graph/Sky.h>
#include <hgl/type/DateTime.h>
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

        // Convert civil date to days since epoch 1970-01-01 using algorithm from Howard Hinnant
        inline int days_from_civil(int y, unsigned m, unsigned d)
        {
            y -= m <= 2;
            const int era = (y >= 0 ? y : y-399) / 400;
            const unsigned yoe = static_cast<unsigned>(y - era * 400);      // [0, 399]
            const unsigned doy = (153*(m + (m > 2 ? -3 : 9)) + 2)/5 + d - 1;
            const unsigned doe = yoe*365 + yoe/4 - yoe/100 + doy;
            return era * 146097 + static_cast<int>(doe) - 719468;
        }

        inline void civil_from_days(int z, int &y, int &m, int &d)
        {
            z += 719468;
            const int era = (z >= 0 ? z : z - 146096) / 146097;
            const unsigned doe = static_cast<unsigned>(z - era * 146097);          // [0, 146096]
            const unsigned yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365; // [0, 399]
            y = static_cast<int>(yoe) + era * 400;
            const unsigned doy = doe - (365*yoe + yoe/4 - yoe/100);
            const unsigned mp = (5*doy + 2)/153;
            d = static_cast<int>(doy - (153*mp+2)/5 + 1);
            m = static_cast<int>(mp + (mp < 10 ? 3 : -9));
            y += (m <= 2);
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

        if (is_day)
        {
            const float cos_e = std::cos(elevation_rad);
            const float sin_e = std::sin(elevation_rad);

            // 太阳方向 (Z-up): horizontal components on X/Y plane, Z is elevation
            const float hx = std::sin(azimuth_rad) * cos_e;
            const float hy = std::cos(azimuth_rad) * cos_e;
            const float hz = sin_e;
            // sun_direction: 从太阳指向场景，需归一化；负号确保方向从光源指向场景
            this->sun_direction = Vector4f(-hx, -hy, -hz, 0.0f);

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
        }
        else
        {
            // 夜晚
            this->sun_intensity = 0.0f;

            // 简化的月亮方位（太阳对面）
            const float moon_azimuth = azimuth_rad + PI;
            const float moon_elevation = std::abs(elevation_rad) * 0.8f;
            const float cos_e = std::cos(moon_elevation);
            const float sin_e = std::sin(moon_elevation);

            // moon direction (Z-up)
            const float mhx = std::sin(moon_azimuth) * cos_e;
            const float mhy = std::cos(moon_azimuth) * cos_e;
            const float mhz = sin_e;
            this->sun_direction = Vector4f(-mhx, -mhy, -mhz, 0.0f);

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
        // 将本地时间转换为 UTC，再以 UTC 时间调用 SetByTimeOfDay
        // 原因：hour_angle(...) 假定传入的 hour 是 UTC（或标准时间），否则需要减去时区偏移。
        std::tm tmp = local_tm; // mktime 会规范化 tm ，拷贝以免修改调用者数据

        // mktime 将 tmp 视为本地时间并返回 time_t
        std::time_t tt = mktime(&tmp);
        if (tt == -1)
        {
            // 退回到原逻辑（不可用 time_t 时）
            const float hour   = static_cast<float>(local_tm.tm_hour);
            const float minute = static_cast<float>(local_tm.tm_min);
            const float second = static_cast<float>(local_tm.tm_sec);

            this->SetDate(1900 + local_tm.tm_year, 1 + local_tm.tm_mon, local_tm.tm_mday);
            this->SetByTimeOfDay(hour, minute, second);
            return;
        }

        std::tm gtm{};
    #if defined(_WIN32)
        gmtime_s(&gtm, &tt);
    #else
        gmtime_r(&tt, &gtm);
    #endif

        const float utc_hour   = static_cast<float>(gtm.tm_hour);
        const float utc_minute = static_cast<float>(gtm.tm_min);
        const float utc_second = static_cast<float>(gtm.tm_sec);

        // 保持日期由调用者控制（仍使用 local_tm 的年月日）
        this->SetDate(1900 + local_tm.tm_year, 1 + local_tm.tm_mon, local_tm.tm_mday);
        // 传入 UTC 时间给 SetByTimeOfDay，使 hour_angle 计算正确
        this->SetByTimeOfDay(utc_hour, utc_minute, utc_second);
    }

    void SkyInfo::SetByLocalTime(float hour, float minute, float second)
    {
        // Use timezone_offset_minutes in SkyInfo if set; default 0
        const int tz_minutes = this->timezone_offset_minutes;

        // total seconds of local time
        int total = int(std::round(hour * 3600.0f + minute * 60.0f + second));
        // subtract timezone offset to get UTC seconds
        total -= tz_minutes * 60;

        int day_offset = 0;
        const int day_seconds = 24 * 3600;
        while (total < 0) { total += day_seconds; --day_offset; }
        while (total >= day_seconds) { total -= day_seconds; ++day_offset; }

        int utc_h = total / 3600;
        int utc_m = (total % 3600) / 60;
        int utc_s = total % 60;

        if (day_offset != 0)
        {
            // shift stored date by day_offset using civil date algorithms
            int z = days_from_civil(this->year, static_cast<unsigned>(this->month), static_cast<unsigned>(this->day));
            z += day_offset;
            int ny, nm, nd;
            civil_from_days(z, ny, nm, nd);
            this->SetDate(ny, nm, nd);
        }

        this->SetByTimeOfDay(static_cast<float>(utc_h), static_cast<float>(utc_m), static_cast<float>(utc_s));
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
