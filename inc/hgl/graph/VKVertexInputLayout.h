#ifndef HGL_GRAPH_VULKAN_VERTEX_INPUT_LAYOUT_INCLUDE
#define HGL_GRAPH_VULKAN_VERTEX_INPUT_LAYOUT_INCLUDE

#include<hgl/graph/VKNamespace.h>
#include<hgl/graph/VertexAttrib.h>
#include<hgl/type/String.h>
#include<hgl/type/List.h>
VK_NAMESPACE_BEGIN

/**
* 顶点输入布局<br>
* 本对象用于传递给Material,用于已经确定好顶点格式的情况下，依然可修改部分设定(如instance)。
*/
class VertexInputLayout
{
public:

    struct VertexInputConfig
    {
        VkFormat    format;
        uint        vec_size;
        uint        stride;

        int         binding;
    };

private:

    int attr_count;
    const AnsiString **name_list;
    const VertexAttribType *type_list;
    VkVertexInputBindingDescription *binding_list;
    VkVertexInputAttributeDescription *attribute_list;

    VertexInputConfig *vic_list;

private:

    friend class VertexShaderModule;

    VertexInputLayout(const int,const AnsiString **,const VertexAttribType *,VkVertexInputBindingDescription *,VkVertexInputAttributeDescription *);

public:

    ~VertexInputLayout();

    const int                                   GetIndex          (const AnsiString &name)const;

    const int                                   GetAttrCount      ()const{return attr_count;}
    const AnsiString **                         GetNameList       ()const{return name_list;}
    const VkVertexInputBindingDescription *     GetBindingList    ()const{return binding_list;}
    const VkVertexInputAttributeDescription *   GetAttributeList  ()const{return attribute_list;}

    const VkFormat      GetFormat   (const AnsiString &name)const
    {
        const int index=GetIndex(name);

        return index==-1?VK_FORMAT_UNDEFINED:attribute_list[index].format;
    }

    const VertexInputConfig *GetConfig(const int index)const{return (index<0||index>=attr_count)?nullptr:vic_list+index;}
    const VertexInputConfig *GetConfig(const AnsiString &name)const{return GetConfig(GetIndex(name));}

    const int Comp(const VertexInputLayout *vil)const;

    CompOperator(const VertexInputLayout *,Comp)
};//class VertexInputLayout

using VIL=VertexInputLayout;
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_VERTEX_INPUT_LAYOUT_INCLUDE
