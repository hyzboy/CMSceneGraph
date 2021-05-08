#ifndef HGL_GRAPH_CAMERA_INFO_INCLUDE
#define HGL_GRAPH_CAMERA_INFO_INCLUDE

#include<hgl/math/Math.h>

namespace hgl
{
    namespace graph
    {
        /**
         * 摄相机矩阵数据
         */
        struct CameraInfo
        {
            Matrix4f ortho;                 ///<2D正角视图矩阵

            Matrix4f projection;
            Matrix4f inverse_projection;

            Matrix4f view;
            Matrix4f inverse_view;
            Matrix4f normal;                ///<transpose(inverse(mat3(view)));

            Matrix4f vp;                    ///< projection * view
            Matrix4f inverse_vp;

            Vector4f pos;                   ///<摄像机坐标
            Vector4f target;                ///<摄像机目标点
            Vector4f world_up;

            Vector4f view_line;
            Vector4f camera_direction;
            Vector4f camera_right;
            Vector4f camera_up;
            Vector4f view_distance;         //x,y,z分别对应right,direction,up
                                            //w对应view_line

            float znear,zfar;

            Vector2f canvas_resolution;     ///<画布尺寸(绘图用尺寸)
            Vector2f viewport_resolution;   ///<视图尺寸(显示的实际尺寸,glFragCoord之类用)
            Vector2f inv_viewport_resolution;
        };//struct CameraInfo

        constexpr size_t CameraInfoBytes=sizeof(CameraInfo);
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_CAMERA_INFO_INCLUDE
