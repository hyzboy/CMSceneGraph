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
        tv["DepthClamp" ]=VkEnum2String(rsci->depthClampEnable);
        tv["Discard"    ]=VkEnum2String(rsci->rasterizerDiscardEnable);
        tv["PolygonMode"]=VkEnum2String(rsci->polygonMode);
        tv["Cull"       ]=VkEnum2String(rsci->cullMode);
        tv["FrontFace"  ]=VkEnum2String(rsci->frontFace);

        {
            toml::value depth_bias;

            depth_bias["Enable"          ]=VkEnum2String(rsci->depthBiasEnable);
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
        tv["SampleShading"      ]=VkEnum2String(msci->sampleShadingEnable);
        tv["MinSampleShading"   ]=msci->minSampleShading;

        //tv["SampleMask"]

        tv["AlphaToCoverage"    ]=VkEnum2String(msci->alphaToCoverageEnable);
        tv["AlphaToOne"         ]=VkEnum2String(msci->alphaToOneEnable);
    }

    void SaveToToml(toml::value &tv,const VkStencilOpState *sos)
    {
        tv["FailOp"      ]=VkEnum2String(sos->failOp);
        tv["PassOp"      ]=VkEnum2String(sos->passOp);
        tv["DepthFailOp" ]=VkEnum2String(sos->depthFailOp);
        tv["CompareOp"   ]=VkEnum2String(sos->compareOp);
        tv["CompareMask" ]=sos->compareMask;
        tv["WriteMask"   ]=sos->writeMask;
        tv["Reference"   ]=sos->reference;
    }

    void SaveToToml(toml::value &tv,const VkPipelineDepthStencilStateCreateInfo *dssci)
    {
        tv["DepthTest"          ]=VkEnum2String(dssci->depthTestEnable);
        tv["DepthWrite"         ]=VkEnum2String(dssci->depthWriteEnable);
        tv["DepthCompareOp"     ]=VkEnum2String(dssci->depthCompareOp);
        tv["DepthBounds"        ]=VkEnum2String(dssci->depthBoundsTestEnable);
        tv["StencilTest"        ]=VkEnum2String(dssci->stencilTestEnable);
        {
            toml::value front,back;

            SaveToToml(front,   &(dssci->front));
            SaveToToml(back,    &(dssci->back));

            tv["Front"]=front;
            tv["Back" ]=back;
        }

        {
            toml::value depth_bounds;

            depth_bounds["Min"]=dssci->minDepthBounds;
            depth_bounds["Max"]=dssci->maxDepthBounds;

            tv["DepthBounds"]=depth_bounds;
        }
    }

    void SaveToToml(toml::value &tv,const VkPipelineColorBlendAttachmentState *cbas)
    {
        tv["Enable"        ]=VkEnum2String(cbas->blendEnable);

        {
            toml::value color;

            color["Src"]=VkEnum2String(cbas->srcColorBlendFactor);
            color["Dst"]=VkEnum2String(cbas->dstColorBlendFactor);
            color["Op" ]=VkEnum2String(cbas->colorBlendOp);

            tv["Color"]=color;
        }

        {
            toml::value alpha;

            alpha["Src"]=VkEnum2String(cbas->srcAlphaBlendFactor);
            alpha["Dst"]=VkEnum2String(cbas->dstAlphaBlendFactor);
            alpha["Op" ]=VkEnum2String(cbas->alphaBlendOp);

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

            logic_op["Enable"   ]=VkEnum2String(cbsci->logicOpEnable);
            logic_op["Op"       ]=VkEnum2String(cbsci->logicOp);

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

std::string SavePipelineToToml(const PipelineData *data)
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
