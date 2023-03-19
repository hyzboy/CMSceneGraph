#include<hgl/graph/VKVertexInput.h>
#include<hgl/graph/VKVertexInputConfig.h>

VK_NAMESPACE_BEGIN
VertexInput::VertexInput(const ShaderAttributeArray &sa_array)
{
    Copy(&shader_attr_list,&sa_array);

    name_list=new const char *[shader_attr_list.count];
    type_list=new VAT[shader_attr_list.count];

    const ShaderAttribute *sa=shader_attr_list.items;
    
    for(uint i=0;i<shader_attr_list.count;i++)
    {
        name_list[i]            =sa->name;
        type_list[i].basetype   =VATBaseType(sa->basetype);
        type_list[i].vec_size   =sa->vec_size;

        ++sa;
    }
}

VertexInput::~VertexInput()
{
    if(vil_sets.GetCount()>0)
    {
        //还有在用的，这是个错误
    }

    Clear(&shader_attr_list);

    delete[] name_list;
    delete[] type_list;
}

VIL *VertexInput::CreateVIL(const VILConfig *cfg)
{
    VkVertexInputBindingDescription *binding_list=new VkVertexInputBindingDescription[shader_attr_list.count];
    VkVertexInputAttributeDescription *attribute_list=new VkVertexInputAttributeDescription[shader_attr_list.count];

    VkVertexInputBindingDescription *bind_desc=binding_list;
    VkVertexInputAttributeDescription *attr_desc=attribute_list;

    const ShaderAttribute *sa=shader_attr_list.items;
    VAConfig vac;

    for(uint i=0;i<shader_attr_list.count;i++)
    {
        //binding对应的是第几个数据输入流
        //实际使用一个binding可以绑定多个attrib
        //比如在一个流中传递{pos,color}这样两个数据，就需要两个attrib
        //但在我们的设计中，仅支持一个流传递一个attrib

        attr_desc->binding   =i;
        attr_desc->location  =sa->location;                 //此值对应shader中的layout(location=
        
        attr_desc->offset    =0;

        bind_desc->binding   =i;                            //binding对应在vkCmdBindVertexBuffer中设置的缓冲区的序列号，所以这个数字必须从0开始，而且紧密排列。
                                                            //在Renderable类中，buffer_list必需严格按照本此binding为序列号排列

        if(!cfg||!cfg->Get(sa->name,vac))
        {
            attr_desc->format    =GetVulkanFormat(sa);

            //if(memcmp((*sa)->name.c_str(),"Inst_",5)==0)                //不可以使用CaseComp("Inst_",5)会被认为是比较一个5字长的字符串，而不是只比较5个字符
            //    bind_desc->inputRate =VK_VERTEX_INPUT_RATE_INSTANCE;
            //else
                bind_desc->inputRate =VK_VERTEX_INPUT_RATE_VERTEX;
        }
        else
        {
            if(vac.format!=PF_UNDEFINED)
                attr_desc->format    =vac.format;
            else                
                attr_desc->format    =GetVulkanFormat(sa);

            bind_desc->inputRate =vac.instance?VK_VERTEX_INPUT_RATE_INSTANCE:VK_VERTEX_INPUT_RATE_VERTEX;
        }

        bind_desc->stride    =GetStrideByFormat(attr_desc->format);

        ++attr_desc;
        ++bind_desc;

        ++sa;
    }

    VIL *vil=new VIL(shader_attr_list.count,name_list,type_list,binding_list,attribute_list);

    vil_sets.Add(vil);

    return(vil);
}

bool VertexInput::Release(VIL *vil)
{
    return vil_sets.Delete(vil);
}
VK_NAMESPACE_END
