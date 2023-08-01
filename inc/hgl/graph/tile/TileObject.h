#pragma once

#include<hgl/type/RectScope.h>

namespace hgl
{
    namespace graph
    {
        struct TileObject
        {
            int col,row;            //当前tile在整个纹理中的tile位置

            RectScope2i uv_pixel;   //以象素为单位的tile位置和尺寸
            RectScope2f uv_float;   //以浮点为单位的tile位置和尺寸
        };
    }//namespace graph
}//namespace hgl
