#pragma once

#include<hgl/graph/AABB.h>
#include<hgl/graph/OBB.h>

namespace hgl::graph
{
    struct BoundingSphere
    {
        Vector3f center;
        float radius;
    };

    struct Bounds
    {
        AABB aabb;
        OBB obb;
        BoundingSphere bsphere;
    };

    struct BoundsData
    {
        struct
        {
            float min[3];
            float max[3];
        }aabb;

        struct
        {
            float center[3];
            float axis[3][3];      //3个轴
            float half_size[3];    //3个半尺寸
        }obb;

        struct
        {
            float center[3];
            float radius;
        }bsphere;
    };

    constexpr const size_t BoundsDataBytes = sizeof(BoundsData);
}//namespace hgl::graph
