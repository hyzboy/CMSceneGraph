﻿#include<hgl/graph/AABB.h>
#include<hgl/graph/OBB.h>

namespace hgl
{
    namespace graph
    {
        void AABB::Set(const OBB &obb)
        {   //此函数由Github Copilot生成，未经测试
            const Vector3f obb_center       =obb.GetCenter();
            const Vector3f obb_half_length  =obb.GetHalfExtend();

            SetCornerLength(obb_center-obb_half_length,obb_half_length*2.0f);
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

            Update();
        }

        void AABB::Update()
        {
            face_center_point[0]=Vector3f(minPoint.x, center.y, center.z);
            face_center_point[1]=Vector3f(maxPoint.x, center.y, center.z);
            face_center_point[2]=Vector3f(center.x, minPoint.y, center.z);
            face_center_point[3]=Vector3f(center.x, maxPoint.y, center.z);
            face_center_point[4]=Vector3f(center.x, center.y, minPoint.z);
            face_center_point[5]=Vector3f(center.x, center.y, maxPoint.z);

            for(uint i=0;i<6;i++)
                planes[i].Set(face_center_point[i],AABBFaceNormal[i]);
        }
    }//namespace graph
}//namespace hgl
