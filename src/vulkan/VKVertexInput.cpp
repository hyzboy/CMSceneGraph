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
        //�������õģ����Ǹ�����
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
        //binding��Ӧ���ǵڼ�������������
        //ʵ��ʹ��һ��binding���԰󶨶��attrib
        //������һ�����д���{pos,color}�����������ݣ�����Ҫ����attrib
        //�������ǵ�����У���֧��һ��������һ��attrib

        attr_desc->binding   =i;
        attr_desc->location  =sa->location;                 //��ֵ��Ӧshader�е�layout(location=
        
        attr_desc->offset    =0;

        bind_desc->binding   =i;                            //binding��Ӧ��vkCmdBindVertexBuffer�����õĻ����������кţ�����������ֱ����0��ʼ�����ҽ������С�
                                                            //��Renderable���У�buffer_list�����ϸ��ձ���bindingΪ���к�����

        if(!cfg||!cfg->Get(sa->name,vac))
        {
            attr_desc->format    =GetVulkanFormat(sa);

            //if(memcmp((*sa)->name.c_str(),"Inst_",5)==0)                //������ʹ��CaseComp("Inst_",5)�ᱻ��Ϊ�ǱȽ�һ��5�ֳ����ַ�����������ֻ�Ƚ�5���ַ�
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
