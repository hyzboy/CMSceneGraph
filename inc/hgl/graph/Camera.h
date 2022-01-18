#ifndef HGL_GRAPH_CAMERA_INCLUDE
#define HGL_GRAPH_CAMERA_INCLUDE

#include<hgl/graph/CameraInfo.h>
namespace hgl
{
    namespace graph
    {
        /**
         * 曝光控制
         */
        struct ExposureControl
        {
            float aperture      =1.0f;          ///<光圈
            float shutter       =1.0f/8.0f;     ///<快门时间(秒)
            float iso           =800.0f;
            float exposure      =0.0f;
        };

        /**
         * 摄像机数据结构
         */
        struct Camera
        {
            float width;                ///<画布宽
            float height;               ///<画布高

            uint vp_width;              ///<视图宽
            uint vp_height;             ///<视图高

            float Yfov;                 ///<水平FOV
            float znear,zfar;           ///<Z轴上离摄像机的距离(注：因znear会参与计算，为避免除0操作，请不要使用0或过于接近0的值)

            Vector3f pos;               ///<摄像机坐标
            Vector3f target;            ///<目标点坐标

            Vector3f world_up;          ///<向上量(默认0,0,1)
            
            Vector3f view_line;         ///<视线(eye-target)
            Vector3f camera_direction;
            Vector3f camera_right;
            Vector3f camera_up;

        public:

            CameraInfo info;

            Camera()
            {
                hgl_zero(*this);

                Yfov        =45;
                znear       =1.0f;
                zfar        =15000;
                world_up.z  =1.0f;
            }

        public:

            void Refresh();

        public:

            void Transform(const Matrix3f &mat)
            {
                camera_direction=mat*camera_direction;
                camera_up       =mat*camera_up;
                camera_right    =mat*camera_right;
            }

            /**
             * 向指定向量移动
             * @param move_dist 移动距离
             */
            void Move(const Vector3f &move_dist)
            {
                pos+=move_dist;
                target+=move_dist;
            }

            /**
             * 以自身为中心旋转
             * @param ang 角度
             * @param axis 旋转轴
             */
            void Rotate(double ang,const Vector3f &axis)
            {
                normalize(axis);

                const Matrix3f mat=rotate(hgl_deg2rad(ang),axis);
                
                target=pos+mat*(target-pos);
            }

            /**
             * 以目标为中心旋转
             * @param ang 角度
             * @param axis 旋转轴
             */
            void WrapRotate(double ang,const Vector3f &axis)
            {
                normalize(axis);

                const Matrix3f mat=rotate(hgl_deg2rad(ang),axis);

                pos=target+mat*(pos-target);
            }

        public: //距离

            const float GetDistance()const{return length(pos-target);}                                 ///<获取视线长度(摄像机到目标点)

            /**
             * 调整距离
             * @param rate 新距离与原距离的比例
             */
            void Distance(float rate)                                                               ///<调整距离
            {
                if(rate==1.0)return;

                pos=target+(pos-target)*rate;
            }
        };//struct Camera
        
        class WalkerCamera:public Camera
        {
        public:

            using Camera::Camera;
            virtual ~WalkerCamera()=default;

        public:

            /**
             * 向前移动指定距离(延视线)
             */
            virtual void Backward(const float move_length)
            {
                const Vector3f dir=camera_direction-camera_direction*world_up;      //减去世界向上向量，变成2D坐标

                Move(dir*move_length);
            }

            /**
             * 向后移动指定距离(延视线)
             */
            virtual void Forward(const float move_length){Backward(-move_length);}

            /**
             * 向上移动指定距离(和视线垂直90度)
             */
            virtual void Up(const float move_length)
            {
                Move(camera_up*move_length);
            }
            
            /**
             * 向下移动指定距离(和视线垂直90度)
             */
            virtual void Down(const float move_length){Up(-move_length);}

            virtual void Left(const float move_length)
            {
                Move(camera_right*move_length);
            }

            virtual void Right(const float move_length){Left(-move_length);}

            virtual void HoriRotate(const float ang)
            {
                Rotate(ang,camera_up);
            }

            virtual void VertRotate(const float ang)
            {
                Rotate(ang,camera_right);
            }

            virtual void WrapHoriRotate(const float ang)
            {
                WrapRotate(ang,camera_up);
            }

            virtual void WrapVertRotate(const float ang)
            {
                WrapRotate(ang,camera_right);
            }
        };//class WalkerCamera:public Camera
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_CAMERA_INCLUDE
