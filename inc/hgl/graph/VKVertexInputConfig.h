#ifndef HGL_GRAPH_VULKAN_VERTEX_INPUT_CONFIG_INCLUDE
#define HGL_GRAPH_VULKAN_VERTEX_INPUT_CONFIG_INCLUDE

#include<hgl/graph/VKFormat.h>
#include<hgl/type/String.h>
#include<hgl/type/Map.h>

VK_NAMESPACE_BEGIN
struct VAConfig
{
    VkFormat format;
    bool instance;

public:

    VAConfig()
    {
        format=PF_UNDEFINED;
        instance=false;
    }

    VAConfig(const VkFormat fmt,bool inst=false)
    {
        format=fmt;
        instance=inst;
    }

    CompOperatorMemcmp(const VAConfig &);
};

class VILConfig:public Map<AnsiString,VAConfig>
{
public:

    using Map<AnsiString,VAConfig>::Map;

    bool Add(const AnsiString &name,const VkFormat fmt,const bool inst=false)
    {
        return Map<AnsiString,VAConfig>::Add(name,VAConfig(fmt,inst));
    }
};
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_VERTEX_INPUT_CONFIG_INCLUDE