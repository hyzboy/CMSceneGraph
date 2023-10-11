#ifndef HGL_GRAPH_FIRST_PERSON_CAMERA_CONTROL_INCLUDE
#define HGL_GRAPH_FIRST_PERSON_CAMERA_CONTROL_INCLUDE

/**
 * thank for LearnOpenGL
 * link: https://learnopengl.com/Getting-started/Camera
 */

#include<hgl/graph/CameraControl.h>
namespace hgl
{
    namespace graph
    {
        class FirstPersonCameraControl:public CameraControl
        {
            float pitch;        ///<抬头角度(绕X轴旋转角度(X轴左右))
            float yaw;          ///<左右角度(绕Z轴旋转角度(Z轴向上))
            float roll;         ///<歪头角度(绕Y轴旋转角度(Y轴向前))

            Vector3f front;
            Vector3f right;
            Vector3f up;

            Vector3f target;            ///<目标点坐标

            Vector2f ReverseDirection;  ///<是否反转方向

        public:

            FirstPersonCameraControl(ViewportInfo *v,Camera *c):CameraControl(v,c)
            {
                target=Vector3f(0.0f);

                pitch=0;
                yaw  =deg2rad(-90.0f);
                roll =0;

                ReverseDirection.x=1;
                ReverseDirection.y=1;

                UpdateCameraVector();
            }
            virtual ~FirstPersonCameraControl()=default;
            
            void SetReserveDirection(bool x,bool y)
            {
                ReverseDirection.x=x?-1:1;
                ReverseDirection.y=y?-1:1;
            }

            void SetTarget(const Vector3f &t)
            {
                front   =normalize(t-camera->pos);
                right   =normalize(cross(front,camera->world_up));
                up      =normalize(cross(right,front));

                pitch   =asin(front.z);
                yaw     =atan2(front.x,front.y);

                UpdateCameraVector();
            }

            void Refresh() override
            {
                target=camera->pos+front;
                
                camera_info.view_line  =front;
                camera_info.view       =glm::lookAtRH(camera->pos,target,up);

                RefreshCameraInfo(&camera_info,vi,camera);
            }

        public: //移动
            
            void UpdateCameraVector()
            {
                front   =PolarToVector(yaw,pitch);

                right   =normalize(cross(front,camera->world_up));
                up      =normalize(cross(right,front));
            }

            void Forward(float move_step)
            {
                camera->pos+=front*move_step;
            }

            void Backward(float move_step)
            {
                camera->pos-=front*move_step;
            }

            void Left(float move_step)
            {
                camera->pos-=right*move_step;
            }

            void Right(float move_step)
            {
                camera->pos+=right*move_step;
            }

        public: //旋转

            void Rotate(const Vector2f &axis)
            {
                constexpr double top_limit      =deg2rad( 89.0f);
                constexpr double bottom_limit   =deg2rad(-89.0f);

                yaw     -=axis.x*ReverseDirection.x/180.0f;
                pitch   -=axis.y*ReverseDirection.y/180.0f;

                if(pitch>top_limit      )pitch=top_limit;
                if(pitch<bottom_limit   )pitch=bottom_limit;
            
                UpdateCameraVector();
            }

            void Move(const Vector3f &delta)
            {
                camera->pos+=delta;
            }
        };//class FirstPersonCameraControl:public CameraControl
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_FIRST_PERSON_CAMERA_CONTROL_INCLUDE