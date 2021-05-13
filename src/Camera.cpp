#include<hgl/graph/Camera.h>
namespace hgl
{
    namespace graph
    {
        void Camera::Refresh()
        {
            view_line                   =pos-target;
            view_line.w                 =length(view_line);

            camera_direction            =normalized(view_line);
            camera_right                =normalized(cross(world_up,     camera_direction));
            camera_up                   =normalized(cross(camera_right, camera_direction));

            camera_right.w              =length(camera_right);
            camera_direction.w          =length(camera_direction);
            camera_up.w                 =length(camera_up);

            info.ortho                  =ortho(width,height);

            if(type==CameraType::Perspective)
                info.projection         =perspective(Yfov,width/height,znear,zfar);
            else
                info.projection         =ortho(width,height,znear,zfar);               //这个算的不对

            info.inverse_projection     =info.projection.Inverted();

            info.view                   =lookat(pos,target,world_up);

            info.inverse_view           =info.view.Inverted();
            info.normal                 =info.inverse_view.Transposed();

            info.vp                     =info.projection*info.view;
            info.inverse_vp             =info.vp.Inverted();

            //注意： C++中要 projection * model_view * local_to_world * position
            //现在glsl中被标记为row_major，顺序同C++

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
