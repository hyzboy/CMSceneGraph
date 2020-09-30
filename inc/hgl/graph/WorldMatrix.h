﻿#ifndef HGL_GRAPH_WORLD_MATRIX_INCLUDE
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
            Matrix4f normal;                // normal=transpose(inverse(modelview)),normal是3x3，但glsl中都是4对齐，所以实际占用为3x4
                                            // 虽然这里被写成了4x4，但因为AVX加速计算会以256位对齐，所以依然占用4x4的空间。需在shader中进行标记
            Matrix4f mvp;
            Matrix4f inverse_mvp;

            Vector4f camera_pos;            ///<摄像机坐标
            Vector2f canvas_resolution;     ///<画布尺寸(绘图用尺寸)
            Vector2f viewport_resolution;   ///<视图尺寸(显示的实际尺寸,glFragCoord之类用)
        };//struct WorldMatrix
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_WORLD_MATRIX_INCLUDE
