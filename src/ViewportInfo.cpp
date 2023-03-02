#include<hgl/graph/ViewportInfo.h>

namespace hgl
{
    namespace graph
    {
        void ViewportInfo::SetViewport(int w,int h)
        {
            viewport_resolution.x=w;
            viewport_resolution.y=h;

            inv_viewport_resolution.x=1.0f/float(w);
            inv_viewport_resolution.y=1.0f/float(h);
        }

        void ViewportInfo::SetCanvas(float w,float h)
        {
            canvas_resolution.x=w;
            canvas_resolution.y=h;
            ortho_matrix=ortho(w,h);
        }
    }//namespace graph
}//namespace hgl