#pragma once

#include<hgl/math/Vector.h>

namespace hgl
{
    namespace graph
    {
        using Triangle3D=Vector3f[3];

        /**
        * 计算三角形的面积
        */
        inline float TriangleArea(const Triangle3D &tri)
        {
            return length(cross(tri[1]-tri[0],tri[2]-tri[0]))/2.0f;
        }

        /**
        * 计算点到三角形的距离(此函数由Github Copilot生成，未经测试)
        */
        inline float DistancePointAndTriangle(const Vector3f &p,const Triangle3D &tri)
        {
            Vector3f v0=tri[0]-p;
            Vector3f v1=tri[1]-p;
            Vector3f v2=tri[2]-p;
        
            Vector3f n=cross(v1-v0,v2-v0);
        
            float area=length(n)/2.0f;
        
            float a0=TriangleArea(Triangle3D{p,tri[1],tri[2]});
            float a1=TriangleArea(Triangle3D{tri[0],p,tri[2]});
            float a2=TriangleArea(Triangle3D{tri[0],tri[1],p});
        
            if(a0+a1+a2>area)
                return -1;
        
            return 2.0f*area/length(n);
        }
    }//namespace graph
}//namespace hgl
