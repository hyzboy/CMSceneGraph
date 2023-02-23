#include<hgl/graph/ViewportInfo.h>

namespace hgl
{
    namespace graph
    {
        void RefreshViewportInfo(ViewportInfo *vi);
        {
            vi->ortho                   =ortho(info.canvas_resolution.x,info.canvas_resolution.y);

            info.inv_viewport_resolution=Vector2f(1.0f/vp_width,1.0f/vp_height);
        }
    }//namespace graph
}//namespace hgl