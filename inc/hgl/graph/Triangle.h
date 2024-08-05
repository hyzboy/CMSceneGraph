#pragma once

#include<hgl/math/Vector.h>
#include<hgl/math/Area.h>

namespace hgl
{
    namespace graph
    {
        template<typename T> class Triangle2
        {
            glm::vec<2,T> vertex[3];

        public:

            Triangle2()
            {
                vertex[0]=glm::vec<2,T>(0,0);
                vertex[1]=glm::vec<2,T>(0,0);
                vertex[2]=glm::vec<2,T>(0,0);
            }

            Triangle2(const glm::vec<2,T> &v0,const glm::vec<2,T> &v1,const glm::vec<2,T> &v2)
            {
                vertex[0]=v0;
                vertex[1]=v1;
                vertex[2]=v2;
            }

            virtual ~Triangle2()=default;

            void SetVertex(const glm::vec<2,T> v[3])
            {
                vertex=v;
            }

            void SetVertex(const glm::vec<2,T> &v0,const glm::vec<2,T> &v1,const glm::vec<2,T> &v2)
            {
                vertex[0]=v0;
                vertex[1]=v1;
                vertex[2]=v2;
            }

            void SetVertex(const int index,const glm::vec<2,T> &v)
            {
                if(index>=0&&index<=2)
                    vertex[index]=v;
            }

            const glm::vec<2,T> &GetVertex(const int index)const
            {
                if(index>=0&&index<=2)return vertex[index];

                return glm::vec<2,T>(0,0);
            }

            const T GetEdgeLength(const int index)const
            {
                if(index==0)return length_2d(vertex[0],vertex[1]);else
                if(index==1)return length_2d(vertex[1],vertex[2]);else
                if(index==2)return length_2d(vertex[2],vertex[0]);else
                    return 0;
            }

            const T Area()const
            {
                return TriangleArea(vertex[0],vertex[1],vertex[2]);
            }

            const bool PointIn(const glm::vec<2,T> &pt)const
            {
                // Compute vectors
                glm::dvec2 v2v1 = vertex[1] - vertex[0];
                glm::dvec2 v3v1 = vertex[2] - vertex[0];
                glm::dvec2 ptv1 = pt        - vertex[0];

                // Compute dot products
                double dot00 = glm::dot(v3v1, v3v1);
                double dot01 = glm::dot(v3v1, v2v1);
                double dot02 = glm::dot(v3v1, ptv1);
                double dot11 = glm::dot(v2v1, v2v1);
                double dot12 = glm::dot(v2v1, ptv1);

                // Compute barycentric coordinates
                double invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);
                double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
                double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

                // Check if point is in triangle
                return (u >= 0) && (v >= 0) && (u + v < 1);
            }
        };//template<typename T> class Triangle2

        using Triangle2s=Triangle2<short>;
        using Triangle2i=Triangle2<int>;
        using Triangle2f=Triangle2<float>;
        using Triangle2d=Triangle2<double>;

        ///**
        //* 计算三角形的面积
        //*/
        //inline float TriangleArea(const Triangle3D &tri)
        //{
        //    return length(cross(tri[1]-tri[0],tri[2]-tri[0]))/2.0f;
        //}

        ///**
        //* 计算点到三角形的距离(此函数由Github Copilot生成，未经测试)
        //*/
        //inline float DistancePointAndTriangle(const Vector3f &p,const Triangle3D &tri)
        //{
        //    Vector3f v0=tri[0]-p;
        //    Vector3f v1=tri[1]-p;
        //    Vector3f v2=tri[2]-p;
        //
        //    Vector3f n=cross(v1-v0,v2-v0);
        //
        //    float area=length(n)/2.0f;
        //
        //    float a0=TriangleArea(Triangle3D{p,tri[1],tri[2]});
        //    float a1=TriangleArea(Triangle3D{tri[0],p,tri[2]});
        //    float a2=TriangleArea(Triangle3D{tri[0],tri[1],p});
        //
        //    if(a0+a1+a2>area)
        //        return -1;
        //
        //    return 2.0f*area/length(n);
        //}
    }//namespace graph
}//namespace hgl
