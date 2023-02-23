﻿#include<hgl/graph/Camera.h>
namespace hgl
{
    namespace graph
    {
        void RefreshCameraInfo(CameraInfo *ci,const ViewportInfo *vi,const Camera *cam)
        {
            ci->projection             =perspective(cam->Yfov,vi->canvas_resolution.x/vi->canvas_resolution.y,cam->znear,cam->zfar);

            ci->inverse_projection     =inverse(ci->projection);

            ci->inverse_view           =inverse(ci->view);

            ci->vp                     =ci->projection*ci->view;
            ci->inverse_vp             =inverse(ci->vp);

            {
                glm::mat4 tmp=ci->view;
                tmp[3]=glm::vec4(0,0,0,1);

                ci->sky=ci->projection*tmp;
            }

            ci->pos                    =cam->pos;
            ci->view_line              =cam->view_line;
            ci->world_up               =cam->world_up;

            ci->znear                  =cam->znear;
            ci->zfar                   =cam->zfar;
        }
    }//namespace graph
}//namespace hgl
