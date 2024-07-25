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
        class ViewportInfo
        {
            Matrix4f ortho_matrix;              ///<64 2D正角视图矩阵

            Vector2f canvas_resolution;         ///< 8 画布尺寸(绘图用尺寸)
            Vector2f viewport_resolution;       ///< 8 视图尺寸(显示的实际尺寸,glFragCoord之类用)
            Vector2f inv_viewport_resolution;   ///< 8 视图尺寸的倒数

        public:

            ViewportInfo()
            {
                hgl_zero(*this);
            }

            void SetViewport(uint,uint);
            void SetCanvas(float,float);
            void Set(uint w,uint h)
            {
                SetViewport(w,h);
                SetCanvas(w,h);
            }

        public:

            const float GetAspectRatio()const
            {
                return canvas_resolution.x/canvas_resolution.y;
            }

            const Vector2f GetViewport()const
            {
                return viewport_resolution;
            }
        };//class ViewportInfo

        constexpr size_t ViewportInfoBytes=sizeof(ViewportInfo);
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_VIEWPORT_INFO_INCLUDE
#pragma once
