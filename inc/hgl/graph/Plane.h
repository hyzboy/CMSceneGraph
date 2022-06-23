#ifndef HGL_GRAPH_PLANE_INCLUDE
#define HGL_GRAPH_PLANE_INCLUDE

#include<hgl/math/Vector.h>
namespace hgl
{
    namespace graph
    {
        /**
        * 面数据结构
        */
        struct Plane
        {
            Vector3f normal;
            float d;

        public:

            void Set(const Vector3f &_p,float _d)
            {
                normal=_p;
                d=_d;
            }

            void Set(const Vector3f &face_center_point,const Vector3f &face_normal)
            {
                normal=face_normal;
                d=dot(face_center_point,face_normal);
            }

            void Set(const Vector4f &p)
            {
                normal=p;
                d=p.w;
            }

            float Distance(const Vector3f &p)const
            {
                return(d+dot(normal,p));
            }
        };//struct Plane
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_PLANE_INCLUDE
