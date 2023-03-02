#include<hgl/graph/VKVertexInputLayout.h>

VK_NAMESPACE_BEGIN
VertexInputLayout::VertexInputLayout(const int count,const char **nl,const VertexAttribType *vat,VkVertexInputBindingDescription *bind_list,VkVertexInputAttributeDescription *attr_list)
{
    attr_count=count;
    name_list=nl;

    if(attr_count<=0)
    {
        binding_list=nullptr;
        attribute_list=nullptr;
        type_list=nullptr;
        return;
    }

    binding_list=bind_list;
    attribute_list=attr_list;
    type_list=vat;

    vic_list=new VertexInputConfig[attr_count];
    VertexInputConfig *va=vic_list;

    for(int i=0;i<attr_count;i++)
    {
        va->format  =attribute_list[i].format;
        va->binding =attribute_list[i].binding;
        va->vec_size=vat[i].vec_size;
        va->stride  =binding_list[i].stride;

        ++va;
    }
}

VertexInputLayout::~VertexInputLayout()
{
    delete[] vic_list;
    SAFE_CLEAR_ARRAY(binding_list);
    SAFE_CLEAR_ARRAY(attribute_list);
}

const int VertexInputLayout::GetIndex(const AnsiString &name)const
{
    if(name.IsEmpty())return(-1);

    for(int i=0;i<attr_count;i++)
        if(name.Comp(name_list[i])==0)
            return(i);

    return -1;
}

const int VertexInputLayout::Comp(const VertexInputLayout *vil)const
{
    if(!vil)return(1);

    int result;

    result=attr_count-vil->attr_count;
    if(!result)return result;

    result=memcmp(binding_list,vil->binding_list,attr_count*sizeof(VkVertexInputBindingDescription));
    if(!result)return result;

    result=memcmp(attribute_list,vil->attribute_list,attr_count*sizeof(VkVertexInputAttributeDescription));
    
    return(result);
}
VK_NAMESPACE_END
