#include<hgl/graph/vulkan/VKPipelineData.h>
#include<hgl/graph/vulkan/VKInlinePipeline.h>
#include<hgl/type/Map.h>

VK_NAMESPACE_BEGIN
PipelineData *LoadPipelineFromFile(const OSString &filename);

namespace
{
    MapObject<InlinePipeline,PipelineData> inline_pipeline_data;

    MapObject<OSString,PipelineData> pipeline_data_by_filename;

    void InitInlinePipelineData()
    {
        PipelineData *pd;
        
        {
            pd=new PipelineData(1);
            inline_pipeline_data.Add(InlinePipeline::Solid3D,pd);
        }

        {
            pd=new PipelineData(1);
            pd->OpenBlend(0);
            pd->SetColorBlend(0,VK_BLEND_OP_ADD,VK_BLEND_FACTOR_SRC_ALPHA,VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA);
            pd->SetAlphaBlend(0,VK_BLEND_OP_ADD,VK_BLEND_FACTOR_ONE,VK_BLEND_FACTOR_ZERO);
            inline_pipeline_data.Add(InlinePipeline::Alpha3D,pd);
        }

        {
            pd=new PipelineData(1);
            pd->CloseCullFace();
            pd->SetDepthTest(false);
            pd->SetDepthWrite(false);
            inline_pipeline_data.Add(InlinePipeline::Solid2D,pd);
        }

        {
            pd=new PipelineData(1);
            pd->CloseCullFace();
            pd->SetDepthTest(false);
            pd->SetDepthWrite(false);
            pd->OpenBlend(0);
            pd->SetColorBlend(0,VK_BLEND_OP_ADD,VK_BLEND_FACTOR_SRC_ALPHA,VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA);
            pd->SetAlphaBlend(0,VK_BLEND_OP_ADD,VK_BLEND_FACTOR_ONE,VK_BLEND_FACTOR_ZERO);
            inline_pipeline_data.Add(InlinePipeline::Alpha2D,pd);
        }

        {
            pd=new PipelineData(1);
            pd->CloseCullFace();
            inline_pipeline_data.Add(InlinePipeline::Sky,pd);
        }
    }
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

PipelineData *GetPipelineData(const InlinePipeline &ip)
{
    if(inline_pipeline_data.GetCount()<=0)
        InitInlinePipelineData();

    return inline_pipeline_data[ip];
}
VK_NAMESPACE_END