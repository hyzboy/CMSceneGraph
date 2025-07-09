#pragma once

#include<hgl/graph/Camera.h>
#include<hgl/graph/VKBuffer.h>
#include<hgl/type/IDName.h>
#include<hgl/io/event/WindowEvent.h>

namespace hgl::graph
{
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
    };//class CameraControl
}//namespace hgl::graph
