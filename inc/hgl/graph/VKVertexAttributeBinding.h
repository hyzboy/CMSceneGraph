#ifndef HGL_GRAPH_VULKAN_VERTEX_ATTRIBUTE_BINDING_INCLUDE
#define HGL_GRAPH_VULKAN_VERTEX_ATTRIBUTE_BINDING_INCLUDE

#include<hgl/graph/VKNamespace.h>
#include<hgl/graph/VertexAttrib.h>
#include<hgl/type/String.h>
#include<hgl/type/List.h>
VK_NAMESPACE_BEGIN

/**
* 顶点输入状态实例<br>
* 本对象用于传递给Material,用于已经确定好顶点格式的情况下，依然可修改部分设定(如instance)。
*/
class VertexAttributeBinding
{
public:

    struct VertexAttribute
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

    VertexAttribute *va_list;

private:

    friend class VertexShaderModule;

    VertexAttributeBinding(const int,const AnsiString **,const VertexAttribType *,VkVertexInputBindingDescription *,VkVertexInputAttributeDescription *);

public:

    ~VertexAttributeBinding();

    const int                                   GetIndex                (const AnsiString &name)const;

    const int                                   GetVertexAttrCount      ()const{return attr_count;}
    const AnsiString **                         GetVertexNameList       ()const{return name_list;}
    const VkVertexInputBindingDescription *     GetVertexBindingList    ()const{return binding_list;}
    const VkVertexInputAttributeDescription *   GetVertexAttributeList  ()const{return attribute_list;}

    const VkFormat      GetFormat   (const AnsiString &name)const
    {
        const int index=GetIndex(name);

        return index==-1?VK_FORMAT_UNDEFINED:attribute_list[index].format;
    }

    const VertexAttribute *GetVertexAttribute(const int index)const{return (index<0||index>=attr_count)?nullptr:va_list+index;}
    const VertexAttribute *GetVertexAttribute(const AnsiString &name)const{return GetVertexAttribute(GetIndex(name));}
};//class VertexAttributeBinding

using VAB=VertexAttributeBinding;
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_VERTEX_ATTRIBUTE_BINDING_INCLUDE
