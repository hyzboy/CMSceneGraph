#ifndef HGL_GRAPH_VULKAN_DESCRIPTOR_SET_TYPE_INCLUDE
#define HGL_GRAPH_VULKAN_DESCRIPTOR_SET_TYPE_INCLUDE

#include<hgl/graph/VKNamespace.h>
#include<hgl/TypeFunc.h>

VK_NAMESPACE_BEGIN
enum class DescriptorSetType
{
    //设计使其对应shader中的set
    
    Global=0,           ///<全局参数(如太阳光等)
    PerFrame,           ///<帧参数(如摄像机等)
    PerMaterialInstance,///<材质实例参数(如纹理等)
    PerObject,          ///<对象参数(如模型矩阵等)

    Instance,
    Skeleton,

    ENUM_CLASS_RANGE(Global,Skeleton)
};//

constexpr char *DescriptSetTypeName[]=
{
    "Global","PerFrame","PerMaterialInstance","PerObject","Instance","Skeleton"
};

inline const char *GetDescriptorSetTypeName(const enum class DescriptorSetType &type)
{
    RANGE_CHECK_RETURN_NULLPTR(type);

    return DescriptSetTypeName[(size_t)type];
}
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_DESCRIPTOR_SET_TYPE_INCLUDE
