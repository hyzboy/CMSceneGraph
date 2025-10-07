#include<hgl/graph/AABB.h>

namespace hgl::graph
{
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

    template<typename T>
    void AABB::SetFromPoints(const T *pts,const uint32_t count)
    {
        Clear();

        const T *in=pts;
            
        T minp=*in;
        T maxp=*in;
        ++in;

        for(uint32_t i=1;i<count;++i)
        {
            minp=glm::min(minp,*in);
            maxp=glm::max(maxp,*in);
            ++in;
        }

        SetMinMax(minp,maxp);
    }

    void AABB::Set(const Vector3f *pts,const uint32_t count){SetFromPoints<Vector3f>(pts,count);}
    void AABB::Set(const Vector4f *pts,const uint32_t count){SetFromPoints<Vector4f>(pts,count);}

    AABB AABB::Transformed(const Matrix4f &m)const
    {
        if(IsEmpty())
            return *this;

        const Vector3f corners[8]=
        {
            minPoint,
            Vector3f(maxPoint.x,minPoint.y,minPoint.z),
            Vector3f(minPoint.x,maxPoint.y,minPoint.z),
            Vector3f(maxPoint.x,maxPoint.y,minPoint.z),
            Vector3f(minPoint.x,minPoint.y,maxPoint.z),
            Vector3f(maxPoint.x,minPoint.y,maxPoint.z),
            Vector3f(minPoint.x,maxPoint.y,maxPoint.z),
            maxPoint
        };

        Vector3f transformed[8];
        for(int i=0;i<8;++i)
            transformed[i] = Vector3f(m * Vector4f(corners[i], 1.0f));

        AABB result;
        result.SetFromPoints<Vector3f>(transformed, 8);
        return result;
    }
}//namespace hgl::graph
