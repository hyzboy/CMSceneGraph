#ifndef HGL_GRAPH_VIEWPORT_INFO_INCLUDE
#define HGL_GRAPH_VIEWPORT_INFO_INCLUDE

#include<hgl/math/Math.h>

namespace hgl
{
    namespace graph
    {
        /**
         * �ӿ���Ϣ
         */
        struct ViewportInfo
        {
            Matrix4f ortho;                 ///<2D������ͼ����

            Vector2f canvas_resolution;     ///<�����ߴ�(��ͼ�óߴ�)
            Vector2f viewport_resolution;   ///<��ͼ�ߴ�(��ʾ��ʵ�ʳߴ�,glFragCoord֮����)
            Vector2f inv_viewport_resolution;
        };//struct ViewportInfo

        constexpr size_t ViewportInfoBytes=sizeof(ViewportInfo);

        void RefreshViewportInfo(ViewportInfo *);
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_VIEWPORT_INFO_INCLUDE
#pragma once
