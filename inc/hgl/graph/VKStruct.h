#ifndef HGL_GRAPH_VULKAN_STRUCT_INCLUDE
#define HGL_GRAPH_VULKAN_STRUCT_INCLUDE

#include<hgl/graph/VKNamespace.h>

VK_NAMESPACE_BEGIN
template<typename T,VkStructureType ST> struct vkstruct:public T
{
public:

    vkstruct()
    {
        this->sType = ST;
        this->pNext = nullptr;
    }

    virtual ~vkstruct()=default;
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

    vkstruct_flag(VkFlags flags)
    {
        this->sType = ST;
        this->pNext = nullptr;
        this->flags = flags;
    }

    virtual ~vkstruct_flag()=default;
};//

#define VKS_DEFINE(name,value)  using name=vkstruct<Vk##name,value>;
#define VKSF_DEFINE(name,value)  using name=vkstruct_flag<Vk##name,value>;

#define VKS_DEFINE_KHR(name,value)  using name=vkstruct<Vk##name##KHR,value>;
#define VKSF_DEFINE_KHR(name,value)  using name=vkstruct_flag<Vk##name##KHR,value>;

VKS_DEFINE(     ApplicationInfo,                VK_STRUCTURE_TYPE_APPLICATION_INFO)

struct InstanceCreateInfo:public vkstruct_flag<VkInstanceCreateInfo,VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO>
{
public:

    InstanceCreateInfo(VkApplicationInfo *ai)
    {
        this->pApplicationInfo=ai;
    }
};

VKSF_DEFINE(    FramebufferCreateInfo,          VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO)

VKSF_DEFINE(    DescriptorSetLayoutCreateInfo,  VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO)
VKSF_DEFINE(    PipelineLayoutCreateInfo,       VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO)
VKS_DEFINE(     DescriptorSetAllocateInfo,      VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO)

VKS_DEFINE(     CommandBufferAllocateInfo,      VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO)
VKSF_DEFINE(    CommandBufferBeginInfo,         VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO)
VKS_DEFINE(     RenderPassBeginInfo,            VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO)

VKS_DEFINE_KHR( PresentInfo,                    VK_STRUCTURE_TYPE_PRESENT_INFO_KHR)

VKS_DEFINE(     SubmitInfo,                     VK_STRUCTURE_TYPE_SUBMIT_INFO)
VKSF_DEFINE(    FenceCreateInfo,                VK_STRUCTURE_TYPE_FENCE_CREATE_INFO)
VKSF_DEFINE(    SemaphoreCreateInfo,            VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO)

VKSF_DEFINE(    SamplerCreateInfo,              VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO)

VKSF_DEFINE(    BufferCreateInfo,               VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO)
VKSF_DEFINE(    ImageViewCreateInfo,            VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO)

struct ImageMemoryBarrier:public vkstruct<VkImageMemoryBarrier,VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER>
{
public:

    ImageMemoryBarrier(VkImage img)
    {
        this->image=img;
    }
};//struct ImageMemoryBarrier:public vkstruct<VkImageMemoryBarrier,VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER>

struct SubpassDescription:public VkSubpassDescription
{
public:

    SubpassDescription(const VkAttachmentReference *color_ref_list,const uint32_t color_count,const VkAttachmentReference *depth_ref=nullptr)
    {
        flags                    =0;
        pipelineBindPoint        =VK_PIPELINE_BIND_POINT_GRAPHICS;
        inputAttachmentCount     =0;
        pInputAttachments        =nullptr;

	    pColorAttachments        =color_ref_list;
        colorAttachmentCount     =color_count;

        pDepthStencilAttachment  =depth_ref;

        pResolveAttachments      =nullptr;
        preserveAttachmentCount  =0;
        pPreserveAttachments     =nullptr;
    }

    SubpassDescription(const VkAttachmentReference *color_ref,const VkAttachmentReference *depth_ref=nullptr):SubpassDescription(color_ref,1,depth_ref){}
    ~SubpassDescription()=default;
};//

struct PipelineShaderStageCreateInfo:public vkstruct_flag<VkPipelineShaderStageCreateInfo,VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO>
{
public:

    PipelineShaderStageCreateInfo(VkShaderStageFlagBits bits)
    {    
        pSpecializationInfo =nullptr;
        stage               =bits;
        module              =nullptr;
        pName               ="main";
    }
};
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_STRUCT_INCLUDE
