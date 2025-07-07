#pragma once

#include<hgl/math/Math.h>
#include<hgl/graph/Plane.h>

namespace hgl::graph
{
    class AABB;

    /**
        * Oriented Bounding Box<Br>
        * 本类由Github Copilot生成，未经测试
        */
    class OBB
    {
        Vector3f center;
        Vector3f axis[3];
        Vector3f half_length;

        Plane planes[6];

    private:

        void ComputePlanes();

    public:

        const Vector3f &GetCenter()const{return center;}
        const Vector3f &GetAxis(int n)const{return axis[n];}
        const Vector3f &GetHalfLength()const{return half_length;}

    public:

        void Set(const Vector3f &c,const Vector3f &hl);
        void Set(const Vector3f &c,const Vector3f &a0,const Vector3f &a1,const Vector3f &a2,const Vector3f &hl);
        void Set(const AABB &aabb);
        void Set(const Matrix4f &local_to_world,const AABB &aabb);

    public:

        OBB()
        {
            Set(Vector3f(0,0,0),Vector3f(1,1,1));
        }

        OBB(const Vector3f &c,const Vector3f &hl)
        {
            Set(c,hl);
        }

        OBB(const Vector3f &c,const Vector3f &a0,const Vector3f &a1,const Vector3f &a2,const Vector3f &hl)
        {
            Set(c,a0,a1,a2,hl);
        }

        OBB(const AABB &aabb)
        {
            Set(aabb);
        }

        OBB(const Matrix4f &local_to_world,const AABB &aabb)
        {
            Set(local_to_world,aabb);
        }

    public:

        const Vector3f GetMin()const{return center-half_length;}
        const Vector3f GetMax()const{return center+half_length;}

        const Plane &GetFacePlanes(int i)const{return planes[i];}
    };//class OBB
}//namespace hgl::graph
