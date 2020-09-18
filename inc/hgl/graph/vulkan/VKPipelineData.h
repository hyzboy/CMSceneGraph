#ifndef HGL_GRAPH_VULKAN_PIPELINE_DATA_INCLUDE
#define HGL_GRAPH_VULKAN_PIPELINE_DATA_INCLUDE

#include<hgl/graph/vulkan/VKNamespace.h>

VK_NAMESPACE_BEGIN
constexpr size_t MAX_SAMPLE_MASK_COUNT=(VK_SAMPLE_COUNT_64_BIT+31)/32;

#ifndef VK_DYNAMIC_STATE_BEGIN_RANGE
constexpr size_t VK_DYNAMIC_STATE_BEGIN_RANGE=VK_DYNAMIC_STATE_VIEWPORT;
#endif//VK_DYNAMIC_STATE_BEGIN_RANGE

#ifndef VK_DYNAMIC_STATE_END_RANGE
constexpr size_t VK_DYNAMIC_STATE_END_RANGE=VK_DYNAMIC_STATE_STENCIL_REFERENCE;
#endif//VK_DYNAMIC_STATE_END_RANGE

#ifndef VK_DYNAMIC_STATE_RANGE_SIZE
constexpr size_t VK_DYNAMIC_STATE_RANGE_SIZE=VK_DYNAMIC_STATE_END_RANGE-VK_DYNAMIC_STATE_BEGIN_RANGE+1;
#endif//VK_DYNAMIC_STATE_RANGE_SIZE

struct VKPipelineData
{
    VkGraphicsPipelineCreateInfo                pipelineInfo;

    VkPipelineVertexInputStateCreateInfo        vis_create_info;
    VkPipelineInputAssemblyStateCreateInfo      inputAssembly;
    VkPipelineTessellationStateCreateInfo       tessellation;

    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineViewportStateCreateInfo           viewportState;

    VkPipelineRasterizationStateCreateInfo      rasterizer;
    
    VkSampleMask                                sample_mask[MAX_SAMPLE_MASK_COUNT];
    VkPipelineMultisampleStateCreateInfo        multisample;

    VkPipelineDepthStencilStateCreateInfo       depthStencilState;
    
    List<VkPipelineColorBlendAttachmentState>   colorBlendAttachments;
    VkPipelineColorBlendStateCreateInfo         colorBlending;

    VkDynamicState                              dynamicStateEnables[VK_DYNAMIC_STATE_RANGE_SIZE];
    VkPipelineDynamicStateCreateInfo            dynamicState;

    float alpha_test;
    bool alpha_blend;
};
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_PIPELINE_DATA_INCLUDE
