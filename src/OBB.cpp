#include<hgl/graph/OBB.h>
#include<hgl/graph/AABB.h>

namespace hgl::graph
{
    void OBB::ComputePlanes()
    {
        planes[0].Set(center + axis[0] * half_length.x,  axis[0]);      // axis[0] 的正方向面
        planes[1].Set(center - axis[0] * half_length.x, -axis[0]);      // axis[0] 的负方向面
        planes[2].Set(center + axis[1] * half_length.y,  axis[1]);      // axis[1] 的正方向面
        planes[3].Set(center - axis[1] * half_length.y, -axis[1]);      // axis[1] 的负方向面
        planes[4].Set(center + axis[2] * half_length.z,  axis[2]);      // axis[2] 的正方向面
        planes[5].Set(center - axis[2] * half_length.z, -axis[2]);      // axis[2] 的负方向面
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
        // 中心点需要应用完整的变换
        center = local_to_world * Vector4f(aabb.GetCenter(), 1.0f);
        
        // 半长直接从AABB获取
        half_length = aabb.GetLength() * 0.5f; // 假设GetLength返回的是全长

        // 取出local_to_world的旋转部分赋给 axis
        axis[0]=glm::normalize(local_to_world[0]);
        axis[1]=glm::normalize(local_to_world[1]);
        axis[2]=glm::normalize(local_to_world[2]);

        ComputePlanes();
    }
}//namespace hgl::graph
