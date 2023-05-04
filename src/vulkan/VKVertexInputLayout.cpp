#include<hgl/graph/VKVertexInputLayout.h>

VK_NAMESPACE_BEGIN
VertexInputLayout::VertexInputLayout(const uint32_t c,const char **nl,const VAT *tl)
{
    count=c;

    name_list=nl;
    type_list=tl;
    bind_list=new VkVertexInputBindingDescription[count];
    attr_list=new VkVertexInputAttributeDescription[count];

    vif_list=new VertexInputFormat[count];

    hgl_zero(count_by_group);
}

VertexInputLayout::~VertexInputLayout()
{
    delete[] vif_list;
    delete[] bind_list;
    delete[] attr_list;
}

const int VertexInputLayout::Comp(const VertexInputLayout *vil)const
{
    if(!vil)return(1);

    int result;

    result=count-vil->count;
    if(!result)return result;

    result=hgl_cmp(bind_list,vil->bind_list,count);
    if(!result)return result;

    result=hgl_cmp(attr_list,vil->attr_list,count);
    
    return(result);
}

const int VertexInputLayout::GetIndex(const AnsiString &name)const
{
    if(name.IsEmpty())return(-1);

    for(int i=0;i<count;i++)
        if(name.Comp(name_list[i])==0)
            return(i);

    return -1;
}
VK_NAMESPACE_END
