#ifndef HGL_GRAPH_VULKAN_INLINE_PIPELINE_INCLUDE
#define HGL_GRAPH_VULKAN_INLINE_PIPELINE_INCLUDE

#include<hgl/TypeFunc.h>
#include<hgl/graph/vulkan/VKNamespace.h>

VK_NAMESPACE_BEGIN
enum class InlinePipeline
{
    Solid3D=0,
    Alpha3D,

    Solid2D,
    Alpha2D,

    Sky,

    ENUM_CLASS_RANGE(Solid3D,Alpha2D)
};//enum class InlinePipeline

struct PipelineData;

/**
 * 获取内置管线数据
 */
PipelineData *GetPipelineData(const InlinePipeline &);
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_INLINE_PIPELINE_INCLUDE
