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

struct VKPipelineData
{
    VkGraphicsPipelineCreateInfo                pipelineInfo;

    VkPipelineVertexInputStateCreateInfo        vis_create_info;
    VkPipelineInputAssemblyStateCreateInfo      inputAssembly;
    VkPipelineTessellationStateCreateInfo       tessellation;

    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineViewportStateCreateInfo           viewportState;

    VkPipelineRasterizationStateCreateInfo      rasterizer;
    
    VkSampleMask                                sample_mask[MAX_SAMPLE_MASK_COUNT];
    VkPipelineMultisampleStateCreateInfo        multisample;

    VkPipelineDepthStencilStateCreateInfo       depthStencilState;
    
    List<VkPipelineColorBlendAttachmentState>   colorBlendAttachments;
    VkPipelineColorBlendStateCreateInfo         colorBlending;

    VkDynamicState                              dynamicStateEnables[VK_DYNAMIC_STATE_RANGE_SIZE];
    VkPipelineDynamicStateCreateInfo            dynamicState;

    float alpha_test;
    bool alpha_blend;

public:

    VKPipelineData(const uint32_t color_attachment_count=1);
    VKPipelineData(uchar *data,uint size);
    ~VKPipelineData()=default;

    void InitVertexInputState(const uint32_t stage_count,const VkPipelineShaderStageCreateInfo *stages);    
    void InitViewportState(const VkExtent2D &extent);
    void InitDynamicState();

public:

    bool Set(const Prim prim,bool=false);

    void SetViewport(       float x,float y,float w,float h){viewport.x=x;viewport.y=y;viewport.width=w;viewport.height=h;}
    void SetDepthRange(     float min_depth,float max_depth){viewport.minDepth=min_depth;viewport.maxDepth=max_depth;}
    void SetScissor(        float l,float t,float w,float h){scissor.offset.x=l;scissor.offset.y=t;scissor.extent.width=w;scissor.extent.height=h;}

    void SetAlphaTest(      const float at)                 {alpha_test=at;}

    void SetDepthTest(      bool                dt)         {depthStencilState.depthTestEnable=dt;}
    void SetDepthWrite(     bool                dw)         {depthStencilState.depthWriteEnable=dw;}
    void SetDepthCompareOp( VkCompareOp         op)         {depthStencilState.depthCompareOp=op;}
    void SetDepthBoundsTest(bool                dbt)        {depthStencilState.depthBoundsTestEnable=dbt;}
    void SetDepthBounds(    float               min_depth,
                            float               max_depth)  {depthStencilState.depthBoundsTestEnable=VK_TRUE;
                                                             depthStencilState.minDepthBounds=min_depth;
                                                             depthStencilState.maxDepthBounds=max_depth;}
    void SetStencilTest(    bool                st)         {depthStencilState.stencilTestEnable=st;}

    void SetDepthClamp(     bool                dc)         {rasterizer.depthClampEnable=dc;}
    void SetDiscard(        bool                discard)    {rasterizer.rasterizerDiscardEnable=discard;}
    void SetPolygonMode(    VkPolygonMode       pm)         {rasterizer.polygonMode =pm;}
    void SetCullMode(       VkCullModeFlagBits  cm)         {rasterizer.cullMode    =cm;}
    void CloseCullFace()                                    {rasterizer.cullMode    =VK_CULL_MODE_NONE;}
    void SetFrontFace(      VkFrontFace         ff)         {rasterizer.frontFace   =ff;}
    void SetDepthBias(      float               ConstantFactor,
                            float               Clamp,
                            float               SlopeFactor)
    {
        rasterizer.depthBiasEnable          =VK_TRUE;
        rasterizer.depthBiasConstantFactor  =ConstantFactor;
        rasterizer.depthBiasClamp           =Clamp;
        rasterizer.depthBiasSlopeFactor     =SlopeFactor;
    }
    void DisableDepthBias()                                 {rasterizer.depthBiasEnable=VK_FALSE;}
    void SetLineWidth(      float               line_width) {rasterizer.lineWidth   =line_width;}

    void SetSamleCount(     VkSampleCountFlagBits sc)
    {
        multisample.sampleShadingEnable=(sc==VK_SAMPLE_COUNT_1_BIT?VK_FALSE:VK_TRUE);
        multisample.rasterizationSamples=sc;
    }

    bool SetColorWriteMask(uint index,bool r,bool g,bool b,bool a);
    void AddColorBlendAttachment(const VkPipelineColorBlendAttachmentState *cba);
    bool SetBlend(uint index,bool blend);

    void SetLogicOp(VkLogicOp logic_op) {colorBlending.logicOpEnable=VK_TRUE;colorBlending.logicOp=logic_op;}
    void DisableLogicOp()               {colorBlending.logicOpEnable=VK_FALSE;}

    void SetBlendConstans(float r,float g,float b,float a)
    {
        colorBlending.blendConstants[0] = r;
        colorBlending.blendConstants[1] = g;
        colorBlending.blendConstants[2] = b;
        colorBlending.blendConstants[3] = a;
    }

    void SetBlendConstans(float *blend_constans)        {hgl_typecpy(colorBlending.blendConstants,blend_constans,4);}

public:

    bool SaveToStream(io::DataOutputStream *dos);
    bool LoadFromMemory(uchar *,uint);
};//struct VKPipelineData

bool SaveToFile(const OSString &filename,VKPipelineData *);
bool LoadFromFile(const OSString &filename,VKPipelineData *);
VK_NAMESPACE_END
#endif//HGL_GRAPH_VULKAN_PIPELINE_DATA_INCLUDE
