#include<hgl/graph/vulkan/VKPipelineData.h>

VK_NAMESPACE_BEGIN
VKPipelineData::VKPipelineData(const uint32_t color_attachment_count)
{
    hgl_zero(pipelineInfo);
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;

    tessellation.sType=VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
    tessellation.pNext=nullptr;
    tessellation.flags=0;
    tessellation.patchControlPoints=0;

    pipelineInfo.pTessellationState=&tessellation;

    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.pNext = nullptr;
    rasterizer.flags = 0;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;     //逆时针，和opengl一样
    rasterizer.depthBiasEnable = VK_FALSE;
    rasterizer.depthBiasConstantFactor = 0;
    rasterizer.depthBiasClamp = 0;
    rasterizer.depthBiasSlopeFactor = 0;
    rasterizer.lineWidth = 1.0f;

    pipelineInfo.pRasterizationState = &rasterizer;

    multisample.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisample.pNext = nullptr;
    multisample.flags = 0;
    multisample.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisample.sampleShadingEnable = VK_FALSE;
    multisample.minSampleShading = 0.0;
    multisample.pSampleMask = nullptr;
    multisample.alphaToCoverageEnable = VK_FALSE;
    multisample.alphaToOneEnable = VK_FALSE;

    pipelineInfo.pMultisampleState = &multisample;

    depthStencilState.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencilState.pNext = nullptr;
    depthStencilState.flags = 0;
    depthStencilState.depthTestEnable = VK_TRUE;
    depthStencilState.depthWriteEnable = VK_TRUE;
    depthStencilState.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
    depthStencilState.depthBoundsTestEnable = VK_FALSE;
    depthStencilState.minDepthBounds = 0;
    depthStencilState.maxDepthBounds = 0;
    depthStencilState.stencilTestEnable = VK_FALSE;
    depthStencilState.back.failOp = VK_STENCIL_OP_KEEP;
    depthStencilState.back.passOp = VK_STENCIL_OP_KEEP;
    depthStencilState.back.compareOp = VK_COMPARE_OP_ALWAYS;
    depthStencilState.back.compareMask = 0;
    depthStencilState.back.reference = 0;
    depthStencilState.back.depthFailOp = VK_STENCIL_OP_KEEP;
    depthStencilState.back.writeMask = 0;
    depthStencilState.front = depthStencilState.back;
    depthStencilState.front.compareOp=VK_COMPARE_OP_NEVER;

    pipelineInfo.pDepthStencilState=&depthStencilState;

    VkPipelineColorBlendAttachmentState cba;
    cba.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    cba.blendEnable = VK_FALSE;
    cba.alphaBlendOp = VK_BLEND_OP_ADD;
    cba.colorBlendOp = VK_BLEND_OP_ADD;
    cba.srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    cba.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    cba.srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    cba.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;

    colorBlendAttachments.Add(cba,color_attachment_count);     //这个需要和subpass中的color attachment数量相等，所以添加多份

    alpha_blend=false;

    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.pNext = nullptr;
    colorBlending.flags = 0;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_CLEAR;
    colorBlending.attachmentCount = colorBlendAttachments.GetCount();
    colorBlending.pAttachments = colorBlendAttachments.GetData();
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;

    pipelineInfo.pColorBlendState = &colorBlending;

    InitDynamicState();

    {
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
        pipelineInfo.basePipelineIndex = -1;
    }
}

VKPipelineData::VKPipelineData(uchar *data,uint size)
{
    LoadFromMemory(data,size);

    pipelineInfo.pInputAssemblyState=&inputAssembly;
    pipelineInfo.pTessellationState =&tessellation;
    pipelineInfo.pRasterizationState=&rasterizer;
    pipelineInfo.pMultisampleState  =&multisample;
    pipelineInfo.pDepthStencilState =&depthStencilState;
    pipelineInfo.pColorBlendState   =&colorBlending;

    InitDynamicState();

    {
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
        pipelineInfo.basePipelineIndex = -1;
    }
}

void VKPipelineData::InitVertexInputState(const uint32_t stage_count,const VkPipelineShaderStageCreateInfo *stages)
{
    pipelineInfo.stageCount = stage_count;
    pipelineInfo.pStages = stages;

    vis_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vis_create_info.pNext = nullptr;
    vis_create_info.flags = 0;
    
    pipelineInfo.pVertexInputState  = &vis_create_info;
}

bool VKPipelineData::Set(const Prim topology,bool restart)
{
    if(topology<Prim::BEGIN_RANGE||topology>Prim::END_RANGE)
        if(topology!=Prim::Rectangles)return(false);

    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.pNext = nullptr;
    inputAssembly.flags = 0;
    inputAssembly.topology = VkPrimitiveTopology(topology==Prim::Rectangles?Prim::Points:topology);
    inputAssembly.primitiveRestartEnable = restart;

    pipelineInfo.pInputAssemblyState = &inputAssembly;
    return(true);
}
    
void VKPipelineData::InitViewportState(const VkExtent2D &extent)
{
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = extent.width;
    viewport.height = extent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    scissor.offset = {0, 0};
    scissor.extent = extent;

    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.pNext = nullptr;
    viewportState.flags = 0;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;
    
    pipelineInfo.pViewportState     = &viewportState;
}

void VKPipelineData::InitDynamicState()
{
    memset(dynamicStateEnables, 0, sizeof dynamicStateEnables);

    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.pNext = nullptr;
    dynamicState.flags = 0;
    dynamicState.pDynamicStates = dynamicStateEnables;
    dynamicState.dynamicStateCount = 0;
    dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_VIEWPORT;
    dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_SCISSOR;
    dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_LINE_WIDTH;

    //如果窗口大小不变，可以不设置这两个。能不能提升效能未知
    pipelineInfo.pDynamicState      = &dynamicState;
}

bool VKPipelineData::SetColorWriteMask(uint index,bool r,bool g,bool b,bool a)
{
    VkPipelineColorBlendAttachmentState *cba=colorBlendAttachments.GetPointer(index);
        
    if(!cba)return(false);

    cba->colorWriteMask=0;

    if(r)cba->colorWriteMask|=VK_COLOR_COMPONENT_R_BIT;
    if(r)cba->colorWriteMask|=VK_COLOR_COMPONENT_G_BIT;
    if(g)cba->colorWriteMask|=VK_COLOR_COMPONENT_B_BIT;
    if(a)cba->colorWriteMask|=VK_COLOR_COMPONENT_A_BIT;

    return(true);
}

void VKPipelineData::AddColorBlendAttachment(const VkPipelineColorBlendAttachmentState *cba)
{
    if(!cba)return;

    colorBlendAttachments.Add(*cba);
    colorBlending.attachmentCount=colorBlendAttachments.GetCount();

    if(cba->blendEnable)
        alpha_blend=true;
}

bool VKPipelineData::SetBlend(uint index,bool blend)
{
    VkPipelineColorBlendAttachmentState *cba=colorBlendAttachments.GetPointer(index);

    if(!cba)return(false);

    cba->blendEnable=blend;

    if(blend)
        alpha_blend=true;
    else
    {
        cba=colorBlendAttachments.GetData();

        for(int i=0;i<colorBlendAttachments.GetCount();i++)
            if(cba->blendEnable)
            {
                alpha_blend=true;
                return(true);
            }

        alpha_blend=false;
    }

    return(true);
}
VK_NAMESPACE_END