#pragma once

#include<hgl/graph/AABB.h>

namespace hgl::graph
{
    struct BoundingSphere
    {
        Vector3f center { 0.0f };

        float radius=-1.0f;

    public:

        void Clear()
        {
            center=Vector3f(0.0f);
            radius=-1.0f;
        }

        bool IsEmpty() const
        {
            return radius<=0.0f;
        }
    };

    BoundingSphere SphereFromAABB(const AABB &a);
    BoundingSphere SphereFromPoints(const Vector3f *pts,const uint32 count);
    BoundingSphere SphereFromPoints(const Vector4f *pts,const uint32 count);
}//namespace hgl::graph
