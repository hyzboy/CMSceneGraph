﻿#ifndef HGL_GRAPH_SHADER_DESCRIPTOR_INCLUDE
#define HGL_GRAPH_SHADER_DESCRIPTOR_INCLUDE

#include<hgl/type/String.h>
#include<hgl/type/List.h>
#include<hgl/graph/VKDescriptorSetType.h>

namespace hgl
{
    namespace graph
    {
        constexpr size_t DESCRIPTOR_NAME_MAX_LENGTH=128;

        struct ShaderDescriptor
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

            const int Comp(const ShaderDescriptor &sr)const
            {
                if(set!=sr.set)return sr.set-set;
                if(binding!=sr.binding)return sr.binding-binding;

                return strcmp(name,sr.name);
            }

            CompOperator(const ShaderDescriptor &,Comp);
        };//struct ShaderDescriptor

        using ShaderDescriptorList=List<ShaderDescriptor *>;

        struct UBODescriptor:public ShaderDescriptor
        {
            AnsiString type;
            AnsiString name;
        };

        struct SamplerDescriptor:public ShaderDescriptor
        {
            AnsiString type;
            AnsiString name;
        };

        /**
         * 未归类的描述符对象，暂没想好怎么命名
         */
        struct ShaderObjectData:public ShaderDescriptor
        {
            AnsiString type;
            AnsiString name;
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
