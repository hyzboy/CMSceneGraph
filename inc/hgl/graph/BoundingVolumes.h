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
    
    struct BoundingVolumesData;

    struct BoundingVolumes
    {
        AABB aabb;
        OBB obb;
        BoundingSphere bsphere;

    public:

        BoundingVolumes()
        {
            Clear();
        }

        void Clear()
        {
            aabb.Clear();
            obb.Clear();
            hgl_zero(bsphere);
        }

        bool IsEmpty()const
        {
            return aabb.IsEmpty() && obb.GetHalfExtend().x <= 0 && bsphere.radius <= 0;
        }

    public:

        void SetFromAABB(const AABB &box)
        {
            aabb = box;
            obb.Set(box);
            bsphere.center = aabb.GetCenter();
            bsphere.radius = glm::length(aabb.GetMax() - bsphere.center);
        }

        void SetFromAABB(const Vector3f &min_v,const Vector3f &max_v)
        {
            AABB box;
            box.SetMinMax(min_v,max_v);
            SetFromAABB(box);
        }

    public:

        void Pack(BoundingVolumesData *packed) const;
    };
    
#pragma pack(push,1)
    struct BoundingVolumesData
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

        void To(BoundingVolumes *bounds);
    };//struct BoundingVolumesData
#pragma pack(pop)
}//namespace hgl::graph
