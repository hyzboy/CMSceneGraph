#ifndef HGL_GRAPH_VULKAN_STRUCT_INCLUDE
#define HGL_GRAPH_VULKAN_STRUCT_INCLUDE

#include<hgl/graph/vulkan/VKNamespace.h>
#include<string.h>

VK_NAMESPACE_BEGIN
template<typename T,VkStructureType ST> struct vkstruct:public T
{
public:

    vkstruct()
    {        
        this->sType = ST;
        this->pNext = nullptr;
    }
    ~vkstruct()=default;
};//

template<typename T,VkStructureType ST> struct vkstruct_flag:public T
{
public:

    vkstruct_flag()
    {        
        this->sType = ST;
        this->pNext = nullptr;
        this->flags = 0;
    }
    ~vkstruct_flag()=default;
};//

#define VKS_DEFINE(name,value)  using name=vkstruct<Vk##name,value>;
#define VKSF_DEFINE(name,value)  using name=vkstruct_flag<Vk##name,value>;

#define VKS_DEFINE_KHR(name,value)  using name=vkstruct<Vk##name##KHR,value>;
#define VKSF_DEFINE_KHR(name,value)  using name=vkstruct_flag<Vk##name##KHR,value>;

VKSF_DEFINE(    FramebufferCreateInfo,          VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO)

VKS_DEFINE(     WriteDescriptorSet,             VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET)
VKSF_DEFINE(    DescriptorSetLayoutCreateInfo,  VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO)
VKSF_DEFINE(    PipelineLayoutCreateInfo,       VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO)
VKS_DEFINE(     DescriptorSetAllocateInfo,      VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO)

VKS_DEFINE(     CommandBufferAllocateInfo,      VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO)
VKSF_DEFINE(    CommandBufferBeginInfo,         VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO)
VKS_DEFINE(     RenderPassBeginInfo,            VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO)

VKS_DEFINE_KHR( PresentInfo,                    VK_STRUCTURE_TYPE_PRESENT_INFO_KHR)

VKS_DEFINE(     SubmitInfo,                     VK_STRUCTURE_TYPE_SUBMIT_INFO)
VKS_DEFINE(     FenceCreateInfo,                VK_STRUCTURE_TYPE_FENCE_CREATE_INFO)
VKSF_DEFINE(    SemaphoreCreateInfo,            VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO)

VKSF_DEFINE(    SamplerCreateInfo,              VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO)

VKSF_DEFINE(    BufferCreateInfo,               VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO)

VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_STRUCT_INCLUDE
