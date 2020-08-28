#ifndef HGL_GRAPH_WORLD_MATRIX_INCLUDE
#define HGL_GRAPH_WORLD_MATRIX_INCLUDE

#include<hgl/math/Math.h>

namespace hgl
{
    namespace graph
    {
        /**
         * 世界矩阵数据
         */
        struct WorldMatrix
        {
            Matrix4f ortho;                 //2D正角视图矩阵

            Matrix4f projection;
            Matrix4f inverse_projection;

            Matrix4f modelview;
            Matrix4f inverse_modelview;

            Matrix4f mvp;
            Matrix4f inverse_map;

            Vector4f camera_pos;            ///<摄像机坐标
            Vector2f canvas_resolution;     ///<画布尺寸(绘图用尺寸)
            Vector2f viewport_resolution;   ///<视图尺寸(显示的实际尺寸,glFragCoord之类用)
        };//struct WorldMatrix
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_WORLD_MATRIX_INCLUDE
