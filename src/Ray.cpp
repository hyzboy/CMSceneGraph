#include<hgl/graph/Ray.h>
#include<hgl/graph/CameraInfo.h>
#include<hgl/graph/ViewportInfo.h>
#include<hgl/graph/Sphere.h>
#include<hgl/graph/AABB.h>
#include<hgl/graph/OBB.h>

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
        * 求射线与指定线段的距离的平方(Github Copilot)
        */
        const float Ray::ToLineSegmentDistanceSquared(const Vector3f &start,const Vector3f &end)const
        {
            const Vector3f ab=end-start;
            const Vector3f ac=origin-start;

            const float e=dot(ac,ab);

            if(e<=0)return dot(ac,ac);

            const float f=dot(ab,ab);

            if(e>=f)return dot(origin-end,origin-end);

            return dot(origin-start,origin-start)-e*e/f;
        }

        bool Ray::CrossSphere(const Sphere &s)const
        {
            const Vector3f  sphere_center=s.GetCenter();
            const float     sphere_radius=s.GetRadius();

            const Vector3f oc=origin-sphere_center;

            const float b=dot(oc,direction);
            const float c=dot(oc,oc)-sphere_radius*sphere_radius;

            if(c>0&&b>0)return(false);

            const float discr=b*b-c;

            if(discr<0)return(false);

            return(true);
        }

        bool Ray::CrossEllipseSphere(const EllipseSphere &es)const
        {
            const Vector3f es_center=es.GetCenter();
            const Vector3f es_radius=es.GetRadius();

            const Vector3f oc=origin-es_center;

            const float b=dot(oc,direction);
            const float c=dot(oc,oc)-es_radius.x*es_radius.y*es_radius.z;

            if(c>0&&b>0)return(false);

            const float discr=b*b-c;

            if(discr<0)return(false);

            return(true);
        }

        /**
        * 指当前射线是否与指定三角形相交(此函数由Github Copilot生成，未经测试)
        */
        bool Ray::CrossTriangle(const Triangle3D &tri)const
        {
            const Vector3f a1=tri[0];
            const Vector3f a2=tri[1];
            const Vector3f a3=tri[2];

            const Vector3f normal=cross(a2-a1,a3-a1);

            const float cos=dot(normal,direction);

            if(cos>=0)return(false);        //射线与三角形背对

            const float d=dot(normal,a1);

            const float t=(d-dot(normal,origin))/cos;

            if(t<0)return(false);            //射线与三角形不相交

            const Vector3f hit_point=origin+direction*t;

            const Vector3f v1=cross(a2-a1,hit_point-a1);
            const Vector3f v2=cross(a3-a2,hit_point-a2);
            const Vector3f v3=cross(a1-a3,hit_point-a3);

            if(dot(v1,v2)<0)return(false);
            if(dot(v2,v3)<0)return(false);
            if(dot(v3,v1)<0)return(false);

            return(true);
        }

        /**
        * 求指定面是否与射线交汇
        */
        bool Ray::CrossPlane(const Vector3f &v1,const Vector3f &v2,const Vector3f &v3,const Vector3f &v4)const
        {
            const float ray_len=ToPointDistance(v1)+ToPointDistance(v2)+ToPointDistance(v3)+ToPointDistance(v4);

            const float len=length(v1,v3)+length(v2,v4);

            return(ray_len<=len);
        }
    }//namespace graph
}//namespace hgl
