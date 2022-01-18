#ifndef HGL_GRAPH_CAMERA_INFO_INCLUDE
#define HGL_GRAPH_CAMERA_INFO_INCLUDE

#include<hgl/math/Math.h>

namespace hgl
{
    namespace graph
    {
        /**
         * 摄相机信息
         */
        struct CameraInfo
        {
            Matrix4f ortho;                 ///<2D正角视图矩阵

            Matrix4f projection;
            Matrix4f inverse_projection;

            Matrix4f view;
            Matrix4f inverse_view;

            Matrix4f vp;                    ///< projection * view
            Matrix4f inverse_vp;

            Matrix4f sky;                   ///<天空盒用矩阵

            alignas(16) Vector3f pos;                   ///<摄像机坐标
            alignas(16) Vector3f target;                ///<摄像机目标点
            alignas(16) Vector3f world_up;

            alignas(16) Vector3f view_line;             ///<pos-target
            alignas(16) Vector3f camera_direction;
            alignas(16) Vector3f camera_right;
            alignas(16) Vector3f camera_up;

            float znear,zfar;

            Vector2f canvas_resolution;     ///<画布尺寸(绘图用尺寸)
            Vector2f viewport_resolution;   ///<视图尺寸(显示的实际尺寸,glFragCoord之类用)
            Vector2f inv_viewport_resolution;
        };//struct CameraInfo

        constexpr size_t CameraInfoBytes=sizeof(CameraInfo);
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_CAMERA_INFO_INCLUDE
