#ifndef HGL_VULKAN_VERTEX_INPUT_INCLUDE
#define HGL_VULKAN_VERTEX_INPUT_INCLUDE

#include<hgl/graph/VKFormat.h>
#include<hgl/graph/VKVertexInputLayout.h>
#include<hgl/type/SortedSets.h>
#include<hgl/graph/VKShaderStage.h>

VK_NAMESPACE_BEGIN
class VILConfig;

class VertexInputConfig
{
    VertexInputAttributeArray via_list;
    VAType *type_list;
    const char **name_list;

    uint count_by_group[size_t(VertexInputGroup::RANGE_SIZE)];

public:

    const uint      GetCount()const{return via_list.count;}

public:

    VertexInputConfig(const VertexInputAttributeArray &sa_array);
    ~VertexInputConfig();

    VIL *CreateVIL(const VILConfig *format_map=nullptr);
};

class VertexInput
{
    VertexInputConfig vic;

    VIL *default_vil;
    
    SortedSets<VIL *> vil_sets;

public:

    VertexInput(const VertexInputAttributeArray &);
    VertexInput(const VertexInput &)=delete;
    ~VertexInput();

    const uint      GetCount()const{return vic.GetCount();}

    const   VIL *   GetDefaultVIL()const{return default_vil;}
    VIL *           CreateVIL(const VILConfig *format_map=nullptr);
    bool            Release(VIL *);
    const uint32_t  GetInstanceCount()const{return vil_sets.GetCount();}
};//class VertexInput

VertexInput *GetVertexInput(const VertexInputAttributeArray &);
void ReleaseVertexInput(VertexInput *);
VK_NAMESPACE_END
#endif//HGL_VULKAN_VERTEX_INPUT_INCLUDE
