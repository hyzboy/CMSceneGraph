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

        public:

            FirstPersonCameraControl(Camera *c):CameraControl(c)
            {
                target=Vector3f(0.0f);

                pitch=0;
                yaw  =-90;
                roll =0;

                UpdateCameraVector();
            }
            virtual ~FirstPersonCameraControl()=default;
            
            void SetTarget(const Vector3f &t)
            {
                front   =normalize(t-camera->pos);
                right   =normalize(cross(front,camera->world_up));
                up      =normalize(cross(right,front));

                pitch   =rad2deg(asin(front.z));
                yaw     =rad2deg(atan2(front.x,front.y));

                UpdateCameraVector();
            }

            void Refresh() override
            {
                target=camera->pos+front;
                
                camera->info.view_line  =front;
                camera->info.view       =lookat(camera->pos,target,up);

                camera->RefreshCameraInfo();
            }

        public: //移动

            void UpdateCameraVector()
            {
                const double _yaw=deg2rad(yaw);
                const double _pitch=deg2rad(pitch);

                front.x=cos(_yaw  )*cos(_pitch);
                front.y=sin(_yaw  )*cos(_pitch);
                front.z=sin(_pitch);

                normalize(front);

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
                camera->pos+=right*move_step;
            }

            void Right(float move_step)
            {
                camera->pos-=right*move_step;
            }

        public: //旋转

            void Rotate(const Vector2f &axis,const float move_step)
            {
                yaw     -=axis.x;
                pitch   -=axis.y;

                if(pitch> 89.0f)pitch= 89.0f;
                if(pitch<-89.0f)pitch=-89.0f;
            
                UpdateCameraVector();
            }
        };//class FirstPersonCameraControl:public CameraControl
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_FIRST_PERSON_CAMERA_CONTROL_INCLUDE