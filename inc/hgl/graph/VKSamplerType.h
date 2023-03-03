#ifndef HGL_VULKAN_SAMPLER_TYPE_INCLUDE
#define HGL_VULKAN_SAMPLER_TYPE_INCLUDE

#include<hgl/graph/VKNamespace.h>
#include<hgl/TypeFunc.h>
#include<hgl/type/StrChar.h>

VK_NAMESPACE_BEGIN
enum class SamplerType
{
    Error,

    Sampler1D,
    Sampler2D,
    Sampler3D,
    SamplerCube,

    Sampler1DArray,
    Sampler2DArray,
    SamplerCubeArray,

    Sampler2DMS,
    Sampler2DMSArray,

    Sampler1DShadow,
    Sampler2DShadow,
    SamplerCubeShadow,

    Sampler1DArrayShadow,
    Sampler2DArrayShadow,
    SamplerCubeArrayShadow,

    ENUM_CLASS_RANGE(Sampler1D,SamplerCubeArrayShadow)
};

constexpr const char *SamplerTypeName[]=
{
    "samplerError",

    "sampler1D",
    "sampler2D",
    "sampler3D",
    "samplerCube",

    "sampler1DArray",
    "sampler2DArray",
    "samplerCubeArray",

    "sampler2DMS",
    "sampler2DMSArray",

    "sampler1DShadow",
    "sampler2DShadow",
    "samplerCubeShadow",

    "sampler1DArrayShadow",
    "sampler2DArrayShadow",
    "samplerCubeArrayShadow",
};

inline constexpr const char *GetSamplerTypeName(const SamplerType st)
{
    return SamplerTypeName[static_cast<int>(st)];
}

inline const SamplerType ParseSamplerType(const char *name)
{
    int result=hgl::find_str_in_array<char>((int)SamplerType::RANGE_SIZE,(const char **)SamplerTypeName,name);

    if(result<=0||result>(int)SamplerType::END_RANGE)
        return SamplerType::Error;

    return (SamplerType)result;
}

constexpr const VkImageViewType SamplerImageViewType[]=
{
    VK_IMAGE_VIEW_TYPE_1D,
    VK_IMAGE_VIEW_TYPE_2D,
    VK_IMAGE_VIEW_TYPE_3D,
    VK_IMAGE_VIEW_TYPE_CUBE,

    VK_IMAGE_VIEW_TYPE_1D_ARRAY,
    VK_IMAGE_VIEW_TYPE_2D_ARRAY,
    VK_IMAGE_VIEW_TYPE_CUBE_ARRAY,

    VK_IMAGE_VIEW_TYPE_2D,
    VK_IMAGE_VIEW_TYPE_2D_ARRAY,

    VK_IMAGE_VIEW_TYPE_1D,
    VK_IMAGE_VIEW_TYPE_2D,
    VK_IMAGE_VIEW_TYPE_CUBE,

    VK_IMAGE_VIEW_TYPE_1D_ARRAY,
    VK_IMAGE_VIEW_TYPE_2D_ARRAY,
    VK_IMAGE_VIEW_TYPE_CUBE_ARRAY,
};

inline constexpr VkImageViewType GetSamplerImageViewType(const SamplerType st)
{
    return SamplerImageViewType[static_cast<int>(st)];
}

VK_NAMESPACE_END
#endif//HGL_VULKAN_SAMPLER_TYPE_INCLUDE