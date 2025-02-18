#include<hgl/graph/VKPipelineData.h>
#include<hgl/graph/VKString.h>
#include<hgl/io/LoadString.h>
#include<toml.hpp>

VK_NAMESPACE_BEGIN

namespace
{
    template<typename E> const bool VkToEnum(E &result,toml::value &tv,const char *name)
    {
        if(!tv.contains(name))
            return(false);

        result=VK_NAMESPACE::VkToEnum<E>(tv[name].as_string().c_str());
        return(true);
    }

    void VkToBool(VkBool32 &result,toml::value &tv,const char *name)
    {
        if(!tv.contains(name))
            return;

        char ch=*(tv[name].as_string().c_str());

        if(ch=='t'||ch=='T'
         ||ch=='y'||ch=='Y'
         ||ch=='1')
            result=VK_TRUE;
        else
            result=VK_FALSE;
    }

    bool LoadFromToml(VkPipelineTessellationStateCreateInfo *tsci,toml::value &tv)
    {
        tsci->patchControlPoints=tv["PatchControlPoints"].as_integer();

        return(true);
    }

    bool LoadFromToml(VkPipelineRasterizationStateCreateInfo *rsci,toml::value &tv)
    {
        VkToBool(rsci->depthClampEnable,        tv,"DepthClamp");
        VkToBool(rsci->rasterizerDiscardEnable, tv,"Discard");
        VkToEnum(rsci->polygonMode,             tv,"PolygonMode");
        VkToEnum(rsci->cullMode,                tv,"Cull");
        VkToEnum(rsci->frontFace,               tv,"FrontFace");

        if(tv.contains("DepthBias"))
        {
            toml::value &depth_bias=tv["DepthBias"];

            rsci->depthBiasEnable        =depth_bias["Enable"          ].as_boolean();
            rsci->depthBiasConstantFactor=depth_bias["ConstantFactor"  ].as_floating();
            rsci->depthBiasClamp         =depth_bias["Clamp"           ].as_floating();
            rsci->depthBiasSlopeFactor   =depth_bias["SlopeFactor"     ].as_floating();
        }

        rsci->lineWidth           =tv["LineWidth"  ].as_floating();

        return(true);
    }

    bool LoadFromToml(VkPipelineMultisampleStateCreateInfo *msci,toml::value &tv)
    {
        msci->rasterizationSamples  =(VkSampleCountFlagBits)tv["Samples"            ].as_integer();

        msci->sampleShadingEnable   =tv["SampleShading"     ].as_boolean();
        msci->minSampleShading      =tv["MinSampleShading"  ].as_floating();
        //msci->pSampleMask
        msci->alphaToCoverageEnable =tv["AlphaToCoverage"   ].as_boolean();
        msci->alphaToOneEnable      =tv["AlphaToOne"        ].as_boolean();

        return(true);
    }

    bool LoadFromToml(VkStencilOpState *sos,toml::value &tv)
    {
        VkToEnum(sos->failOp,      tv,"FailOp");
        VkToEnum(sos->passOp,      tv,"PassOp");
        VkToEnum(sos->depthFailOp, tv,"DepthFailOp");
        VkToEnum(sos->compareOp,   tv,"CompareOp");

        sos->compareMask=tv["CompareMask"].as_integer();
        sos->writeMask  =tv["WriteMask"  ].as_integer();
        sos->reference  =tv["Reference"  ].as_integer();

        return(true);
    }

    bool LoadFromToml(VkPipelineDepthStencilStateCreateInfo *dssci,toml::value &tv)
    {
        dssci->depthTestEnable      =tv["DepthTest"].as_boolean();
        dssci->depthWriteEnable     =tv["DepthWrite"].as_boolean();

        VkToEnum(dssci->depthCompareOp,tv,"DepthCompareOp");

        dssci->depthBoundsTestEnable=tv["DepthBounds"].as_boolean();
        dssci->stencilTestEnable    =tv["StencilTest"].as_boolean();

        if(tv.contains("DepthBounds"))
        {
            toml::value &depth_bounds=tv["DepthBounds"];

            dssci->minDepthBounds=depth_bounds["Min"].as_floating();
            dssci->maxDepthBounds=depth_bounds["Max"].as_floating();
        }

        if(tv.contains("Front"))
            LoadFromToml(&(dssci->front),tv["Front"]);

        if(tv.contains("Back"))
            LoadFromToml(&(dssci->back),tv["Back"]);

        return(true);
    }

