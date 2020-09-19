#ifndef HGL_GRAPH_VULKAN_PIPELINE_DATA_INCLUDE
#define HGL_GRAPH_VULKAN_PIPELINE_DATA_INCLUDE

#include<hgl/graph/vulkan/VKNamespace.h>
#include<hgl/graph/vulkan/VKPrimivate.h>
#include<hgl/type/List.h>
#include<hgl/type/String.h>

namespace hgl
{
    namespace io
    {
        class DataOutputStream;
    }
}

VK_NAMESPACE_BEGIN

constexpr size_t MAX_SAMPLE_MASK_COUNT=(VK_SAMPLE_COUNT_64_BIT+31)/32;

#ifndef VK_DYNAMIC_STATE_BEGIN_RANGE
constexpr size_t VK_DYNAMIC_STATE_BEGIN_RANGE=VK_DYNAMIC_STATE_VIEWPORT;
#endif//VK_DYNAMIC_STATE_BEGIN_RANGE

#ifndef VK_DYNAMIC_STATE_END_RANGE
constexpr size_t VK_DYNAMIC_STATE_END_RANGE=VK_DYNAMIC_STATE_STENCIL_REFERENCE;
#endif//VK_DYNAMIC_STATE_END_RANGE

#ifndef VK_DYNAMIC_STATE_RANGE_SIZE
constexpr size_t VK_DYNAMIC_STATE_RANGE_SIZE=VK_DYNAMIC_STATE_END_RANGE-VK_DYNAMIC_STATE_BEGIN_RANGE+1;
#endif//VK_DYNAMIC_STATE_RANGE_SIZE

struct PipelineData
{
private:

    uchar *file_data;

public:

    VkGraphicsPipelineCreateInfo                pipeline_info;

    VkPipelineVertexInputStateCreateInfo        vis_create_info;
    VkPipelineInputAssemblyStateCreateInfo      input_assembly;
    VkPipelineTessellationStateCreateInfo *     tessellation;

    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineViewportStateCreateInfo           viewport_state;

    VkPipelineRasterizationStateCreateInfo *    rasterization;

    VkSampleMask *                              sample_mask;
    VkPipelineMultisampleStateCreateInfo *      multi_sample;

    VkPipelineDepthStencilStateCreateInfo *     depth_stencil;

    VkPipelineColorBlendAttachmentState *       color_blend_attachments;
    VkPipelineColorBlendStateCreateInfo *       color_blend;

    VkDynamicState                              dynamic_state_enables[VK_DYNAMIC_STATE_RANGE_SIZE];
    VkPipelineDynamicStateCreateInfo            dynamic_state;

    float alpha_test;
    bool alpha_blend;

public:

    PipelineData(const uint32_t color_attachment_count);
    PipelineData();
    ~PipelineData();

    void InitVertexInputState(const uint32_t stage_count,const VkPipelineShaderStageCreateInfo *stages);
    void InitViewportState(const VkExtent2D &extent);
    void InitDynamicState();

public:

    bool Set(const Prim prim,bool=false);

    void SetViewport(       float x,float y,float w,float h){viewport.x=x;viewport.y=y;viewport.width=w;viewport.height=h;}
    void SetDepthRange(     float min_depth,float max_depth){viewport.minDepth=min_depth;viewport.maxDepth=max_depth;}
    void SetScissor(        float l,float t,float w,float h){scissor.offset.x=l;scissor.offset.y=t;scissor.extent.width=w;scissor.extent.height=h;}

    void SetAlphaTest(      const float at)                 {alpha_test=at;}

    void SetDepthTest(      bool                dt)         {depth_stencil->depthTestEnable=dt;}
    void SetDepthWrite(     bool                dw)         {depth_stencil->depthWriteEnable=dw;}
    void SetDepthCompareOp( VkCompareOp         op)         {depth_stencil->depthCompareOp=op;}
    void SetDepthBoundsTest(bool                dbt)        {depth_stencil->depthBoundsTestEnable=dbt;}
    void SetDepthBounds(    float               min_depth,
                            float               max_depth)  {depth_stencil->depthBoundsTestEnable=VK_TRUE;
                                                             depth_stencil->minDepthBounds=min_depth;
                                                             depth_stencil->maxDepthBounds=max_depth;}
    void SetStencilTest(    bool                st)         {depth_stencil->stencilTestEnable=st;}

    void SetDepthClamp(     bool                dc)         {rasterization->depthClampEnable=dc;}
    void SetDiscard(        bool                discard)    {rasterization->rasterizerDiscardEnable=discard;}
    void SetPolygonMode(    VkPolygonMode       pm)         {rasterization->polygonMode =pm;}
    void SetCullMode(       VkCullModeFlagBits  cm)         {rasterization->cullMode    =cm;}
    void CloseCullFace()                                    {rasterization->cullMode    =VK_CULL_MODE_NONE;}
    void SetFrontFace(      VkFrontFace         ff)         {rasterization->frontFace   =ff;}
    void SetDepthBias(      float               ConstantFactor,
                            float               Clamp,
                            float               SlopeFactor)
    {
        rasterization->depthBiasEnable          =VK_TRUE;
        rasterization->depthBiasConstantFactor  =ConstantFactor;
        rasterization->depthBiasClamp           =Clamp;
        rasterization->depthBiasSlopeFactor     =SlopeFactor;
    }
    void DisableDepthBias()                                 {rasterization->depthBiasEnable=VK_FALSE;}
    void SetLineWidth(      float               line_width) {rasterization->lineWidth   =line_width;}

    void SetSamleCount(     VkSampleCountFlagBits sc)
    {
        multi_sample->sampleShadingEnable=(sc==VK_SAMPLE_COUNT_1_BIT?VK_FALSE:VK_TRUE);
        multi_sample->rasterizationSamples=sc;
    }
    
    bool SetColorWriteMask(uint index,bool r,bool g,bool b,bool a);
    bool OpenBlend(uint index);
    bool CloseBlend(uint index);

    void SetLogicOp(VkLogicOp logic_op) {color_blend->logicOpEnable=VK_TRUE;color_blend->logicOp=logic_op;}
    void DisableLogicOp()               {color_blend->logicOpEnable=VK_FALSE;}

    void SetBlendConstans(float r,float g,float b,float a)
    {
        color_blend->blendConstants[0] = r;
        color_blend->blendConstants[1] = g;
        color_blend->blendConstants[2] = b;
        color_blend->blendConstants[3] = a;
    }

    void SetBlendConstans(float *blend_constans)        {hgl_cpy(color_blend->blendConstants,blend_constans,4);}

public:

    bool SaveToStream(io::DataOutputStream *dos);
    bool LoadFromMemory(uchar *,uint);
};//struct PipelineData

/**
 * 根据文件名获取PipelineData
 * @param filename 文件名(注意不包含扩展名)
 */
PipelineData *GetPipelineData(const OSString &filename);
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_PIPELINE_DATA_INCLUDE
