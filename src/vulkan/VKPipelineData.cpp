#include<hgl/graph/VKPipelineData.h>

VK_NAMESPACE_BEGIN

void SetDefault(VkPipelineColorBlendAttachmentState *cba)
{    
    cba->colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    cba->blendEnable = VK_FALSE;
    cba->alphaBlendOp = VK_BLEND_OP_ADD;
    cba->colorBlendOp = VK_BLEND_OP_ADD;
    cba->srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    cba->dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    cba->srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    cba->dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
}

PipelineData::PipelineData(const uint32_t color_attachment_count)
{
    file_data=nullptr;

    hgl_zero(pipeline_info);
    //hgl_zero(vis_create_info);
    //hgl_zero(input_assembly);
    //hgl_zero(tessellation);
    //hgl_zero(viewport);
    //hgl_zero(scissor);
    //hgl_zero(viewport_state);
    //hgl_zero(rasterization);    
    //hgl_zero(sample_mask);
    //hgl_zero(multi_sample);
    //hgl_zero(depth_stencil);    
    //hgl_zero(color_blend);
    //hgl_zero(dynamic_state_enables);
    //hgl_zero(dynamic_state);

    pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    
    tessellation=new VkPipelineTessellationStateCreateInfo;
    tessellation->sType=VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
    tessellation->pNext=nullptr;
    tessellation->flags=0;
    tessellation->patchControlPoints=0;

    pipeline_info.pTessellationState=tessellation;
    
    rasterization=new VkPipelineRasterizationStateCreateInfo;
    rasterization->sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterization->pNext = nullptr;
    rasterization->flags = 0;
    rasterization->depthClampEnable = VK_FALSE;
    rasterization->rasterizerDiscardEnable = VK_FALSE;
    rasterization->polygonMode = VK_POLYGON_MODE_FILL;
    rasterization->cullMode = VK_CULL_MODE_BACK_BIT;
    rasterization->frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;     //逆时针，和opengl一样
    rasterization->depthBiasEnable = VK_FALSE;
    rasterization->depthBiasConstantFactor = 0;
    rasterization->depthBiasClamp = 0;
    rasterization->depthBiasSlopeFactor = 0;
    rasterization->lineWidth = 1.0f;

    pipeline_info.pRasterizationState=rasterization;
    
    multi_sample=new VkPipelineMultisampleStateCreateInfo;
    multi_sample->sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multi_sample->pNext = nullptr;
    multi_sample->flags = 0;
    multi_sample->rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multi_sample->sampleShadingEnable = VK_FALSE;
    multi_sample->minSampleShading = 0.0;
    multi_sample->pSampleMask = nullptr;
    multi_sample->alphaToCoverageEnable = VK_FALSE;
    multi_sample->alphaToOneEnable = VK_FALSE;
    
    sample_mask=nullptr;

    pipeline_info.pMultisampleState=multi_sample;
    
    depth_stencil=new VkPipelineDepthStencilStateCreateInfo;
    depth_stencil->sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depth_stencil->pNext = nullptr;
    depth_stencil->flags = 0;
    depth_stencil->depthTestEnable = VK_TRUE;
    depth_stencil->depthWriteEnable = VK_TRUE;
    depth_stencil->depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
    depth_stencil->depthBoundsTestEnable = VK_FALSE;
    depth_stencil->minDepthBounds = 0;
    depth_stencil->maxDepthBounds = 0;
    depth_stencil->stencilTestEnable = VK_FALSE;
    depth_stencil->back.failOp = VK_STENCIL_OP_KEEP;
    depth_stencil->back.passOp = VK_STENCIL_OP_KEEP;
    depth_stencil->back.compareOp = VK_COMPARE_OP_ALWAYS;
    depth_stencil->back.compareMask = 0;
    depth_stencil->back.reference = 0;
    depth_stencil->back.depthFailOp = VK_STENCIL_OP_KEEP;
    depth_stencil->back.writeMask = 0;
    depth_stencil->front = depth_stencil->back;
    depth_stencil->front.compareOp=VK_COMPARE_OP_NEVER;

    pipeline_info.pDepthStencilState=depth_stencil;

    //这个需要和subpass中的color attachment数量相等，所以添加多份
    color_blend_attachments=hgl_align_malloc<VkPipelineColorBlendAttachmentState>(color_attachment_count);
    SetDefault(color_blend_attachments);

    alpha_test=0;
    alpha_blend=false;
    
    color_blend=new VkPipelineColorBlendStateCreateInfo;
    color_blend->sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    color_blend->pNext = nullptr;
    color_blend->flags = 0;
    color_blend->logicOpEnable = VK_FALSE;
    color_blend->logicOp = VK_LOGIC_OP_CLEAR;
    color_blend->attachmentCount = color_attachment_count;
    color_blend->pAttachments = color_blend_attachments;
    color_blend->blendConstants[0] = 0.0f;
    color_blend->blendConstants[1] = 0.0f;
    color_blend->blendConstants[2] = 0.0f;
    color_blend->blendConstants[3] = 0.0f;

    pipeline_info.pColorBlendState=color_blend;

    InitDynamicState();

    {
        pipeline_info.basePipelineHandle = VK_NULL_HANDLE;
        pipeline_info.basePipelineIndex = -1;
    }
}

