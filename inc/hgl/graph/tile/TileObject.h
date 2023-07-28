#pragma once

#include<hgl/type/Map.h>

namespace hgl
{
    namespace graph
    {
        using TileUVPixel=RectScope2i;
        using TileUVFloat=RectScope2f;

        using TileUVFloatList=List<TileUVFloat>;
        using TileUVFloatMap=Map<u32char,TileUVFloat>;

        struct TileObject
        {
            int col,row;            //当前tile在整个纹理中的tile位置

            TileUVPixel uv_pixel;   //以象素为单位的tile位置和尺寸
            TileUVFloat uv_float;   //以浮点为单位的tile位置和尺寸
        };//struct TileObject
    }//namespace graph
}//namespace hgl
