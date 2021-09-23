#ifndef HGL_GRAPH_AABB_INCLUDE
#define HGL_GRAPH_AABB_INCLUDE

#include<hgl/math/Math.h>
namespace hgl
{
    namespace graph
    {
        /**
        * AABB
        */
        struct AABB
        {
            Vector3f minPoint;
            Vector3f center;
            Vector3f length;
            Vector3f maxPoint;

        public:

            AABB();
            AABB(const Vector3f &c,const Vector3f &l)
            {
                SetCornerLength(c,l);
            }

            void SetCornerLength(const Vector3f &c,const Vector3f &l)           ///<按顶角和长度设置盒子范围
            {
                minPoint=c;
                length=l;
                maxPoint=c+l;
                center=(minPoint+maxPoint)/2.0f;
            }

            void SetMinMax(const Vector3f &min_v,const Vector3f &max_v)         ///<按最小最大值设置盒子范围
            {
                minPoint=min_v;
                maxPoint=max_v;
                length=max_v-min_v;
                center=(min_v+max_v)/2.0f;
            }

            Vector3f GetVertexP(const Vector3f &)const;
            Vector3f GetVertexN(const Vector3f &)const;

        public:

            void operator += (const AABB &);                                   ///<融合另一个AABox
        };//struct AABB
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_AABB_INCLUDE