    bool LoadFromToml(VkPipelineColorBlendAttachmentState *cbas,toml::value &tv)
    {
        cbas->blendEnable=tv["Enable"].as_boolean();

        if(tv.contains("Color"))
        {
            toml::value &color=tv["Color"];
            VkToEnum(cbas->srcColorBlendFactor,color,"Src");
            VkToEnum(cbas->dstColorBlendFactor,color,"Dst");
            VkToEnum(cbas->colorBlendOp,       color,"Op");
        }

        if(tv.contains("Alpha"))
        {
            toml::value &alpha=tv["Alpha"];
        
            VkToEnum(cbas->srcAlphaBlendFactor,alpha,"Src");
            VkToEnum(cbas->dstAlphaBlendFactor,alpha,"Dst");
            VkToEnum(cbas->alphaBlendOp,       alpha,"Op");
        }

        {
            std::string &color_mask=tv["WriteMask"].as_string();

            cbas->colorWriteMask=0;

            for(char ch:color_mask)
            {
                if(ch=='R'||ch=='r')cbas->colorWriteMask|=VK_COLOR_COMPONENT_R_BIT;else
                if(ch=='G'||ch=='g')cbas->colorWriteMask|=VK_COLOR_COMPONENT_G_BIT;else
                if(ch=='B'||ch=='b')cbas->colorWriteMask|=VK_COLOR_COMPONENT_B_BIT;else
                if(ch=='A'||ch=='a')cbas->colorWriteMask|=VK_COLOR_COMPONENT_A_BIT;
            }
        }

        return(true);
    }

    bool LoadFromToml(PipelineData *data,VkPipelineColorBlendStateCreateInfo *cbsci,toml::value &tv)
    {
        if(tv.contains("LogicOp"))
        {
            toml::value &logic_op=tv["LogicOp"];

            cbsci->logicOpEnable=logic_op["Enable"].as_boolean();

            VkToEnum(cbsci->logicOp,logic_op,"Op");
        }

        if(tv.contains("Attachments"))
        {
            toml::array &attachments=tv["Attachments"].as_array();

            cbsci->attachmentCount=(uint32_t)attachments.size();

            data->SetColorAttachments(cbsci->attachmentCount);

            for(uint i=0;i<cbsci->attachmentCount;i++)
                LoadFromToml(data->color_blend_attachments+i,attachments[i]);
        }

        if(tv.contains("BlendConstants"))
        {
            toml::array &blend_constants=tv["BlendConstants"].as_array();

            cbsci->blendConstants[0]=blend_constants[0].as_floating();
            cbsci->blendConstants[1]=blend_constants[1].as_floating();
            cbsci->blendConstants[2]=blend_constants[2].as_floating();
            cbsci->blendConstants[3]=blend_constants[3].as_floating();
        }

        return(true);
    }
}//namespace

bool LoadPipelineFromToml(PipelineData *pd,const std::string &toml_string)
{
    toml::value root=toml::parse_str(toml_string);

    if(root.contains("Tessellation"))
        LoadFromToml(pd->tessellation,root["Tessellation"]);

    if(root.contains("Rasterization"))
        LoadFromToml(pd->rasterization,root["Rasterization"]);

    if(root.contains("Multisample"))
        LoadFromToml(pd->multi_sample,root["Multisample"]);

    if(root.contains("DepthStencil"))
        LoadFromToml(pd->depth_stencil,root["DepthStencil"]);

    if(root.contains("ColorBlend"))
        LoadFromToml(pd,pd->color_blend,root["ColorBlend"]);

    return(false);
}

bool LoadPipelineFromTomlFile(PipelineData *pd,const OSString &filename)
{
    if(!pd)return(false);

    if(filename.IsEmpty())return(false);

    std::string toml_string;

    if(LoadStringFromTextFile(toml_string,filename)<=0)
        return(false);

    return LoadPipelineFromToml(pd,toml_string);
}

VK_NAMESPACE_END
