#include<hgl/graph/Frustum.h>

namespace hgl
{
    namespace graph
    {
        void Frustum::SetMatrix(const Matrix4f &mvp)
        {
            //@see https://github.com/SaschaWillems/Vulkan/base/frustum.hpp
            
            Vector4f planes[6];

            planes[size_t(Side::Left    )].x = mvp[0].w + mvp[0].x;
			planes[size_t(Side::Left    )].y = mvp[1].w + mvp[1].x;
			planes[size_t(Side::Left    )].z = mvp[2].w + mvp[2].x;
			planes[size_t(Side::Left    )].w = mvp[3].w + mvp[3].x;

			planes[size_t(Side::Right   )].x = mvp[0].w - mvp[0].x;
			planes[size_t(Side::Right   )].y = mvp[1].w - mvp[1].x;
			planes[size_t(Side::Right   )].z = mvp[2].w - mvp[2].x;
			planes[size_t(Side::Right   )].w = mvp[3].w - mvp[3].x;

			planes[size_t(Side::Front   )].x = mvp[0].w - mvp[0].y;
			planes[size_t(Side::Front   )].y = mvp[1].w - mvp[1].y;
			planes[size_t(Side::Front   )].z = mvp[2].w - mvp[2].y;
			planes[size_t(Side::Front   )].w = mvp[3].w - mvp[3].y;

			planes[size_t(Side::Back    )].x = mvp[0].w + mvp[0].y;
			planes[size_t(Side::Back    )].y = mvp[1].w + mvp[1].y;
			planes[size_t(Side::Back    )].z = mvp[2].w + mvp[2].y;
			planes[size_t(Side::Back    )].w = mvp[3].w + mvp[3].y;

			planes[size_t(Side::Top     )].x = mvp[0].w + mvp[0].z;
			planes[size_t(Side::Top     )].y = mvp[1].w + mvp[1].z;
			planes[size_t(Side::Top     )].z = mvp[2].w + mvp[2].z;
			planes[size_t(Side::Top     )].w = mvp[3].w + mvp[3].z;

			planes[size_t(Side::Bottom  )].x = mvp[0].w - mvp[0].z;
			planes[size_t(Side::Bottom  )].y = mvp[1].w - mvp[1].z;
			planes[size_t(Side::Bottom  )].z = mvp[2].w - mvp[2].z;
			planes[size_t(Side::Bottom  )].w = mvp[3].w - mvp[3].z;

            for(int i=0;i<6;i++)
            {
				float length = sqrtf(planes[i].x * planes[i].x + planes[i].y * planes[i].y + planes[i].z * planes[i].z);
				
                planes[i] /= length;

                pl[i].Set(planes[i]);
            }
        }

        Frustum::Scope Frustum::PointIn(const Vector3f &p) const
        {
            Frustum::Scope result = Frustum::Scope::INSIDE;

            for(int i=0; i < 6; i++)
                if (pl[i].Distance(p) < 0)
                    return Frustum::Scope::OUTSIDE;

            return(result);
        }

        Frustum::Scope Frustum::SphereIn(const Vector3f &p, float radius) const
        {
            Frustum::Scope result = Frustum::Scope::INSIDE;
            float distance;

            for(int i=0; i < 6; i++)
            {
                distance = pl[i].Distance(p);

                if (distance < -radius)
                    return Frustum::Scope::OUTSIDE;
                else
                if (distance < radius)
                    result =  Frustum::Scope::INTERSECT;
            }

            return(result);
        }

        Frustum::Scope Frustum::BoxIn(const AABB &b) const
        {
            Frustum::Scope result = Frustum::Scope::INSIDE;

            for(int i=0; i < 6; i++)
            {
                if (pl[i].Distance(b.GetVertexP(pl[i].normal)) < 0)
                    return Frustum::Scope::OUTSIDE;
                else 
                if (pl[i].Distance(b.GetVertexN(pl[i].normal)) < 0)
                    result =  Frustum::Scope::INTERSECT;
            }

            return(result);
        }
    }//namespace graph
}//namespace hgl
