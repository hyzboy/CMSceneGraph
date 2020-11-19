#include<hgl/graph/Camera.h>
namespace hgl
{
    namespace graph
    {
        void Camera::Refresh()
        {
            view_line       =pos-target;
            camera_direction=normalized(view_line);
            camera_right    =normalized(cross(world_up,camera_direction));
            camera_up       =cross(camera_direction,camera_right);

            view_distance.x =length(camera_right);
            view_distance.y =length(camera_direction);
            view_distance.z =length(camera_up);
            view_distance.w =length(view_line);

            matrix.ortho    =ortho(width,height);

            if(type==CameraType::Perspective)
                matrix.projection=perspective(Yfov,width/height,znear,zfar);
            else
                matrix.projection=ortho(width,height,znear,zfar);               //这个算的不对

            matrix.inverse_projection   =matrix.projection.Inverted();

            matrix.view                 =lookat(pos,target,world_up);
            matrix.inverse_view         =matrix.view.Inverted();
            matrix.normal               =matrix.inverse_view.Transposed();

            matrix.viewproj             =matrix.projection*matrix.view;
            matrix.inverse_viewproj     =matrix.viewproj.Inverted();

            //注意： C++中要 projection * model_view * local_to_world * position
            //现在glsl中被标记为row_major，顺序同C++

            matrix.pos              =pos;
            matrix.target           =target;

            matrix.world_forward    =world_forward;
            matrix.world_right      =world_right;
            matrix.world_up         =world_up;

            matrix.view_line        =view_line;
            matrix.camera_direction =camera_direction;
            matrix.camera_right     =camera_right;
            matrix.camera_up        =camera_up;

            matrix.canvas_resolution.x      =width;
            matrix.canvas_resolution.y      =height;
            matrix.viewport_resolution.x    =vp_width;
            matrix.viewport_resolution.y    =vp_height;
            matrix.inv_viewport_resolution  =Vector2f(1.0f/vp_width,1.0f/vp_height);
        }
    }//namespace graph
}//namespace hgl
