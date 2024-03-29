#ifndef HGL_GRAPH_FRUSTUM_INCLUDE
#define HGL_GRAPH_FRUSTUM_INCLUDE

#include<hgl/graph/AABB.h>
#include<hgl/graph/Plane.h>
namespace hgl
{
    namespace graph
    {
        /**
        * 平截头裁剪处理
        */
        class Frustum
        {
            Plane pl[6];

        public:
            
		    enum class Side 
            { 
                Left=0,
                Right,
                Front,
                Back,
                Top,
                Bottom
            };

            enum
            {
                OUTSIDE,    //外部
                INTERSECT,  //交错
                INSIDE      //内部
            };

        public:

            void SetMatrix(const Matrix4f &);

            int PointIn(const Vector3f &)const;
            int SphereIn(const Vector3f &,float radius)const;
            int BoxIn(const AABB &)const;
        };//class Frustum
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_FRUSTUM_INCLUDE
