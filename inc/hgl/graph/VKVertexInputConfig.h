#ifndef HGL_GRAPH_VULKAN_VERTEX_INPUT_CONFIG_INCLUDE
#define HGL_GRAPH_VULKAN_VERTEX_INPUT_CONFIG_INCLUDE

#include<hgl/graph/VKFormat.h>
#include<hgl/type/String.h>
#include<hgl/type/Map.h>

VK_NAMESPACE_BEGIN
struct VAConfig
{
    VkFormat format;
    VkVertexInputRate input_rate;

public:

    VAConfig()
    {
        format=PF_UNDEFINED;
        input_rate=VK_VERTEX_INPUT_RATE_VERTEX;
    }

    VAConfig(const VkFormat fmt,const VkVertexInputRate ir=VK_VERTEX_INPUT_RATE_VERTEX)
    {
        format=fmt;
        input_rate=ir;
    }

    CompOperatorMemcmp(const VAConfig &);
};

class VILConfig:public Map<AnsiString,VAConfig>
{
public:

    using Map<AnsiString,VAConfig>::Map;

    bool Add(const AnsiString &name,const VkFormat fmt,const VkVertexInputRate ir=VK_VERTEX_INPUT_RATE_VERTEX)
    {
        if(ContainsKey(name))
            return(false);

        return Map<AnsiString,VAConfig>::Add(name,VAConfig(fmt,ir));
    }

    int Comp(const VILConfig &vc)const
    {
        int off;

        off=GetCount()-vc.GetCount();
        if(off)return(off);

        auto **sp=GetDataList();
        VAConfig vac;

        for(int i=0;i<GetCount();i++)
        {
            if(!vc.Get((*sp)->key,vac))
                return(1);

            off=(*sp)->value._Comp(vac);
            if(off)return(off);

            ++sp;
        }

        return 0;
    }

    CompOperator(const VILConfig &,Comp)
};//class VILConfig:public Map<AnsiString,VAConfig>
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_VERTEX_INPUT_CONFIG_INCLUDE
