#include<hgl/graph/VKVertexAttributeBinding.h>

VK_NAMESPACE_BEGIN
VertexAttributeBinding::VertexAttributeBinding(const int count,const AnsiString **nl,const VertexAttribType *vat,VkVertexInputBindingDescription *bind_list,VkVertexInputAttributeDescription *attr_list)
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
}

VertexAttributeBinding::~VertexAttributeBinding()
{
    SAFE_CLEAR_ARRAY(binding_list);
    SAFE_CLEAR_ARRAY(attribute_list);
}

const int VertexAttributeBinding::GetIndex(const AnsiString &name)const
{
    if(name.IsEmpty())return(-1);

    for(int i=0;i<attr_count;i++)
        if(name==*(name_list[i]))
            return(i);

    return -1;
}

VK_NAMESPACE_END
