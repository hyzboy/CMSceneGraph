#include <hgl/graph/BoundingSphere.h>

namespace hgl::graph
{
    // Helper: sphere from AABB (center = mid, radius = half diagonal)
    BoundingSphere SphereFromAABB(const AABB &a)
    {
        BoundingSphere s;

        s.Clear();

        if(!a.IsEmpty())
        {
            s.center=(a.GetMin()+a.GetMax())*0.5f;
            s.radius=glm::length(a.GetMax()-s.center);
        }

        return s;
    }

    // Internal template implementation for SphereFromPoints
    namespace
    {
        template<typename VecType>
        BoundingSphere SphereFromPointsImpl(const VecType *pts,const uint32 count)
        {
            BoundingSphere s;

            s.Clear();
            if(count<=0) return s;
        
            glm::vec3 c(0.0f);

            const VecType *p=pts;
            for(uint32 i=0;i<count;++i)
            {
                c.x += p->x;
                c.y += p->y;
                c.z += p->z;

                ++p;
            }
            c /= static_cast<float>(count);
        
            float r=0.0f;
            p=pts;
            for(uint32 i=0;i<count;++i)
            {
                r = std::max(r, glm::length(Vector3f(p->x - c.x,
                                                    p->y - c.y,
                                                    p->z - c.z)));

                ++p;
            }
        
            s.center = c;
            s.radius = r;
            return s;
        }
    }

    // Helper: sphere from points (center = average, radius = max distance to center) using float input
    BoundingSphere SphereFromPoints(const Vector3f *pts,const uint32 count)
    {
        return SphereFromPointsImpl(pts,count);
    }

    BoundingSphere SphereFromPoints(const Vector4f *pts,const uint32 count)
    {
        return SphereFromPointsImpl(pts,count);
    }
}//namespace hgl::graph