void PipelineData::SetColorAttachments(const uint32_t count)
{
    if(!color_blend_attachments)
    {
        color_blend->attachmentCount=0;
        color_blend_attachments=hgl_align_malloc<VkPipelineColorBlendAttachmentState>(count);
        SetDefault(color_blend_attachments);
    }
    else
    {
        if(color_blend->attachmentCount==count)return;

        color_blend_attachments=hgl_align_realloc<VkPipelineColorBlendAttachmentState>(color_blend_attachments,count);
    }

    if(count>color_blend->attachmentCount)
    {        
        VkPipelineColorBlendAttachmentState *cba=color_blend_attachments+color_blend->attachmentCount;

        for(uint32_t i=color_blend->attachmentCount;i<count;i++)
        {
            memcpy(cba,color_blend_attachments,sizeof(VkPipelineColorBlendAttachmentState));
            ++cba;
        }
    }

    color_blend->attachmentCount=count;
    color_blend->pAttachments = color_blend_attachments;
}

PipelineData::PipelineData()
{
    hgl_zero(pipeline_info);
    pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;

    pipeline_info.basePipelineHandle = VK_NULL_HANDLE;
    pipeline_info.basePipelineIndex = -1;

    sample_mask=nullptr;
    color_blend_attachments=nullptr;
}

void PipelineData::InitVertexInputState(const uint32_t stage_count,
                                        const VkPipelineShaderStageCreateInfo *stages,
                                        const uint32_t attr_count,
                                        const VkVertexInputBindingDescription *binding_list,
                                        const VkVertexInputAttributeDescription *attribute_list)
{
    pipeline_info.stageCount = stage_count;
    pipeline_info.pStages = stages;

    vis_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vis_create_info.pNext = nullptr;
    vis_create_info.flags = 0;
    vis_create_info.vertexBindingDescriptionCount   = attr_count;
    vis_create_info.pVertexBindingDescriptions      = binding_list;
    vis_create_info.vertexAttributeDescriptionCount = attr_count;
    vis_create_info.pVertexAttributeDescriptions    = attribute_list;
    
    pipeline_info.pVertexInputState  = &vis_create_info;
}

bool PipelineData::Set(const Prim topology,bool restart)
{
    if(topology<Prim::BEGIN_RANGE||topology>Prim::END_RANGE)
        if(topology!=Prim::Rectangles)return(false);

    input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    input_assembly.pNext = nullptr;
    input_assembly.flags = 0;
    input_assembly.topology = VkPrimitiveTopology(topology==Prim::Rectangles?Prim::Points:topology);
    input_assembly.primitiveRestartEnable = restart;

    pipeline_info.pInputAssemblyState = &input_assembly;
    return(true);
}
    
void PipelineData::InitViewportState(const VkExtent2D &extent)
{
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = extent.width;
    viewport.height = extent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    scissor.offset = {0, 0};
    scissor.extent = extent;

    viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_state.pNext = nullptr;
    viewport_state.flags = 0;
    viewport_state.viewportCount = 1;
    viewport_state.pViewports = &viewport;
    viewport_state.scissorCount = 1;
    viewport_state.pScissors = &scissor;
    
    pipeline_info.pViewportState     = &viewport_state;
}

void PipelineData::InitDynamicState()
{
    memset(dynamic_state_enables, 0, sizeof dynamic_state_enables);

    dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamic_state.pNext = nullptr;
    dynamic_state.flags = 0;
    dynamic_state.pDynamicStates = dynamic_state_enables;
    dynamic_state.dynamicStateCount = 0;
    dynamic_state_enables[dynamic_state.dynamicStateCount++] = VK_DYNAMIC_STATE_VIEWPORT;
    dynamic_state_enables[dynamic_state.dynamicStateCount++] = VK_DYNAMIC_STATE_SCISSOR;
    dynamic_state_enables[dynamic_state.dynamicStateCount++] = VK_DYNAMIC_STATE_LINE_WIDTH;

    //如果窗口大小不变，可以不设置这两个。能不能提升效能未知
    pipeline_info.pDynamicState      = &dynamic_state;
}

bool PipelineData::SetColorWriteMask(uint index,bool r,bool g,bool b,bool a)
{
    if(index>=color_blend->attachmentCount)
        return(false);

    VkPipelineColorBlendAttachmentState *cba=color_blend_attachments+index;

    cba->colorWriteMask=0;

    if(r)cba->colorWriteMask|=VK_COLOR_COMPONENT_R_BIT;
    if(r)cba->colorWriteMask|=VK_COLOR_COMPONENT_G_BIT;
    if(g)cba->colorWriteMask|=VK_COLOR_COMPONENT_B_BIT;
    if(a)cba->colorWriteMask|=VK_COLOR_COMPONENT_A_BIT;

    return(true);
}

bool PipelineData::OpenBlend(uint index)
{
    if(index>=color_blend->attachmentCount)
        return(false);

    color_blend_attachments[index].blendEnable=true;

    return(true);
}

bool PipelineData::CloseBlend(uint index)
{
    if(index>=color_blend->attachmentCount)
        return(false);

    color_blend_attachments[index].blendEnable=false;

    return(true);
}

bool PipelineData::SetColorBlend(uint index,VkBlendOp op,VkBlendFactor src,VkBlendFactor dst)
{
    if(index>=color_blend->attachmentCount)
        return(false);
        
    VkPipelineColorBlendAttachmentState *cba=color_blend_attachments+index;

    cba->colorBlendOp=op;
    cba->srcColorBlendFactor=src;
    cba->dstColorBlendFactor=dst;

    return(true);
}

bool PipelineData::SetAlphaBlend(uint index,VkBlendOp op,VkBlendFactor src,VkBlendFactor dst)
{
    if(index>=color_blend->attachmentCount)
        return(false);
        
    VkPipelineColorBlendAttachmentState *cba=color_blend_attachments+index;

    cba->colorBlendOp=op;
    cba->srcAlphaBlendFactor=src;
    cba->dstAlphaBlendFactor=dst;

    return(true);
}
VK_NAMESPACE_END