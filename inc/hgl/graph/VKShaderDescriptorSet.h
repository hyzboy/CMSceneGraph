#ifndef HGL_VULKAN_SHADER_DESCRIPTR_SET_INCLUDE
#define HGL_VULKAN_SHADER_DESCRIPTR_SET_INCLUDE

#include<hgl/graph/VKNamespace.h>
#include<hgl/graph/VKDescriptorSetType.h>
#include<hgl/graph/VKShaderDescriptor.h>
#include<hgl/type/Map.h>

VK_NAMESPACE_BEGIN
struct ShaderDescriptorSet
{
    DescriptorSetType set_type;

    int set;
    int count;

    ObjectMap<AnsiString,ShaderDescriptor>  descriptor_map;

public:

    ShaderDescriptor *AddDescriptor(VkShaderStageFlagBits ssb,ShaderDescriptor *new_sd);                       ///<添加一个描述符，如果它本身存在，则返回false
};

using ShaderDescriptorSetArray=ShaderDescriptorSet[DESCRIPTOR_SET_TYPE_COUNT];
VK_NAMESPACE_END
#endif//HGL_VULKAN_SHADER_DESCRIPTR_SET_INCLUDE
