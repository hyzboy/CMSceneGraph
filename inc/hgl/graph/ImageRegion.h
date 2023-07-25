#pragma once

#include<hgl/type/DataType.h>
namespace hgl
{
    namespace graph
    {
        struct Image2DRegion
        {
            int left,top,width,height;
            uint bytes;
        };//struct ImageRegion
    }//namespace graph
}//namespace hgl
