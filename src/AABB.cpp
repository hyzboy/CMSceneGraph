#include<hgl/graph/AABB.h>
namespace hgl
{
    namespace graph
    {
        AABB::AABB(void)
        {
            SetCornerLength(Vector3f(0,0,0),Vector3f(1,1,1));
        }

        Vector3f AABB::GetVertexP(const Vector3f &normal) const
        {
            Vector3f res = minPoint;

            if (normal[0] > 0)res[0] += length[0];
            if (normal[1] > 0)res[1] += length[1];
            if (normal[2] > 0)res[2] += length[2];

            return(res);
        }

        Vector3f AABB::GetVertexN(const Vector3f &normal) const
        {
            Vector3f res = minPoint;

            if (normal[0] < 0)res[0] += length[0];
            if (normal[1] < 0)res[1] += length[1];
            if (normal[2] < 0)res[2] += length[2];

            return(res);
        }

        void AABB::operator+=(const AABB &box)
        {
            minPoint[0]=hgl_min(minPoint[0],box.minPoint[0]);
            minPoint[1]=hgl_min(minPoint[1],box.minPoint[1]);
            minPoint[2]=hgl_min(minPoint[2],box.minPoint[2]);

            maxPoint[0]=hgl_max(maxPoint[0],box.maxPoint[0]);
            maxPoint[1]=hgl_max(maxPoint[1],box.maxPoint[1]);
            maxPoint[2]=hgl_max(maxPoint[2],box.maxPoint[2]);

            length=maxPoint-minPoint;

            center=(minPoint+maxPoint)/2.0f;
        }
    }//namespace graph
}//namespace hgl
