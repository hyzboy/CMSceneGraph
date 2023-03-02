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

        constexpr size_t SHADER_RESOURCE_NAME_MAX_LENGTH=128;

        struct ShaderStage
        {
            //注：这个类要从GLSLCompiler动态链接库中直接传递，所以不可以使用AnsiString

            char    name[SHADER_RESOURCE_NAME_MAX_LENGTH];
            uint8   location;

            //对应hgl/graph/VertexAttrib.h中的enum class VertexAttribType::BaseType
            uint8_t basetype;
            uint8_t vec_size;
        };//struct ShaderStage

        inline const char *GetShaderStageTypeName(ShaderStage *ss)
        {
            return GetVertexAttribName((VertexAttribType::BaseType)ss->basetype,ss->vec_size);
        }

        using ShaderStageList=ObjectList<ShaderStage>;
    
        struct ShaderStageIO
        {
            VkShaderStageFlagBits prev,cur,next;
            ShaderStageList input,output;

        public:

            ShaderStageIO()
            {
                prev=cur=next=(VkShaderStageFlagBits)0;
            }

            void Clear()
            {
                input.Clear();
                output.Clear();
            }
        };//struct ShaderStageIO
    }//namespace graph
}//namespace hgl
#endif//HGL_SHADER_GEN_SHADER_STAGE_INCLUDE
