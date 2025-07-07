#include<hgl/graph/OBB.h>
#include<hgl/graph/AABB.h>

namespace hgl::graph
{
    void OBB::ComputePlanes()
    {
        planes[0].Set(center,axis[0]);
        planes[1].Set(center,axis[1]);
        planes[2].Set(center,axis[2]);
        planes[3].Set(center+axis[0]*half_length.x,axis[0]);
        planes[4].Set(center+axis[1]*half_length.y,axis[1]);
        planes[5].Set(center+axis[2]*half_length.z,axis[2]);
    }

    void OBB::Set(const Vector3f &c,const Vector3f &hl)
    {
        Set(c,Vector3f(1,0,0),Vector3f(0,1,0),Vector3f(0,0,1),hl);
    }

    void OBB::Set(const Vector3f &c,const Vector3f &a0,const Vector3f &a1,const Vector3f &a2,const Vector3f &hl)
    {
        center=c;
        axis[0]=a0;
        axis[1]=a1;
        axis[2]=a2;
        half_length=hl;

        ComputePlanes();
    }

    void OBB::Set(const AABB &aabb)
    {
        Set(aabb.GetCenter(),aabb.GetLength());
    }

    void OBB::Set(const Matrix4f &local_to_world,const AABB &aabb)
    {
        center=aabb.GetCenter();
        half_length=aabb.GetLength();

        axis[0]=local_to_world*Vector4f(1,0,0,1.0f);
        axis[1]=local_to_world*Vector4f(0,1,0,1.0f);
        axis[2]=local_to_world*Vector4f(0,0,1,1.0f);

        ComputePlanes();
    }
}//namespace hgl::graph
