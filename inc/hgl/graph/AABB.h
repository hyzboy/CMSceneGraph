#ifndef HGL_GRAPH_AABB_INCLUDE
#define HGL_GRAPH_AABB_INCLUDE

#include<hgl/math/Math.h>
#include<hgl/graph/Plane.h>

namespace hgl
{
    namespace graph
    {
        class OBB;

        constexpr Vector3f AABBFaceNormal[6]=
        {
            Vector3f(-1,  0,  0),
            Vector3f( 1,  0,  0),
            Vector3f( 0, -1,  0),
            Vector3f( 0,  1,  0),
            Vector3f( 0,  0, -1),
            Vector3f( 0,  0,  1)
        };

        /**
        * Axis Aligned Bounding Box
        */
        class AABB
        {
            Vector3f minPoint;
            Vector3f center;
            Vector3f length;
            Vector3f maxPoint;

            Vector3f face_center_point[6];

            Plane planes[6];

        private:

            void Update();

        public:

            AABB()
            {
                SetCornerLength(Vector3f(0,0,0),Vector3f(1,1,1));
            }

            void SetCornerLength(const Vector3f &c,const Vector3f &l)           ///<按顶角和长度设置盒子范围
            {
                minPoint=c;
                length=l;
                maxPoint=c+l;
                center=(minPoint+maxPoint)/2.0f;
                Update();
            }

            void SetMinMax(const Vector3f &min_v,const Vector3f &max_v)         ///<按最小最大值设置盒子范围
            {
                minPoint=min_v;
                maxPoint=max_v;
                length=max_v-min_v;
                center=(min_v+max_v)/2.0f;
                Update();
            }

            void Set(const OBB &);

            void SetZero()
            {
                hgl_zero(minPoint);
                hgl_zero(maxPoint);
            }

            const   Vector3f &  GetMin      ()const{return minPoint;}
            const   Vector3f &  GetMax      ()const{return maxPoint;}

            const   Vector3f &  GetCenter   ()const{return center;}
            const   Vector3f &  GetLength   ()const{return length;}

                    Vector3f    GetVertexP  (const Vector3f &)const;
                    Vector3f    GetVertexN  (const Vector3f &)const;

            void Enclose(const AABB &box)
            {
                SetMinMax(MinVector(minPoint,box.minPoint)
                         ,MaxVector(maxPoint,box.maxPoint));
            }

            const Plane &GetFacePlanes(int i)const{return planes[i];}

        public:

            void operator += (const AABB &);                                   ///<融合另一个AABox
        };//struct AABB
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_AABB_INCLUDE
