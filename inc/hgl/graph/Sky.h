#pragma once
#include <ctime>                   // std::tm
#include <hgl/color/Color.h>
#include <hgl/graph/Camera.h>      // 提供 Vector4f（约定 Y 轴向上）

namespace hgl::graph
{
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

        // 未来可用的大气与曝光等参数，先注释保留：
        // float turbidity        = 2.0f;    // 浊度（大气混浊程度）
        // float rayleigh         = 1.0f;    // 瑞利散射强度
        // float mie              = 0.005f;  // 米氏散射强度
        // float ground_albedo    = 0.1f;    // 地表反照率
        // float exposure         = 1.0f;    // 曝光
        // float sun_angular_deg  = 0.53f;   // 太阳视半径（度）
        // Color3f sky_tint       = {0.5f, 0.6f, 1.0f}; // 天空色倾向
        // bool   enable_stars    = false;   // 夜空星星

        /**
         * 根据“本地时间（小时/分/秒）”设置太阳方向与颜色（简化日照模型）
         * 坐标系：
         *   - Y 轴向上
         *   - 方位角 azimuth：+X 为 0°，逆时针到 +Z 为 90°（右手系）
         *   - sun_path_azimuth_deg 为“正午”朝向（默认 180°=南）
         * 时间约定：
         *   - 6:00 ~ 18:00 为白天，正午（12:00）仰角最大；夜晚强度为 0
         */
        void SetByTimeOfDay(float hour, float minute = 0.0f, float second = 0.0f, 
                           float latitude_deg = 0.0f, float longitude_deg = 0.0f);

        /**
         * 根据"本地时间（小时/分/秒）"设置太阳/月亮方向与颜色（使用已存储的经纬度）
         */
        void SetByTimeOfDay(float hour, float minute = 0.0f, float second = 0.0f);

        /**
         * 使用 std::tm 的本地时间来设置太阳
         */
        void SetByLocalTime(const std::tm &local_tm);

        /**
         * 使用系统当前本地时间来设置太阳
         */
        void SetBySystemClock();
    };
} // namespace hgl::graph
