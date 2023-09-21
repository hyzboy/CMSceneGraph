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

/**
* <summary>
* 
*    layout(location=?) in uint MaterialInstanceID
*
*    #define MI_MAX_COUNT ???                //该值由引擎根据 UBORange/sizeof(MaterialInstance) 计算出来
*
*    struct MaterialInstance                 //这部分数据，即为材质实例的具体数据，每一个材质实例类负责提供具体数据。由RenderList合并成一整个UBO
*    {                                       //该类数据，由DescriptorSetType为PerMaterial的参数构成
*        vec4 BaseColor;
*        vec4 Emissive;
*        vec4 ARM;
*    };
*
*    layout(set=?,binding=?) uniform Material
*    {
*        MaterialInstance mi[MI_MAX_COUNT]
*    }mtl;
*
*    void main()
*    {
*        MaterialInstance mi=mtl.mi[(MaterialInstanceID>=MI_MAX_COUNT)?:0:MaterialInstanceID];   //如果超出范围则使用0号材质实例数据
*
*        vec4 BaseColor  =mi.BaseColor;
*        vec4 Emissive   =mi.Emissive;
*
*        float AO        =mi.ARM.x;
*        float Roughness =mi.ARM.y;
*        float Metallic  =mi.ARM.z;
*
* </summary>
*/
    PerMaterial,        ///<材质参数
    MaterialInstance,   ///<材质实例

    Instance,

    ENUM_CLASS_RANGE(Global,Instance)
};//

constexpr const size_t DESCRIPTOR_SET_TYPE_COUNT=size_t(DescriptorSetType::RANGE_SIZE);

constexpr char *DescriptSetTypeName[]=
{
    "Global",
    "PerFrame",
    "PerMaterial",
    "MaterialInstance",
    "Instance"
};

inline const char *GetDescriptorSetTypeName(const enum class DescriptorSetType &type)
{
    RANGE_CHECK_RETURN_NULLPTR(type);

    return DescriptSetTypeName[(size_t)type];
}
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_DESCRIPTOR_SET_TYPE_INCLUDE
