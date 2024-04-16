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

        /**
        * 3D空间中的矩形<br>
        * 一般用于描述一些特殊的矩形平面区域
        */
        struct Rectangle3D
        {
            Vector3f center;
            Vector3f normal;
            Vector3f up;
            Vector3f right;
            Vector2f size;
        };

        inline float DistanceBetweenPointAndRectangle3D(const Vector3f &p,const Rectangle3D &rect)
        {
            Vector3f v=p-rect.center;

            float up_len=dot(v,rect.up);
            float right_len=dot(v,rect.right);

            if(up_len<0||up_len>rect.size.y
               ||right_len<0||right_len>rect.size.x)
            {
                float up_len2=up_len<0?0:up_len>rect.size.y?rect.size.y:up_len;
                float right_len2=right_len<0?0:right_len>rect.size.x?rect.size.x:right_len;

                Vector3f up_v=rect.up*up_len2;
                Vector3f right_v=rect.right*right_len2;

                Vector3f point=rect.center+up_v+right_v;

                return length(p-point);
            }

            return 0;
        }
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_PLANE_INCLUDE
