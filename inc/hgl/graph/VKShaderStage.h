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
            uint8   basetype;
            uint8   vec_size;

            uint8               input_rate;     //输入频率
            VertexInputGroup    group;          //分组

            Interpolation       interpolation;  //插值方式
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

        public:

            int Comp(const ShaderAttributeArray *saa)const
            {
                if(!saa)
                    return 1;

                int off=count-saa->count;
                if(off)return off;

                for(uint i=0;i<count;i++)
                {
                #define SAA_COMP_ITEM(name) off=items[i].name-saa->items[i].name;if(off)return off;
                    SAA_COMP_ITEM(location)
                    SAA_COMP_ITEM(basetype)
                    SAA_COMP_ITEM(vec_size)
                    SAA_COMP_ITEM(input_rate)
                #undef SAA_COMP_ITEM
                }

                return 0;
            }

            CompOperator(const ShaderAttributeArray *,Comp)
        };

        inline void Init(ShaderAttributeArray *sad,const uint count=0)
        {
            sad->count=count;

            if(count>0)
                sad->items=array_alloc<ShaderAttribute>(count);
            else
                sad->items=nullptr;
        }

        inline void Clear(ShaderAttributeArray *sad)
        {
            if(sad->items)
                array_free(sad->items);

            sad->count=0;
            sad->items=nullptr;
        }

        inline void Copy(ShaderAttributeArray *dst,const ShaderAttributeArray *src)
        {
            Init(dst,src->count);

            if(src->count>0)
                hgl_cpy(dst->items,src->items,src->count);
        }

        inline void Append(ShaderAttributeArray *sad,ShaderAttribute *sa)
        {
            if(!sad->items)
            {
                sad->items=array_alloc<ShaderAttribute>(1);
                sad->count=1;
            }
            else
            {
                sad->items=array_realloc(sad->items,sad->count+1);
                sad->count++;
            }

            memcpy(sad->items+sad->count-1,sa,sizeof(ShaderAttribute));
        }

        struct ShaderStageIO
        {
            ShaderAttributeArray input,output;
        };//struct ShaderStageIO

        inline void Init(ShaderStageIO &io)
        {
            Init(&io.input);
            Init(&io.output);
        }

        inline void Clear(ShaderStageIO &io)
        {
            Clear(&io.input);
            Clear(&io.output);
        }

        inline void Copy(ShaderStageIO *dst,const ShaderStageIO *src)
        {
            Copy(&(dst->input),&(src->input));
            Copy(&(dst->output),&(src->output));
        }
    }//namespace graph
}//namespace hgl
#endif//HGL_SHADER_GEN_SHADER_STAGE_INCLUDE
