#include<hgl/graph/Plane.h>

namespace hgl::graph
{
    float DistanceBetweenPointAndRectangle3D(const Vector3f &p,const Rectangle3D &rect)
    {
        Vector3f v=p-rect.center;

        float up_len=dot(v,rect.up);
        float right_len=dot(v,rect.right);

        if(up_len<0||up_len>rect.size.y
            ||right_len<0||right_len>rect.size.x)
        {
            float up_len2=up_len<0?0:up_len>rect.size.y?rect.size.y:up_len;
            float right_len2=right_len<0?0:right_len>rect.size.x?rect.size.x:right_len;

            Vector3f up_v=rect.up*up_len2;
            Vector3f right_v=rect.right*right_len2;

            Vector3f point=rect.center+up_v+right_v;

            return length(p-point);
        }

        return 0;
    }
}//namespace hgl::graph
