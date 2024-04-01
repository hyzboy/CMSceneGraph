#include<hgl/graph/Ray.h>
#include<hgl/graph/CameraInfo.h>
#include<hgl/graph/ViewportInfo.h>

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
        
        void unProjectZO(Vector3f &near_point,Vector3f &far_point,const Vector2f &win, const Matrix4f &Inverse, const Vector2f &viewport)
        {
            Vector4f tmp;

            tmp.x = win.x / viewport.x;
            tmp.y = win.y / viewport.y;
            tmp.x = tmp.x + tmp.x - 1.0;
            tmp.y = tmp.y + tmp.y - 1.0;

            tmp.z=0.0;
            tmp.w=1.0;

            near_point = Inverse * tmp;

            tmp.z=1.0;

            tmp = Inverse * tmp;
            tmp /= tmp.w;

            far_point=tmp;
        }

        /**
        * 设置屏幕坐标产生拾取射线
        * @param mp 屏幕点坐标
        * @param camera_info 摄像机信息
        */
        void Ray::Set(const Vector2f &mp,const CameraInfo *ci,const ViewportInfo *vi)
        {
            //新方案

            unProjectZO(origin,direction,mp,ci->inverse_vp,vi->GetViewport());

            //由于near/far的xy一样，而near.z又是0。所以省去了direction=normalize(far-near)的计算

            //旧标准方案

            //Vector3f pos(mp.x,mp.y,0);
            //Vector4i vp(0,0,camera_info->viewport_resolution.x,camera_info->viewport_resolution.y);

            //origin      =glm::unProject(pos,camera_info->view,camera_info->projection,vp);        //射线最近点

            //pos.z=1.0f;

            //direction   =glm::unProject(pos,camera_info->view,camera_info->projection,vp);        //射线最远点
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
