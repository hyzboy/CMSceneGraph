#ifndef HGL_GRAPH_VERTEX_ATTRIB_INCLUDE
#define HGL_GRAPH_VERTEX_ATTRIB_INCLUDE

#include<hgl/TypeFunc.h>
namespace hgl
{
    namespace graph
    {
        struct VertexAttribType
        {
            enum class BaseType
            {
                Bool=0,
                Int,
                UInt,
                Float,
                Double,

                ENUM_CLASS_RANGE(Bool,Double)
            };//enum class BaseType

            BaseType basetype;
            uint vec_size;

        public:

            const bool Check()const
            {
                if(basetype<BaseType::Bool
                 ||basetype>BaseType::Double)return(false);

                if(vec_size<=0||vec_size>4)return(false);

                return(true);
            }

            const uint32 GetStride()const
            {
                constexpr uint32 stride[5]={1,4,4,4,8};

                return stride[uint32(basetype)]*vec_size;
            }
        };//struct VAT

        using VAT=VertexAttribType;
        using VATBaseType=VertexAttribType::BaseType;

        /**
         * 根据字符串解晰顶点属性类型
         */
        bool ParseVertexAttribType(VAT *,const char *);

        const char *GetVertexAttribName(const VATBaseType &base_type,const uint vec_size);
        const char *GetVertexAttribName(const VAT *type);

        const VAT VAT_BOOL ={VATBaseType::Bool,1};
        const VAT VAT_BVEC2={VATBaseType::Bool,2};
        const VAT VAT_BVEC3={VATBaseType::Bool,3};
        const VAT VAT_BVEC4={VATBaseType::Bool,4};

        const VAT VAT_INT  ={VATBaseType::Int,1};
        const VAT VAT_IVEC2={VATBaseType::Int,2};
        const VAT VAT_IVEC3={VATBaseType::Int,3};
        const VAT VAT_IVEC4={VATBaseType::Int,4};

        const VAT VAT_UINT ={VATBaseType::UInt,1};
        const VAT VAT_UVEC2={VATBaseType::UInt,2};
        const VAT VAT_UVEC3={VATBaseType::UInt,3};
        const VAT VAT_UVEC4={VATBaseType::UInt,4};

        const VAT VAT_FLOAT={VATBaseType::Float,1};
        const VAT VAT_VEC2 ={VATBaseType::Float,2};
        const VAT VAT_VEC3 ={VATBaseType::Float,3};
        const VAT VAT_VEC4 ={VATBaseType::Float,4};

        const VAT VAT_DOUBLE={VATBaseType::Double,1};
        const VAT VAT_DVEC2 ={VATBaseType::Double,2};
        const VAT VAT_DVEC3 ={VATBaseType::Double,3};
        const VAT VAT_DVEC4 ={VATBaseType::Double,4};

        /**
         * 顶点输入流配置
         */
        union VertexInputStreamConfig
        {
            struct
            {
                bool Position       :1;
                bool Normal         :1;
                bool Tangnet        :1;
                bool Bitangent      :1;

                uint TexCoord       :4;
                uint Color          :4;

                bool Bone           :1;
                bool LocalToWorld   :1;
            };

            uint32 config;
        };

        /**
        * 计算指定配置下需要的流数量
        */
        const uint GetVertexInputStreamCount(const VertexInputStreamConfig &);

        /**
         * 预定义一些顶点属性名称，可用可不用。但一般默认shader会使用这些名称
         */
        namespace VertexAttribName
        {
            #define VAN_DEFINE(name)    constexpr char name[]=#name;
            VAN_DEFINE(Position)
            VAN_DEFINE(Normal)
            VAN_DEFINE(Tangent)
            VAN_DEFINE(Bitangent)
            VAN_DEFINE(TexCoord)
            VAN_DEFINE(Color)
            VAN_DEFINE(BoneID)
            VAN_DEFINE(BoneWeight)

            VAN_DEFINE(LocalToWorld)
            #undef VAN_DEFINE
        }//namespace VertexAttribName

        #define VAN VertexAttribName
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_VERTEX_ATTRIB_INCLUDE
