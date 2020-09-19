#include<hgl/graph/vulkan/VKPipelineData.h>
#include<hgl/type/Map.h>

VK_NAMESPACE_BEGIN
PipelineData *LoadPipelineFromFile(const OSString &filename);

namespace
{
    MapObject<OSString,PipelineData> pipeline_data_by_filename;
}//namespace

PipelineData *GetPipelineData(const OSString &filename)
{
    const OSString fn=filename+OS_TEXT(".pipeline");
    
    PipelineData *pd;

    if(pipeline_data_by_filename.Get(fn,pd))
        return pd;

    pd=LoadPipelineFromFile(fn);

    //即便加载入失败了，也放入队列中。避免再次申请加载

    pipeline_data_by_filename.Add(fn,pd);

    return pd;
}
VK_NAMESPACE_END