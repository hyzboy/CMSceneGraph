#ifndef HGL_GRAPH_LOOKAT_CAMERA_CONTROL_INCLUDE
#define HGL_GRAPH_LOOKAT_CAMERA_CONTROL_INCLUDE

#include<hgl/graph/CameraControl.h>
namespace hgl
{
    namespace graph
    {
        class LookAtCameraControl:public CameraControl
        {
        protected:

            Vector3f direction;
            Vector3f right;
            Vector3f up;

        public:

            Vector3f target;            ///<Ŀ�������

        public:

            using CameraControl::CameraControl;
            virtual ~LookAtCameraControl()=default;

            void Refresh() override
            {
                if(!camera)return;

                camera->info.view_line  =camera->pos-target;
                camera->info.view       =lookat(camera->pos,target,camera->world_up);

                direction               =normalized(camera->view_line);
                right                   =normalized(cross(camera->world_up, direction));
                up                      =normalized(cross(right,            direction));

                camera->RefreshCameraInfo();
            }
            
        public:

            /**
             * ��ָ�������ƶ�
             * @param move_dist �ƶ�����
             */
            void Move(const Vector3f &move_dist)
            {
                camera->pos+=move_dist;
                target+=move_dist;
            }

            /**
             * ������Ϊ������ת
             * @param ang �Ƕ�
             * @param axis ��ת��
             */
            void Rotate(double ang,const Vector3f &axis)
            {
                normalize(axis);

                const Matrix3f mat=rotate(deg2rad(ang),axis);
                
                target=camera->pos+mat*(target-camera->pos);
            }

            /**
             * ��Ŀ��Ϊ������ת
             * @param ang �Ƕ�
             * @param axis ��ת��
             */
            void WrapRotate(double ang,const Vector3f &axis)
            {
                normalize(axis);

                const Matrix3f mat=rotate(deg2rad(ang),axis);

                camera->pos=target+mat*(camera->pos-target);
            }

        public: //����

            const float GetDistance()const{return length(camera->pos-target);}                      ///<��ȡ���߳���(�������Ŀ���)

            /**
             * ��������
             * @param rate �¾�����ԭ����ı���
             */
            void Distance(float rate)                                                               ///<��������
            {
                if(rate==1.0)return;

                camera->pos=target+(camera->pos-target)*rate;
            }
        };//class LookAtCameraControl:public CameraControl
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_LOOKAT_CAMERA_CONTROL_INCLUDE