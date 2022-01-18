#include<hgl/graph/Camera.h>
namespace hgl
{
    namespace graph
    {
        void Camera::Refresh()
        {
            view_line                   =pos-target;

            camera_direction            =normalized(view_line);
            camera_right                =normalized(cross(world_up,     camera_direction));
            camera_up                   =normalized(cross(camera_right, camera_direction));

            info.ortho                  =ortho(width,height);

            info.projection             =perspective(Yfov,width/height,znear,zfar);

            info.inverse_projection     =inverse(info.projection);

            info.view                   =lookat(pos,target,world_up);
            info.inverse_view           =inverse(info.view);

            info.vp                     =info.projection*info.view;
            info.inverse_vp             =inverse(info.vp);

            {
                glm::mat4 tmp=info.view;
                tmp[3]=glm::vec4(0,0,0,1);

                info.sky=info.projection*tmp;
            }

            info.pos                    =pos;
            info.target                 =target;

            info.world_up               =world_up;

            info.view_line              =view_line;
            info.camera_direction       =camera_direction;
            info.camera_right           =camera_right;
            info.camera_up              =camera_up;

            info.znear                  =znear;
            info.zfar                   =zfar;

            info.canvas_resolution.x    =width;
            info.canvas_resolution.y    =height;
            info.viewport_resolution.x  =vp_width;
            info.viewport_resolution.y  =vp_height;
            info.inv_viewport_resolution=Vector2f(1.0f/vp_width,1.0f/vp_height);
        }
    }//namespace graph
}//namespace hgl
