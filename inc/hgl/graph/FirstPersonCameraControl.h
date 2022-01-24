#ifndef HGL_GRAPH_FIRST_PERSON_CAMERA_CONTROL_INCLUDE
#define HGL_GRAPH_FIRST_PERSON_CAMERA_CONTROL_INCLUDE

/**
 * @see https://github.com/SaschaWillems/Vulkan/blob/master/base/camera.hpp
 * Author: Sascha Willems
 * License: MIT
 */

#include<hgl/graph/CameraControl.h>
namespace hgl
{
    namespace graph
    {
        class FirstPersonCameraControl:public CameraControl
        {
            Vector3f rotation=Vector3f(0.0f);

            Vector3f camera_front;
            Vector3f camera_right;

        public:

            FirstPersonCameraControl(Camera *c):CameraControl(c)
            {
                Rotate(Vector2f(0.0f,-90.0f),1.0f);

                UpdateCameraFront();
            }
            virtual ~FirstPersonCameraControl()=default;

            void Refresh() override
            {
                Matrix4f rotM=Matrix4f(1.0f);
                Matrix4f transM;

                rotM=glm::rotate(rotM,glm::radians(rotation.x),Vector3f(1.0f,0.0f,0.0f));
                rotM=glm::rotate(rotM,glm::radians(rotation.y),Vector3f(0.0f,1.0f,0.0f));
                rotM=glm::rotate(rotM,glm::radians(rotation.z),Vector3f(0.0f,0.0f,1.0f));

                transM=glm::translate(glm::mat4(1.0f),camera->pos);

                camera->info.view=rotM*transM;

                camera->RefreshCameraInfo();
            }

        public: //ÒÆ¶¯

            void UpdateCameraFront()
            {
                camera_front.x=cos(glm::radians(rotation.x))*sin(glm::radians(rotation.y));
                camera_front.y=sin(glm::radians(rotation.x));
                camera_front.z=cos(glm::radians(rotation.x))*cos(glm::radians(rotation.y));

                camera_right=normalize(cross(camera_front,camera->world_up));
            }

            void Forward(float move_step)
            {
                camera->pos+=camera_front*move_step;
            }

            void Backward(float move_step)
            {
                camera->pos-=camera_front*move_step;
            }

            void Left(float move_step)
            {
                camera->pos-=camera_right*move_step;
            }

            void Right(float move_step)
            {
                camera->pos+=camera_right*move_step;
            }

        public: //Ðý×ª

            void Rotate(const Vector2f &axis,const float move_step)
            {
                constexpr float deadZone=0.0015f;
                constexpr float range=1.0f-deadZone;

                if(fabsf(axis.x)>deadZone)
                {
                    float pos=(fabsf(axis.x)-deadZone)/range;
                    rotation.z+=pos*((axis.x<0.0f)?-1.0f:1.0f)*move_step;
                }

                if(fabsf(axis.y)>deadZone)
                {
                    float pos=(fabsf(axis.y)-deadZone)/range;
                    rotation.x+=pos*((axis.y<0.0f)?-1.0f:1.0f)*move_step;
                }
            
                UpdateCameraFront();
            }
        };//class FirstPersonCameraControl:public CameraControl
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_FIRST_PERSON_CAMERA_CONTROL_INCLUDE