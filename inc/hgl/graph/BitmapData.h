#pragma once

#include<hgl/type/DataType.h>
namespace hgl
{
    namespace graph
    {
        struct BitmapData
        {
            int         width;
            int         height;
            uint32      vulkan_format;
            uint32      total_bytes;

            char *      data=nullptr;

        public:

            virtual ~BitmapData()
            {
                delete[] data;
            }
        };//struct BitmapData
    }//namespace graph
}//namespace hgl
