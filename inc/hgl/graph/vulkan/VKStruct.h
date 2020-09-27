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

    vkstruct_flag(VkFlags flags)
    {        
        this->sType = ST;
        this->pNext = nullptr;
        this->flags = flags;
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
VKSF_DEFINE(    FenceCreateInfo,                VK_STRUCTURE_TYPE_FENCE_CREATE_INFO)
VKSF_DEFINE(    SemaphoreCreateInfo,            VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO)

VKSF_DEFINE(    SamplerCreateInfo,              VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO)

VKSF_DEFINE(    BufferCreateInfo,               VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO)
VKSF_DEFINE(    ImageViewCreateInfo,            VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO)
VKSF_DEFINE(    ImageCreateInfo,                VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO)

struct Image1DCreateInfo:public ImageCreateInfo
{
public:

    Image1DCreateInfo()
    {
        this->imageType=VK_IMAGE_TYPE_1D;
    }

    Image1DCreateInfo(const VkFormat &fmt,const uint32_t length)
    {
        this->format        =fmt;
        this->imageType     =VK_IMAGE_TYPE_1D;
        this->extent.width  =length;
        this->extent.height =1;
        this->extent.depth  =1;
        this->arrayLayers   =1;
    }

    ~Image1DCreateInfo()=default;
};//

struct Image1DArrayCreateInfo:public ImageCreateInfo
{
public:

    Image1DArrayCreateInfo()
    {
        this->imageType=VK_IMAGE_TYPE_1D;
    }

    Image1DArrayCreateInfo(const VkFormat &fmt,const uint32_t length,const uint32_t layers)
    {
        this->format        =fmt;
        this->imageType     =VK_IMAGE_TYPE_1D;
        this->extent.width  =length;
        this->extent.height =1;
        this->extent.depth  =1;
        this->arrayLayers   =layers;
    }

    ~Image1DArrayCreateInfo()=default;
};//

struct Image2DCreateInfo:public ImageCreateInfo
{
public:

    Image2DCreateInfo()
    {
        this->imageType=VK_IMAGE_TYPE_2D;
    }

    Image2DCreateInfo(const VkFormat &fmt,const uint32_t w,const uint32_t h)
    {
        this->format        =fmt;
        this->imageType     =VK_IMAGE_TYPE_2D;
        this->extent.width  =w;
        this->extent.height =h;
        this->extent.depth  =1;
        this->arrayLayers   =1;
    }

    Image2DCreateInfo(const VkFormat &fmt,const VkExtent3D &extent)
    {
        this->format        =fmt;
        this->imageType     =VK_IMAGE_TYPE_2D;
        this->extent        =extent;
        this->arrayLayers   =1;
    }

    ~Image2DCreateInfo()=default;
};//

struct Image2DArrayCreateInfo:public ImageCreateInfo
{
public:

    Image2DArrayCreateInfo()
    {
        this->imageType=VK_IMAGE_TYPE_2D;
    }

    Image2DArrayCreateInfo(const VkFormat &fmt,const uint32_t w,const uint32_t h,const uint32_t layers)
    {
        this->format        =fmt;
        this->imageType     =VK_IMAGE_TYPE_2D;
        this->extent.width  =w;
        this->extent.height =h;
        this->extent.depth  =1;
        this->arrayLayers   =layers;
    }

    Image2DArrayCreateInfo(const VkFormat &fmt,const VkExtent3D &extent,const uint32_t layers)
    {
        this->format        =fmt;
        this->imageType     =VK_IMAGE_TYPE_2D;
        this->extent        =extent;
        this->arrayLayers   =layers;
    }

    ~Image2DArrayCreateInfo()=default;
};//

struct Image3DCreateInfo:public ImageCreateInfo
{
public:

    Image3DCreateInfo()
    {
        this->imageType=VK_IMAGE_TYPE_3D;
    }

    Image3DCreateInfo(const VkFormat &fmt,const VkExtent3D &extent)
    {
        this->format        =fmt;
        this->imageType     =VK_IMAGE_TYPE_3D;
        this->extent        =extent;
        this->arrayLayers   =1;
    }

    ~Image3DCreateInfo()=default;
};//

struct ImageCubemapCreateInfo:public ImageCreateInfo
{
public:

    ImageCubemapCreateInfo():ImageCreateInfo(VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT)
    {
        this->imageType=VK_IMAGE_TYPE_2D;
    }

    ImageCubemapCreateInfo(const VkFormat &fmt,const uint32_t w,const uint32_t h):ImageCreateInfo(VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT)
    {
        this->format        =fmt;
        this->imageType     =VK_IMAGE_TYPE_2D;
        this->extent.width  =w;
        this->extent.height =h;
        this->extent.depth  =1;
        this->arrayLayers   =6;
    }

    ImageCubemapCreateInfo(const VkFormat &fmt,const VkExtent3D &extent):ImageCreateInfo(VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT)
    {
        this->format        =fmt;
        this->imageType     =VK_IMAGE_TYPE_2D;
        this->extent        =extent;
        this->arrayLayers   =6;
    }

    ~ImageCubemapCreateInfo()=default;
};//
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_STRUCT_INCLUDE
