#include<hgl/graph/VKVertexInput.h>
#include<hgl/graph/VKVertexInputConfig.h>
#include<hgl/graph/VKRenderAssign.h>
#include<hgl/type/ObjectManage.h>

VK_NAMESPACE_BEGIN
VertexInput::VertexInput(const ShaderAttributeArray &sa_array)
{
    Copy(&shader_attr_list,&sa_array);

    name_list=new const char *[shader_attr_list.count];
    type_list=new VAT[shader_attr_list.count];

    const ShaderAttribute *sa=shader_attr_list.items;

    hgl_zero(count_by_group);
    
    for(uint i=0;i<shader_attr_list.count;i++)
    {
        name_list[i]            =sa->name;
        type_list[i].basetype   =VATBaseType(sa->basetype);
        type_list[i].vec_size   =sa->vec_size;

        count_by_group[size_t(sa->group)]++;

        ++sa;
    }

    default_vil=CreateVIL(nullptr);
}

VertexInput::~VertexInput()
{
    delete default_vil;

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
    if(!cfg)
        return(default_vil);

    VIL *vil=new VIL(shader_attr_list.count,name_list,type_list);

    VkVertexInputBindingDescription *bind_desc=vil->bind_list;
    VkVertexInputAttributeDescription *attr_desc=vil->attr_list;
    VertexInputFormat *vif=vil->vif_list;

    const ShaderAttribute *sa;
    VAConfig vac;
    uint binding=0;

    hgl_cpy(vil->count_by_group,count_by_group);

    for(uint group=0;group<uint(VertexInputGroup::RANGE_SIZE);group++)
    {
        vil->vif_list_by_group[group]=vif;
        vil->first_binding[group]=binding;

        sa=shader_attr_list.items;

        for(uint i=0;i<shader_attr_list.count;i++)
        {
            if(uint(sa->group)!=group)
            {
                ++sa;
                continue;
            }

            //binding对应的是第几个数据输入流
            //实际使用一个binding可以绑定多个attrib
            //比如在一个流中传递{pos,color}这样两个数据，就需要两个attrib
            //但在我们的设计中，仅支持一个流传递一个attrib

            attr_desc->binding   =binding;
            attr_desc->location  =sa->location;                 //此值对应shader中的layout(location=
        
            attr_desc->offset    =0;

            bind_desc->binding   =binding;                      //binding对应在vkCmdBindVertexBuffer中设置的缓冲区的序列号，所以这个数字必须从0开始，而且紧密排列。
                                                                //在Renderable类中，buffer_list必需严格按照本此binding为序列号排列

            ++binding;

            if(group==uint(VertexInputGroup::JointID))
            {
                attr_desc->format   =VK_FORMAT_R8G8B8A8_UINT;

                bind_desc->inputRate=VK_VERTEX_INPUT_RATE_VERTEX;
                bind_desc->stride   =4;
            }
            else
            if(group==uint(VertexInputGroup::JointWeight))
            {
                attr_desc->format   =VK_FORMAT_R8G8B8A8_UNORM;

                bind_desc->inputRate=VK_VERTEX_INPUT_RATE_VERTEX;
                bind_desc->stride   =4;
            }
            else
            if(group==uint(VertexInputGroup::Assign))
            {
                attr_desc->format   =ASSIGN_VBO_FMT;
                bind_desc->inputRate=VK_VERTEX_INPUT_RATE_INSTANCE;
                bind_desc->stride   =ASSIGN_VBO_STRIDE_BYTES;
            }
            else
            {
                if(!cfg||!cfg->Get(sa->name,vac))
                {
                    attr_desc->format    =GetVulkanFormat(sa);

                    bind_desc->inputRate =VkVertexInputRate(sa->input_rate);
                }
                else
                {
                    attr_desc->format    =(vac.format==PF_UNDEFINED?GetVulkanFormat(sa):vac.format);

                    bind_desc->inputRate =vac.input_rate;
                }

                bind_desc->stride    =GetStrideByFormat(attr_desc->format);
            }

            vif->format     =attr_desc->format;
            vif->vec_size   =sa->vec_size;
            vif->stride     =bind_desc->stride;

            vif->name       =sa->name;
            vif->binding    =attr_desc->binding;
            vif->input_rate =bind_desc->inputRate;
            vif->group      =sa->group;

            ++vif;
            ++attr_desc;
            ++bind_desc;

            ++sa;
        }
    }

    vil_sets.Add(vil);

    return(vil);
}

bool VertexInput::Release(VIL *vil)
{
    return vil_sets.Delete(vil);
}

namespace
{
    ObjectManage<ShaderAttributeArray,VertexInput> vertex_input_manager;

    //完全没必要的管理

    //ShaderAttributeArray+VertexInput 就算有1024个，也没多少内存占用。完全没必要搞什么引用计数管理
}//namespace

VertexInput *GetVertexInput(const ShaderAttributeArray &saa)
{
    VertexInput *vi=vertex_input_manager.Get(saa);

    if(!vi)
    {
        vi=new VertexInput(saa);

        vertex_input_manager.Add(saa,vi);
    }

    return vi;
}

void ReleaseVertexInput(VertexInput *vi)
{
    if(!vi)return;

    vertex_input_manager.Release(vi);
}
VK_NAMESPACE_END
