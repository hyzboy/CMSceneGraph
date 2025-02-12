#include<hgl/graph/VKPipelineData.h>
#include<hgl/graph/VKString.h>
#include<toml.hpp>

VK_NAMESPACE_BEGIN

namespace
{
    void SaveToToml(toml::value &tv,const VkPipelineTessellationStateCreateInfo *tsci)
    {
        tv["PatchControlPoints"]=tsci->patchControlPoints;
    }

    void SaveToToml(toml::value &tv,const VkPipelineRasterizationStateCreateInfo *rsci)
    {
        tv["DepthClamp" ]=VkToString(rsci->depthClampEnable);
        tv["Discard"    ]=VkToString(rsci->rasterizerDiscardEnable);
        tv["PolygonMode"]=VkToString(rsci->polygonMode);
        tv["Cull"       ]=VkToString(rsci->cullMode);
        tv["FrontFace"  ]=VkToString(rsci->frontFace);

        {
            toml::value depth_bias;

            depth_bias["Enable"          ]=VkToString(rsci->depthBiasEnable);
            depth_bias["ConstantFactor"  ]=rsci->depthBiasConstantFactor;
            depth_bias["Clamp"           ]=rsci->depthBiasClamp;
            depth_bias["SlopeFactor"     ]=rsci->depthBiasSlopeFactor;

            tv["DepthBias"]=depth_bias;
        }

        tv["LineWidth"  ]=rsci->lineWidth;
    }

    void SaveToToml(toml::value &tv,const VkPipelineMultisampleStateCreateInfo *msci)
    {
        tv["Samples"            ]=(uint)msci->rasterizationSamples;
        tv["SampleShading"      ]=VkToString(msci->sampleShadingEnable);
        tv["MinSampleShading"   ]=msci->minSampleShading;

        //tv["SampleMask"]

        tv["AlphaToCoverage"    ]=VkToString(msci->alphaToCoverageEnable);
        tv["AlphaToOne"         ]=VkToString(msci->alphaToOneEnable);
    }

    void SaveToToml(toml::value &tv,const VkStencilOpState *sos)
    {
        tv["FailOp"      ]=VkToString(sos->failOp);
        tv["PassOp"      ]=VkToString(sos->passOp);
        tv["DepthFailOp" ]=VkToString(sos->depthFailOp);
        tv["CompareOp"   ]=VkToString(sos->compareOp);
        tv["CompareMask" ]=sos->compareMask;
        tv["WriteMask"   ]=sos->writeMask;
        tv["Reference"   ]=sos->reference;
    }

    void SaveToToml(toml::value &tv,const VkPipelineDepthStencilStateCreateInfo *dssci)
    {
        tv["DepthTest"          ]=VkToString(dssci->depthTestEnable);
        tv["DepthWrite"         ]=VkToString(dssci->depthWriteEnable);
        tv["DepthCompareOp"     ]=VkToString(dssci->depthCompareOp);
        tv["DepthBounds"        ]=VkToString(dssci->depthBoundsTestEnable);
        tv["StencilTest"        ]=VkToString(dssci->stencilTestEnable);
        {
            toml::value front,back;

            SaveToToml(front,   &(dssci->front));
            SaveToToml(back,    &(dssci->back));

            tv["Front"]=front;
            tv["Back" ]=back;
        }

        tv["MinDepthBounds"     ]=dssci->minDepthBounds;
        tv["MaxDepthBounds"     ]=dssci->maxDepthBounds;
    }

    void SaveToToml(toml::value &tv,const VkPipelineColorBlendAttachmentState *cbas)
    {
        tv["Enable"        ]=VkToString(cbas->blendEnable);

        {
            toml::value color;

            color["Src"]=VkToString(cbas->srcColorBlendFactor);
            color["Dst"]=VkToString(cbas->dstColorBlendFactor);
            color["Op" ]=VkToString(cbas->colorBlendOp);

            tv["Color"]=color;
        }

        {
            toml::value alpha;

            alpha["Src"]=VkToString(cbas->srcAlphaBlendFactor);
            alpha["Dst"]=VkToString(cbas->dstAlphaBlendFactor);
            alpha["Op" ]=VkToString(cbas->alphaBlendOp);

            tv["Alpha"]=alpha;
        }

        {
            char color_mask[5],*p;

            p=color_mask;

            if(cbas->colorWriteMask&VK_COLOR_COMPONENT_R_BIT)*p++='R';
            if(cbas->colorWriteMask&VK_COLOR_COMPONENT_G_BIT)*p++='G';
            if(cbas->colorWriteMask&VK_COLOR_COMPONENT_B_BIT)*p++='B';
            if(cbas->colorWriteMask&VK_COLOR_COMPONENT_A_BIT)*p++='A';

            *p=0;

            tv["ColorWriteMask"     ]=color_mask;
        }
    }

    void SaveToToml(toml::value &tv,const VkPipelineColorBlendStateCreateInfo *cbsci)
    {
        {
            toml::value logic_op;

            logic_op["Enable"   ]=VkToString(cbsci->logicOpEnable);
            logic_op["Op"       ]=VkToString(cbsci->logicOp);

            tv["LogicOp"]=logic_op;
        }

        {
            toml::array attachments;

            for(uint i=0;i<cbsci->attachmentCount;i++)
            {
                toml::value attachment;
                SaveToToml(attachment,cbsci->pAttachments+i);
                attachments.push_back(attachment);
            }

            tv["Attachments"]=attachments;
        }

        {
            toml::array blend_constants;
            blend_constants.push_back(cbsci->blendConstants[0]);
            blend_constants.push_back(cbsci->blendConstants[1]);
            blend_constants.push_back(cbsci->blendConstants[2]);
            blend_constants.push_back(cbsci->blendConstants[3]);
            tv["BlendConstants"]=blend_constants;
        }
    }
}//namespace

std::string SavePipeline2Toml(const PipelineData *data)
{
    toml::value result;

    {
        toml::value tessellation;
        SaveToToml(tessellation,data->tessellation);
        result["Tessellation"]=tessellation;
    }
    {
        toml::value rasterization;
        SaveToToml(rasterization,data->rasterization);
        result["Rasterization"]=rasterization;
    }
    {
        toml::value multisample;
        SaveToToml(multisample,data->multi_sample);
        result["Multisample"]=multisample;
    }
    {
        toml::value depth_stencil;
        SaveToToml(depth_stencil,data->depth_stencil);
        result["DepthStencil"]=depth_stencil;
    }
    {
        toml::value color_blend;
        SaveToToml(color_blend,data->color_blend);
        result["ColorBlend"]=color_blend;
    }

    return toml::format(result);
}

VK_NAMESPACE_END
