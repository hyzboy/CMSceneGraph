#ifndef HGL_GRAPH_BITMAP_INCLUDE
#define HGL_GRAPH_BITMAP_INCLUDE

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

        struct ImageRegion
        {
            int left,top,width,height;
            uint bytes;
        };//struct ImageRegion
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_BITMAP_INCLUDE
