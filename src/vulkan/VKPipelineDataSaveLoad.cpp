#include<hgl/graph/vulkan/VKPipelineData.h>
#include<hgl/type/String.h>
#include<hgl/io/MemoryOutputStream.h>
#include<hgl/io/DataOutputStream.h>
#include<hgl/io/MemoryInputStream.h>
#include<hgl/io/DataInputStream.h>
#include<hgl/filesystem/FileSystem.h>

using namespace hgl;

VK_NAMESPACE_BEGIN

constexpr u8char PipelineFileHeader[]=u8"Pipeline\x1A";
constexpr size_t PipelineFileHeaderLength=sizeof(PipelineFileHeader)-1;

#define WRITE_AND_CHECK_SIZE(ptr,type)  if(dos->Write(ptr,sizeof(type))!=sizeof(type))return(false);

bool VKPipelineData::SaveToStream(io::DataOutputStream *dos)
{
    if(!dos)return(false);

    if(dos->Write(PipelineFileHeader,PipelineFileHeaderLength)!=PipelineFileHeaderLength)return(false);
    if(!dos->WriteUint16(1))return(false);     //file ver

    if(!dos->WriteUint32(pipelineInfo.stageCount))return(false);
    WRITE_AND_CHECK_SIZE(&tessellation, VkPipelineTessellationStateCreateInfo   );
    WRITE_AND_CHECK_SIZE(&rasterizer,   VkPipelineRasterizationStateCreateInfo  );

    WRITE_AND_CHECK_SIZE(&multisample,  VkPipelineMultisampleStateCreateInfo    );
    if(multisample.pSampleMask)
    {
        const uint count=(pipelineInfo.pMultisampleState->rasterizationSamples+31)/32;
        if(!dos->WriteUint8(count))return(false);
        if(dos->WriteUint32(sample_mask,count)!=count)return(false);
    }
    else
    {
        if(!dos->WriteUint8(0))return(false);
    }

    WRITE_AND_CHECK_SIZE(&depthStencilState,   VkPipelineDepthStencilStateCreateInfo);

    WRITE_AND_CHECK_SIZE(&colorBlending,     VkPipelineColorBlendStateCreateInfo);

    for(uint32_t i=0;i<colorBlending.attachmentCount;i++)
        WRITE_AND_CHECK_SIZE(colorBlending.pAttachments+i,VkPipelineColorBlendAttachmentState);

    if(!dos->WriteFloat(alpha_test))return(false);

    return(true);
}

#define CHECK_SIZE_AND_COPY(ptr,type)   if(size<sizeof(type))return(false); \
                                        memcpy(&ptr,data,sizeof(type));  \
                                        data+=sizeof(type); \
                                        size-=sizeof(type);

bool VKPipelineData::LoadFromMemory(uchar *data,uint size)
{
    uint16 ver=*(uint16 *)data;

    if(memcmp(data,PipelineFileHeader,PipelineFileHeaderLength)!=0)
        return(false);

    data+=PipelineFileHeaderLength;
    size-=PipelineFileHeaderLength;

    if(ver!=1)
        return(false);

    data+=sizeof(uint16);
    size-=sizeof(uint16);
    
    CHECK_SIZE_AND_COPY(pipelineInfo.stageCount,uint32_t);
    CHECK_SIZE_AND_COPY(tessellation,VkPipelineTessellationStateCreateInfo);
    CHECK_SIZE_AND_COPY(rasterizer,VkPipelineRasterizationStateCreateInfo);

    CHECK_SIZE_AND_COPY(multisample,VkPipelineMultisampleStateCreateInfo);

    const uint8 count=*(uint8 *)data;
    ++data;

    if(count>0)
    {
        memcpy(sample_mask,data,count);
        multisample.pSampleMask=sample_mask;
        data+=count;
        size=count;
    }
    else
    {
        multisample.pSampleMask=nullptr;
    }

    CHECK_SIZE_AND_COPY(depthStencilState,VkPipelineDepthStencilStateCreateInfo);
    CHECK_SIZE_AND_COPY(colorBlending,VkPipelineColorBlendStateCreateInfo);

    if(colorBlending.attachmentCount>0)
    {
        if(size<colorBlending.attachmentCount*sizeof(VkPipelineColorBlendAttachmentState))
            return(false);

        VkPipelineColorBlendAttachmentState *cba=(VkPipelineColorBlendAttachmentState *)data;

        colorBlendAttachments.SetCount(colorBlending.attachmentCount);
        memcpy(colorBlendAttachments.GetData(),data,colorBlending.attachmentCount*sizeof(VkPipelineColorBlendAttachmentState));

        colorBlending.pAttachments=colorBlendAttachments.GetData();

        for(uint i=0;i<colorBlending.attachmentCount;i++)
        {
            if(cba->blendEnable)
                alpha_blend=true;

            ++cba;
        }
    }
    else
    {
        colorBlending.pAttachments=nullptr;
        alpha_blend=false;
    }

    CHECK_SIZE_AND_COPY(alpha_test,float);
    
    pipelineInfo.pInputAssemblyState=&inputAssembly;
    pipelineInfo.pTessellationState =&tessellation;
    pipelineInfo.pRasterizationState=&rasterizer;
    pipelineInfo.pMultisampleState  =&multisample;
    pipelineInfo.pDepthStencilState =&depthStencilState;
    pipelineInfo.pColorBlendState   =&colorBlending;

    InitDynamicState();

    return(true);
}

bool SaveToFile(const OSString &filename,VKPipelineData *pd)
{
    if(filename.IsEmpty()||!pd)
        return(false);

    io::MemoryOutputStream mos;
    io::DataOutputStream *dos=new io::LEDataOutputStream(&mos);

    pd->SaveToStream(dos);

    delete dos;

    filesystem::SaveMemoryToFile(filename,mos.GetData(),mos.Tell());

    return(true);
}

bool LoadFromFile(const OSString &filename,VKPipelineData *pd)
{
    if(filename.IsEmpty()||!pd)
        return(false);

    char *data;
    uint size=filesystem::LoadFileToMemory(filename,(void **)&data);

    bool result=pd->LoadFromMemory((uchar *)data,size);

    delete[] data;
    return result;
}
VK_NAMESPACE_END
