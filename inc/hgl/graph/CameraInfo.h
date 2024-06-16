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
            Matrix4f projection;
            Matrix4f inverse_projection;

            Matrix4f view;
            Matrix4f inverse_view;

            Matrix4f vp;                    ///< projection * view
            Matrix4f inverse_vp;

            Matrix4f sky;                   ///<天空盒用矩阵

            alignas(16) Vector3f pos;                   ///<摄像机坐标
            alignas(16) Vector3f view_line;             ///<pos-target
            alignas(16) Vector3f world_up;

            alignas(16) Vector3f billboard_up;
            alignas(16) Vector3f billboard_right;

            float znear,zfar;
        };//struct CameraInfo

        constexpr size_t CameraInfoBytes=sizeof(CameraInfo);
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_CAMERA_INFO_INCLUDE
