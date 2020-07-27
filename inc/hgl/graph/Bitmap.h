#ifndef HGL_GRAPH_BITMAP_INCLUDE
#define HGL_GRAPH_BITMAP_INCLUDE

#include<hgl/type/graph/vulkan/VKFormat.h>
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
#endif//HGL_GRAPH_BITMAP_INCLUDE
