#ifndef HGL_GRAPH_SHADER_DESCRIPTOR_INCLUDE
#define HGL_GRAPH_SHADER_DESCRIPTOR_INCLUDE

#include<hgl/type/String.h>
#include<hgl/type/ArrayList.h>
#include<hgl/graph/VKDescriptorSetType.h>

namespace hgl
{
    namespace graph
    {
        constexpr size_t DESCRIPTOR_NAME_MAX_LENGTH=32;

        struct ShaderDescriptor:public Comparator<ShaderDescriptor>
        {
            char name[DESCRIPTOR_NAME_MAX_LENGTH];
            VkDescriptorType desc_type;
            DescriptorSetType set_type;

            int set;
            int binding;
            uint32_t stage_flag;

        public:

            ShaderDescriptor()
            {
                hgl_zero(*this);
                set=-1;
                binding=-1;
                stage_flag=0;
            }

            ShaderDescriptor(const ShaderDescriptor *sr)
            {
                if(!sr)
                {
                    hgl_zero(*this);

                    set=-1;
                    binding=-1;
                }
                else
                    hgl_cpy(*this,*sr);
            }

            virtual ~ShaderDescriptor()=default;

            const int compare(const ShaderDescriptor &sr)const override
            {
                if(set!=sr.set)return sr.set-set;
                if(binding!=sr.binding)return sr.binding-binding;

                return strcmp(name,sr.name);
            }
        };//struct ShaderDescriptor

        using ShaderDescriptorList=ArrayList<ShaderDescriptor *>;

        struct UBODescriptor:public ShaderDescriptor
        {
            AnsiString type;

        public:

            UBODescriptor()
            {
                desc_type=VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            }
        };

        struct SamplerDescriptor:public ShaderDescriptor
        {
            AnsiString type;

        public:

            SamplerDescriptor()
            {
                desc_type=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            }
        };

        /**
         * 未归类的描述符对象，暂没想好怎么命名
         */
        struct ShaderObjectData:public ShaderDescriptor
        {
            AnsiString type;
        };

        struct ConstValueDescriptor
        {
            int constant_id;

            AnsiString type;
            AnsiString name;
            AnsiString value;
        };

        struct SubpassInputDescriptor
        {
            AnsiString name;
            uint8_t input_attachment_index;
            uint8_t binding;
        };

        struct ShaderPushConstant
        {
            AnsiString name;
            uint8_t offset;
            uint8_t size;
        };
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_SHADER_DESCRIPTOR_INCLUDE
