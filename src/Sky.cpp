#include <hgl/graph/Sky.h>

namespace hgl::graph
{
    void SkyInfo::SetTime(float hour,float minute,float second)
    {
        std::tm t{};

        t.tm_hour = static_cast<int>(hour);
        t.tm_min  = static_cast<int>(minute);
        t.tm_sec  = static_cast<int>(second);

        const float total_hours = hour + minute / 60.0f + second / 3600.0f;

        // 简单模型：假设太阳在正南方（180度），根据时间计算仰角
        // 正午12点时，太阳在最高点，仰角为90度
        // 早晨6点和傍晚18点，太阳在地平线，仰角为0度
        // 夜晚则太阳在地平线以下，仰角为负值
        float elevation_deg = 0.0f;

        if (total_hours >= 6.0f && total_hours <= 18.0f)
        {
            // 白天：线性插值从0到90再到0
            if (total_hours <= 12.0f)
                elevation_deg = (total_hours - 6.0f) * (90.0f / 6.0f); // 6点到12点
            else
                elevation_deg = (18.0f - total_hours) * (90.0f / 6.0f); // 12点到18点
        }
        else
        {
            // 夜晚：太阳在地平线以下，设为-10度
            elevation_deg = -10.0f;
        }
        // 方位角固定为180度（正南方）
        const float azimuth_deg = 180.0f;
        // 将方位角和仰角转换为方向向量
        const float azimuth_rad   = azimuth_deg * (3.14159265f / 180.0f);
        const float elevation_rad = elevation_deg * (3.14159265f / 180.0f);

        sun_direction.x = cos(elevation_rad) * sin(azimuth_rad);
        sun_direction.y = cos(elevation_rad) * cos(azimuth_rad);
        sun_direction.z = sin(elevation_rad);
        sun_direction.w = 0.0f; // 方向向量

        // 根据仰角调整太阳光强度和颜色（简单模型）
        if (elevation_deg > 0.0f)
        {
            // 白天，光强随仰角增加
            sun_intensity=1.0f;
            moon_intensity=0.0f;
        }
        else
        {
            sun_intensity=0.0f;
            moon_intensity=1.0f;
        }
    }
} // namespace hgl::graph
