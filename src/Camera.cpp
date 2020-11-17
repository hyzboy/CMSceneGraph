#include<hgl/graph/Camera.h>
namespace hgl
{
    namespace graph
    {
        template<typename V>
        inline Matrix4f LookAt(const V &eye,const V &target,const V &up)
        {
            V forward=target-eye;

            normalize(forward);

            V side=cross(forward,up);

            normalize(side);

            V nup=cross(side,forward);

            Matrix4f result( side.x,         side.y,         side.z,            1.0f,
                             nup.x,          nup.y,          nup.z,             1.0f,
                            -forward.x,     -forward.y,     -forward.z/2.0f,    1.0f,
                             0.0f,           0.0f,           0.0f,              1.0f);
                                                        //  ^^^^^^
                                                        //  某些引擎这里为0.5，那是因为他们是 -1 to 1 的Z值设定，而我们是0 to 1，所以这里不用乘
                                                        //  同理，camera的znear为接近0的正数，zfar为一个较大的正数，默认使用16/256

            return result*translate(-eye.xyz());
        }

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

            matrix.ortho=ortho(width,height);

            if(type==CameraType::Perspective)
                matrix.projection=perspective(fov,width/height,znear,zfar);
            else
                matrix.projection=ortho(width,height,znear,zfar);               //这个算的不对

            matrix.inverse_projection=matrix.projection.Inverted();

            matrix.view=hgl::graph::LookAt(pos,target,world_up);
            //matrix.view=Matrix4f::LookAt(pos.xyz(),center.xyz(),world_forward.xyz(),world_up.xyz(),world_up.xyz());
            matrix.inverse_view=matrix.view.Inverted();
            matrix.normal=matrix.inverse_view.Transposed();

            matrix.mvp=matrix.projection*matrix.view;
            matrix.inverse_mvp=matrix.mvp.Inverted();

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

            matrix.canvas_resolution.x  =width;
            matrix.canvas_resolution.y  =height;
            matrix.viewport_resolution.x=vp_width;
            matrix.viewport_resolution.y=vp_height;
            matrix.inv_viewport_resolution=Vector2f(1.0f/vp_width,1.0f/vp_height);

            frustum.SetVerticalFovAndAspectRatio(DegToRad(fov),width/height);
            frustum.SetViewPlaneDistances(znear,zfar);
        }
    }//namespace graph
}//namespace hgl
