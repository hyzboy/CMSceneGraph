#ifndef HGL_GRAPH_VULKAN_DESCRIPTOR_SET_TYPE_INCLUDE
#define HGL_GRAPH_VULKAN_DESCRIPTOR_SET_TYPE_INCLUDE

#include<hgl/graph/VKNamespace.h>
#include<hgl/TypeFunc.h>

VK_NAMESPACE_BEGIN

/**
* 描述符集类型
*/
enum class DescriptorSetType
{
    // 设计使其对应shader中的set
    // 
    // 我们按更新频率将descriptor分类到不同的set
    // 减少每一次draw之前bind的数量
    // 
    // 如果set标记错误会导致descriptor不会得到更新
    
    Global=0,           ///<全局参数，不确定什么时候更新，但一般不怎么更新(如视窗大小，太阳光等), 不会在RenderList中处理刷新

    PerFrame,           ///<帧参数，固定每帧刷新一次(如摄像机位置等)

    /// <summary>
    /// 材质参数配置在MaterialInstance中，此类信息会独立一个ubo struct，并成为一个结构。由RenderList归类整理一个MaterialInstanceID的数组走顶点流传入Shader。如
    /// 
    /// layout(location = ? ) in uint MaterialID;
    /// 
    /// struct MaterialInstance
    /// {
    ///     vec3 color;
    ///     float metallic;
    ///     float roughness;
    ///     float ao;
    ///     vec3 emissive;
    /// };
    /// 
    /// uniform Material
    /// {
    ///     MaterialInstance mi[1024];
    /// }mtl;
    /// 
    /// void main()
    /// {
    ///     MaterialInstance mi=mtl.mi[MaterialID];
    ///     ...
    /// }
    /// 
    /// </summary>
    PerMaterial,        ///<材质参数

    Instance,

    ENUM_CLASS_RANGE(Global,Instance)
};//

constexpr const size_t DESCRIPTOR_SET_TYPE_COUNT=size_t(DescriptorSetType::RANGE_SIZE);

constexpr char *DescriptSetTypeName[]=
{
    "Global",
    "PerFrame",
    "PerMaterial",
    "Instance"
};

inline const char *GetDescriptorSetTypeName(const enum class DescriptorSetType &type)
{
    RANGE_CHECK_RETURN_NULLPTR(type);

    return DescriptSetTypeName[(size_t)type];
}
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_DESCRIPTOR_SET_TYPE_INCLUDE
