﻿#include<hgl/graph/Camera.h>
#include<hgl/graph/Frustum.h>
namespace hgl
{
    namespace graph
    {
        void RefreshCameraInfo(CameraInfo *ci,const ViewportInfo *vi,const Camera *cam)
        {
            ci->projection             =perspective(cam->Yfov,vi->GetAspectRatio(),cam->znear,cam->zfar);

            ci->inverse_projection     =inverse(ci->projection);

            ci->inverse_view           =inverse(ci->view);

            ci->vp                     =ci->projection*ci->view;
            ci->inverse_vp             =inverse(ci->vp);

            GetFrustumPlanes(ci->frustum_planes,ci->vp);

            {
                glm::mat4 tmp=ci->view;
                tmp[3]=glm::vec4(0,0,0,1);

                ci->sky=ci->projection*tmp;
            }

            ci->pos                    =cam->pos;
            ci->view_line              =cam->view_line;
            ci->world_up               =cam->world_up;

            // http://www.opengl-tutorial.org/intermediate-tutorials/billboards-particles/billboards/

            ci->billboard_right         =Vector3f(ci->view[0][0],ci->view[1][0],ci->view[2][0]);
            ci->billboard_up            =Vector3f(ci->view[0][1],ci->view[1][1],ci->view[2][1]);

            ci->znear                  =cam->znear;
            ci->zfar                   =cam->zfar;
        }
    }//namespace graph
}//namespace hgl
