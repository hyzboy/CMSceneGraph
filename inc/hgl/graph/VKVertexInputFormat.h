#ifndef HGL_GRAPH_VULKAN_VERTEX_INPUT_FORMAT_INCLUDE
#define HGL_GRAPH_VULKAN_VERTEX_INPUT_FORMAT_INCLUDE

#include<hgl/graph/VKNamespace.h>
#include<hgl/graph/VertexAttrib.h>
VK_NAMESPACE_BEGIN
struct VertexInputFormat
{
    VkFormat    format;
    uint        vec_size;
    uint        stride;

    const char *        name;
    int                 binding;
    VkVertexInputRate   input_rate;
    VertexInputGroup    group;
};//struct VertexInputFormat

using VIF=VertexInputFormat;
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_VERTEX_INPUT_FORMAT_INCLUDE
