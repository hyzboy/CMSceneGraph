#include<hgl/graph/VKVertexInputLayout.h>

VK_NAMESPACE_BEGIN
VertexInputLayout::VertexInputLayout(const uint32_t c)
{
    count=c;

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

const int VertexInputLayout::compare(const VertexInputLayout &vil)const
{
    int result;

    result=count-vil.count;
    if(result)return result;

    result=hgl_cmp(bind_list,vil.bind_list,count);
    if(result)return result;

    result=hgl_cmp(attr_list,vil.attr_list,count);
    
    return(result);
}

const int VertexInputLayout::GetIndex(const AnsiString &name)const
{
    if(name.IsEmpty())return(-1);

    for(int i=0;i<count;i++)
        if(name.Comp(vif_list[i].name)==0)
            return(i);

    return -1;
}
VK_NAMESPACE_END
