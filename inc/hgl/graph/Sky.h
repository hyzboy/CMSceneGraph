#pragma once
#include <ctime>                   // std::tm
#include <hgl/color/Color.h>
#include <hgl/graph/Camera.h>      // 提供 Vector4f（约定 Y 轴向上）

namespace hgl::graph
{
    /**
     * EnvironmentProfile: 粗略环境描述（可多类混合）。
     * 典型使用：在初始化/关卡加载时设置一次，运行时很少改动。
     */
    struct EnvironmentProfile
    {
        // 环境权重，范围建议 0..1，可多项并存，内部会归一化使用
        float sea          = 0.0f; // 海中间
        float shore        = 0.0f; // 海边/海岸
        float desert       = 0.0f; // 沙漠中间
        float desert_sea   = 0.0f; // 沙漠与海交界
        float forest       = 0.0f; // 森林
        float city         = 0.0f; // 城市
        float snow         = 0.0f; // 雪地
        float grassland    = 0.0f; // 草原
        float hills        = 0.0f; // 丘陵
        float mountain     = 0.0f; // 山地

        // 便捷设置（后四项提供默认值，兼容仅传前6项的旧用法）
        void SetWeights(float sea_w, float shore_w, float desert_w, float desert_sea_w, float forest_w, float city_w,
                        float snow_w = 0.0f, float grassland_w = 0.0f, float hills_w = 0.0f, float mountain_w = 0.0f)
        {
            sea = sea_w; shore = shore_w; desert = desert_w; desert_sea = desert_sea_w; forest = forest_w; city = city_w;
            snow = snow_w; grassland = grassland_w; hills = hills_w; mountain = mountain_w;
        }

        // 归一化到 0..1，若总和为 0 则保持为 0（由调用方决定默认环境）
        void Normalize()
        {
            const float sum = sea + shore + desert + desert_sea + forest + city + snow + grassland + hills + mountain;
            if (sum > 1e-6f)
            {
                const float inv = 1.0f / sum;
                sea *= inv; shore *= inv; desert *= inv; desert_sea *= inv; forest *= inv; city *= inv;
                snow *= inv; grassland *= inv; hills *= inv; mountain *= inv;
            }
        }

        // 依据权重返回一个环境天空色倾向（线性空间）
        Color4f SkyTint() const;

        // 依据权重估计环境湿度/空气湿润度（0..1）
        float Humidity() const;

        // 依据权重估计气溶胶/扬尘（0..1），城市/沙漠较高
        float Aerosol() const;
    };

    /**
     * SkyInfo: 基本天空信息
     * - sun_direction: 方向光方向（从太阳指向场景，w=0），需归一化
     * - sun_color:     方向光颜色（线性空间）
     * - sun_intensity: 光照强度（标量，可单独上传或与颜色相乘）
     * - sun_path_azimuth_deg: 正午太阳在地平面投影的方位角（度），默认 180 度=南
     * - max_elevation_deg:    正午太阳最大仰角（度），默认 60 度
     */
    struct SkyInfo
    {
        // Vector4f and Color4f types grouped together for optimal UBO alignment
        Vector4f sun_direction = Vector4f(0, 1, 0, 0);     // w=0 表示方向向量
        Color4f  sun_color     = Color4f(1, 0.95f, 0.9f, 1);
        Color4f  base_sky_color = Color4f(0.5f, 0.6f, 1.0f, 1.0f); // 天空基础色（用于shader中的exp2(-ray.y / BaseSkyColor)计算）
        Color4f  moon_color     = Color4f(0.8f, 0.8f, 1.0f, 1.0f);
        Color4f  halo_color     = Color4f(1.0f, 0.9f, 0.7f, 1.0f);

        // Scalar values grouped together
        float    sun_intensity = 1.0f;
        float    sun_path_azimuth_deg = 180.0f;            // 正午方位角（默认朝南）
        float    max_elevation_deg    = 60.0f;             // 正午最大仰角
        float    latitude_deg  = 0.0f;                     // 纬度（度）
        float    longitude_deg = 0.0f;                     // 经度（度）
        float    moon_intensity = 0.3f;
        float    halo_intensity = 0.5f;
        float    padding_ubo = 0.0f;                       // UBO对齐填充

        // Date info for solar declination calculation
        int      year  = 2024;
        int      month = 4;
        int      day   = 10;

        // 环境概况（可多类混合）
        EnvironmentProfile environment{};

        // 未来可用的大气与曝光等参数，先注释保留：
        // float turbidity        = 2.0f;    // 浊度（大气混浊程度）
        // float rayleigh         = 1.0f;    // 瑞利散射强度
        // float mie              = 0.005f;  // 米氏散射强度
        // float ground_albedo    = 0.1f;    // 地表反照率
        // float exposure         = 1.0f;    // 曝光
        // float sun_angular_deg  = 0.53f;   // 太阳视半径（度）
        // Color3f sky_tint       = {0.5f, 0.6f, 1.0f}; // 天空色倾向
        // bool   enable_stars    = false;   // 夜空星星

        /** 设置经纬度（度） */
        void SetLocation(float latitude_deg, float longitude_deg);
        /** 设置日期（年-月-日），用于计算太阳赤纬（影响季节变化） */
        void SetDate(int year, int month, int day);
        /** 设置环境概况（可多类混合） */
        void SetEnvironment(const EnvironmentProfile &env) { environment = env; environment.Normalize(); }

        /** 根据“本地时间（小时/分/秒）”设置太阳/月亮方向与颜色（使用已存储经纬度与日期） */
        void SetByTimeOfDay(float hour, float minute = 0.0f, float second = 0.0f);
        /** 使用 std::tm 的本地时间来设置（仅取时分秒，不修改已存储的日期） */
        void SetByLocalTime(const std::tm &local_tm);
        /** 使用系统当前本地时间来设置（仅取时分秒，不修改已存储的日期） */
        void SetBySystemClock();
    };
} // namespace hgl::graph
