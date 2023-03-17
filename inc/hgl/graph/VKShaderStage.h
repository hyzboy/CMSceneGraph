#ifndef HGL_SHADER_GEN_SHADER_STAGE_INCLUDE
#define HGL_SHADER_GEN_SHADER_STAGE_INCLUDE

#include<hgl/graph/VertexAttrib.h>
#include<hgl/graph/VKInterpolation.h>
#include<hgl/type/List.h>

namespace hgl
{
    namespace graph
    {
        const uint GetShaderCountByBits(const uint32_t bits);                   ///<根据ShaderStage位数据统计有多少个shader
        const char *GetShaderStageName(const VkShaderStageFlagBits &);          ///<获取指定ShaderStage位的名称

        constexpr size_t SHADER_RESOURCE_NAME_MAX_LENGTH=32;

        struct ShaderAttribute
        {
            //注：这个类要从GLSLCompiler动态链接库中直接传递，所以不可以使用AnsiString

            char    name[SHADER_RESOURCE_NAME_MAX_LENGTH];
            uint8   location;

            //对应hgl/graph/VertexAttrib.h中的enum class VATBaseType
            uint8_t basetype;
            uint8_t vec_size;
        };//struct ShaderAttribute

        inline const AnsiString GetShaderAttributeTypename(const ShaderAttribute *ss)
        {
            return AnsiString(GetVertexAttribName((VATBaseType)ss->basetype,ss->vec_size));
        }

        const VkFormat GetVulkanFormat(const ShaderAttribute *sa);

        struct ShaderAttributeArray
        {
            uint32_t count;
            ShaderAttribute *items;
        };

        inline void Init(ShaderAttributeArray &sad,const uint count=0)
        {
            sad.count=count;

            if(count>0)
                sad.items=array_alloc<ShaderAttribute>(count);
            else
                sad.items=nullptr;
        }

        inline void Clear(ShaderAttributeArray &sad)
        {
            if(sad.items)
                array_free(sad.items);

            sad.count=0;
            sad.items=nullptr;
        }

        inline void Append(ShaderAttributeArray &sad,ShaderAttribute *sa)
        {
            if(!sad.items)
            {
                sad.items=array_alloc<ShaderAttribute>(1);
                sad.count=1;
            }
            else
            {
                sad.items=array_realloc(sad.items,sad.count+1);
                sad.count++;
            }

            memcpy(sad.items+sad.count-1,sa,sizeof(ShaderAttribute));
        }

        struct ShaderStageIO
        {
            ShaderAttributeArray input,output;
        };//struct ShaderStageIO

        inline void Init(ShaderStageIO &io)
        {
            Init(io.input);
            Init(io.output);
        }

        inline void Clear(ShaderStageIO &io)
        {
            Clear(io.input);
            Clear(io.output);
        }
    }//namespace graph
}//namespace hgl
#endif//HGL_SHADER_GEN_SHADER_STAGE_INCLUDE
