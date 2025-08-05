#pragma once

#include<hgl/graph/Camera.h>
#include<hgl/graph/VKBuffer.h>
#include<hgl/type/IDName.h>
#include<hgl/io/event/WindowEvent.h>

namespace hgl::graph
{
    struct Ray;

    using UBOCameraInfo=UBOInstance<CameraInfo>;

    HGL_DEFINE_IDNAME(CameraControlIDName,   char)

    class CameraControl:public io::WindowEvent
    {
    protected:

        ViewportInfo *vi;
        Camera *camera;

        UBOCameraInfo *ubo_camera_info;
        CameraInfo *camera_info;
        DescriptorBinding *desc_binding_camera;

    public:

        virtual const CameraControlIDName GetControlName()const=0;

    public:

        CameraControl(ViewportInfo *v,Camera *c,UBOCameraInfo *ci);

        virtual ~CameraControl();

        void SetViewport(ViewportInfo *i)
        {
            vi=i;
        }

        void SetCamera(Camera *c)
        {
            camera=c;
        }

        void SetPosition(const Vector3f &p)
        {
            if(camera)
                camera->pos=p;
        }

        virtual void SetTarget(const Vector3f &t)=0;

        void ZoomFOV(int adjust)
        {
            constexpr float MinFOV=10;
            constexpr float MaxFOV=180;

            camera->Yfov+=float(adjust)/10.0f;

            if(adjust<0&&camera->Yfov<MinFOV)camera->Yfov=MinFOV;else
            if(adjust>0&&camera->Yfov>MaxFOV)camera->Yfov=MaxFOV;
        }

        ViewportInfo *      GetViewportInfo     (){return vi;}
        Camera *            GetCamera           (){return camera;}
        CameraInfo *        GetCameraInfo       (){return camera_info;}

        DescriptorBinding * GetDescriptorBinding(){return desc_binding_camera;}

        virtual void Refresh()=0;

    public:

        bool SetMouseRay(Ray *,const Vector2i &);

        /**
        * 本地坐标到观察坐标
        */
        const Vector3f LocalToViewSpace(const Matrix4f &l2w,const Vector3f &local_pos)const
        {
            if(!vi||!camera_info)return(Vector3f(0,0,0));

            const Vector4f clip_pos=camera_info->LocalToViewSpace(l2w,local_pos);

            if(clip_pos.w==0.0f)
                return(Vector3f(0,0,0));

            return Vector3f(clip_pos.x/clip_pos.w,clip_pos.y/clip_pos.w,clip_pos.z/clip_pos.w);
        }

        /**
        * 求指定坐标点(世界坐标)单位长度1相对当前屏幕空间象素的粗略缩放比(注：不准)
        */
        float GetPixelPerUnit(const Vector3f &point)const
        {
            if(!vi)return(1.0f);

            const float dist=length(point,camera->pos);

            return vi->GetViewportHeight()/(2.0f*dist*tan(camera->Yfov*HGL_PI/360.0f));
        }

        const Vector2f WorldPositionToScreen(const Vector3f &wp)const
        {
            if(!vi)return(Vector2i(0,0));

            const Vector4f clip_pos=camera_info->Project(wp);

            if(clip_pos.w==0.0f)
                return(Vector2i(0,0));

            Vector3f ndc_pos(clip_pos.x/clip_pos.w,clip_pos.y/clip_pos.w,clip_pos.z/clip_pos.w);

            Vector2f screen_pos;

            screen_pos.x=(ndc_pos.x+1.0f)*0.5f*vi->GetViewportWidth();
            screen_pos.y=(ndc_pos.y+1.0f)*0.5f*vi->GetViewportHeight();

            if (screen_pos.x<0)screen_pos.x=0;
            if (screen_pos.x>=vi->GetViewportWidth())screen_pos.x=vi->GetViewportWidth()-1;
            if (screen_pos.y<0)screen_pos.y=0;
            if (screen_pos.y>=vi->GetViewportHeight())screen_pos.y=vi->GetViewportHeight()-1;

            return(screen_pos);
        }

        const Vector3f ScreenPositionToWorld(const Vector2i &sp)const
        {
            if(!vi)return(Vector3f(0,0,0));

            const float x=(float(sp.x)/vi->GetViewportWidth())*2.0f-1.0f;
            const float y=(float(sp.y)/vi->GetViewportHeight())*2.0f-1.0f;

            Vector4f clip_pos(x,y,-1.0f,1.0f);
            Vector3f ndc_pos(clip_pos.x/clip_pos.w,clip_pos.y/clip_pos.w,clip_pos.z/clip_pos.w);

            return camera_info->UnProject(ndc_pos);
        }
    };//class CameraControl
}//namespace hgl::graph
