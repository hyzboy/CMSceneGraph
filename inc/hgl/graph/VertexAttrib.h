﻿#ifndef HGL_GRAPH_VERTEX_ATTRIB_INCLUDE
#define HGL_GRAPH_VERTEX_ATTRIB_INCLUDE

#include<hgl/TypeFunc.h>
namespace hgl
{
    namespace graph
    {
        enum class VertexInputGroup:uint8
        {
            Basic,

            LocalToWorld,
            MaterialInstanceID,
            JointID,
            JointWeight,

            ENUM_CLASS_RANGE(Basic,JointWeight)
        };

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

            int Comp(const VertexAttribType &vat)const
            {
                int off=(int)basetype-(int)vat.basetype;
    
                if(off)return(off);

                off=vec_size-vat.vec_size;

                return(off);
            }

            const bool operator > (const VertexAttribType& i)const {return Comp(i)>0;}
            const bool operator < (const VertexAttribType& i)const {return Comp(i)<0;}
            const bool operator >=(const VertexAttribType& i)const {return Comp(i) >= 0;}
            const bool operator <=(const VertexAttribType& i)const {return Comp(i) <= 0;}
            const bool operator ==(const VertexAttribType& i)const {return Comp(i) == 0;}
            const bool operator !=(const VertexAttribType& i)const {return Comp(i) != 0;}
        };//struct VAT

        using VAT=VertexAttribType;
        using VATBaseType=VertexAttribType::BaseType;

        /**
         * 根据字符串解晰顶点属性类型
         */
        bool ParseVertexAttribType(VAT *,const char *);

        const char *GetVertexAttribName(const VATBaseType &base_type,const uint vec_size);
        const char *GetVertexAttribName(const VAT *type);

        constexpr const VAT VAT_BOOL ={VATBaseType::Bool,1};
        constexpr const VAT VAT_BVEC2={VATBaseType::Bool,2};
        constexpr const VAT VAT_BVEC3={VATBaseType::Bool,3};
        constexpr const VAT VAT_BVEC4={VATBaseType::Bool,4};

        constexpr const VAT VAT_INT  ={VATBaseType::Int,1};
        constexpr const VAT VAT_IVEC2={VATBaseType::Int,2};
        constexpr const VAT VAT_IVEC3={VATBaseType::Int,3};
        constexpr const VAT VAT_IVEC4={VATBaseType::Int,4};

        constexpr const VAT VAT_UINT ={VATBaseType::UInt,1};
        constexpr const VAT VAT_UVEC2={VATBaseType::UInt,2};
        constexpr const VAT VAT_UVEC3={VATBaseType::UInt,3};
        constexpr const VAT VAT_UVEC4={VATBaseType::UInt,4};

        constexpr const VAT VAT_FLOAT={VATBaseType::Float,1};
        constexpr const VAT VAT_VEC2 ={VATBaseType::Float,2};
        constexpr const VAT VAT_VEC3 ={VATBaseType::Float,3};
        constexpr const VAT VAT_VEC4 ={VATBaseType::Float,4};

        constexpr const VAT VAT_DOUBLE={VATBaseType::Double,1};
        constexpr const VAT VAT_DVEC2 ={VATBaseType::Double,2};
        constexpr const VAT VAT_DVEC3 ={VATBaseType::Double,3};
        constexpr const VAT VAT_DVEC4 ={VATBaseType::Double,4};

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
            VAN_DEFINE(Luminance)

            VAN_DEFINE(LocalToWorld)
            VAN_DEFINE(MaterialInstanceID)

            VAN_DEFINE(JointID)
            VAN_DEFINE(JointWeight)
            #undef VAN_DEFINE
        }//namespace VertexAttribName

        #define VAN VertexAttribName
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_VERTEX_ATTRIB_INCLUDE
