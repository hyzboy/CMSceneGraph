#ifndef HGL_VULKAN_VERTEX_INPUT_INCLUDE
#define HGL_VULKAN_VERTEX_INPUT_INCLUDE

#include<hgl/graph/VKFormat.h>
#include<hgl/graph/VKVertexInputLayout.h>
#include<hgl/type/SortedSets.h>
#include<hgl/type/Map.h>
#include<hgl/graph/VKShaderStage.h>

VK_NAMESPACE_BEGIN
class VILConfig;

class VertexInput
{
    ShaderAttributeArray shader_attr_list;
    VAT *type_list;
    const char **name_list;

    uint count_by_group[size_t(VertexInputGroup::RANGE_SIZE)];

private:
    
    SortedSets<VIL *> vil_sets;

public:

    VertexInput(const ShaderAttributeArray &);
    VertexInput(const VertexInput &)=delete;
    ~VertexInput();

    const uint      GetCount()const{return shader_attr_list.count;}

    VIL *           CreateVIL(const VILConfig *format_map=nullptr);
    bool            Release(VIL *);
    const uint32_t  GetInstanceCount()const{return vil_sets.GetCount();}
};//class VertexInput
VK_NAMESPACE_END
#endif//HGL_VULKAN_VERTEX_INPUT_INCLUDE
