#include<hgl/graph/Ray.h>
#include<hgl/graph/CameraInfo.h>

namespace hgl
{
    namespace graph
    {
        /**
        * 求射线上距离指定点最近的点
        * @param point 指定点
        * @return 位于射线上的点
        */
        Vector3f Ray::ClosestPoint(const Vector3f &point)const
        {
            const float length=dot(direction,point-origin);

            if(length<=0)
                return origin;
            else
                return origin+direction*length;
        }

        /**
        * 设置屏幕坐标产生拾取射线
        * @param x 屏幕点坐标X
        * @param y 屏幕点坐标Y
        * @param ci 摄像机信息
        */
        void Ray::Set(int x,int y,const CameraInfo *ci)
        {
            Vector3f pos(x,y,0);
            Vector4i vp(0,0,ci->viewport_resolution.x,ci->viewport_resolution.y);

            origin      =glm::unProject(pos,ci->view,ci->projection,vp);        //射线最近点

            pos.z=1.0f;

            direction   =glm::unProject(pos,ci->view,ci->projection,vp);        //射线最远点
        }

        /**
        * 求指定面是否与射线交汇
        */
        bool Ray::CrossPlane(const Vector3f &v1,const Vector3f &v2,const Vector3f &v3,const Vector3f &v4)const
        {
            const float ray_len=Distance(v1)+Distance(v2)+Distance(v3)+Distance(v4);

            const float len=length(v1,v3)+length(v2,v4);

            return(ray_len<=len);
        }

        /**
        * 求指定box是否与射线交汇
        */
        bool Ray::CrossBox(const Vector3f &v1,const Vector3f &v2)const
        {
            const Vector3f v3(v1[0],v2[1],v2[2]);
            const Vector3f v4(v2[0],v1[1],v1[2]);
            const Vector3f v5(v1[0],v1[1],v2[2]);
            const Vector3f v6(v2[0],v2[1],v1[2]);

            const float ray_len=Distance(v1)+Distance(v2)+Distance(v3)+Distance(v4)+Distance(v5)+Distance(v6);

            const float len=length(v1,v2)+length(v3,v4)+length(v5,v6);

            return(ray_len<=len);
        }
    }//namespace graph
}//namespace hgl
