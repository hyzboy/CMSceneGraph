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

            Vector3f world_up;          ///<向上量(默认0,0,1)
            
            Vector3f view_line;         ///<视线 normalize(eye-target)

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

            void RefreshCameraInfo();
        };//struct Camera
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_CAMERA_INCLUDE
