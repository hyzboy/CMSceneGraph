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
    
#pragma pack(push,1)
    struct PackedBounds
    {
        float aabbMin[3];
        float aabbMax[3];
        float obbCenter[3];
        float obbAxisX[3];
        float obbAxisY[3];
        float obbAxisZ[3];
        float obbHalfSize[3];
        float sphereCenter[3];
        float sphereRadius;

    public:

        void To(Bounds *bounds)
        {
            bounds->aabb.SetMinMax(
                Vector3f(aabbMin[0], aabbMin[1], aabbMin[2]),
                Vector3f(aabbMax[0], aabbMax[1], aabbMax[2]));

            bounds->obb.Set(
                Vector3f(obbCenter[0],  obbCenter[1],   obbCenter[2]),
                Vector3f(obbAxisX[0],   obbAxisX[1],    obbAxisX[2]),
                Vector3f(obbAxisY[0],   obbAxisY[1],    obbAxisY[2]),
                Vector3f(obbAxisZ[0],   obbAxisZ[1],    obbAxisZ[2]),
                Vector3f(obbHalfSize[0],obbHalfSize[1], obbHalfSize[2]));

            bounds->bsphere.center = Vector3f(sphereCenter[0], sphereCenter[1], sphereCenter[2]);
            bounds->bsphere.radius = sphereRadius;
        }
    };
#pragma pack(pop)
}//namespace hgl::graph
