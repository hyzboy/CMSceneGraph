#ifndef HGL_GRAPH_VIEWPORT_INFO_INCLUDE
#define HGL_GRAPH_VIEWPORT_INFO_INCLUDE

#include<hgl/math/Math.h>

namespace hgl
{
    namespace graph
    {
        /**
         * 视口信息
         */
        struct ViewportInfo
        {
            Matrix4f ortho;                 ///<2D正角视图矩阵

            Vector2f canvas_resolution;     ///<画布尺寸(绘图用尺寸)
            Vector2f viewport_resolution;   ///<视图尺寸(显示的实际尺寸,glFragCoord之类用)
            Vector2f inv_viewport_resolution;
        };//struct ViewportInfo

        constexpr size_t ViewportInfoBytes=sizeof(ViewportInfo);

        void RefreshViewportInfo(ViewportInfo *);
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_VIEWPORT_INFO_INCLUDE
#pragma once
