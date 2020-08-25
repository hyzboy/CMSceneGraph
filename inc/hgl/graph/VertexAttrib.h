#ifndef HGL_GRAPH_VERTEX_ATTRIB_INCLUDE
#define HGL_GRAPH_VERTEX_ATTRIB_INCLUDE

#include<hgl/TypeFunc.h>
namespace hgl
{
    namespace graph
    {
        enum class VertexAttribBaseType
        {
            Bool=0,
            Int,
            UInt,
            Float,
            Double,

            ENUM_CLASS_RANGE(Bool,Double)
        };//enum class VertexAttribBaseType

        struct VertexAttribType
        {
            VertexAttribBaseType basetype;
            uint vec_size;

        public:

            const bool Check()const
            {
                if(basetype<VertexAttribBaseType::Bool
                 ||basetype>VertexAttribBaseType::Double)return(false);

                if(vec_size<=0||vec_size>4)return(false);

                return(true);
            }

            const size_t GetStride()const
            {
                constexpr size_t stride[5]={1,4,4,4,8};

                return stride[size_t(basetype)]*vec_size;
            }
        };//struct VertexAttribType

        /**
         * 根据字符串解晰顶点属性类型
         */
        bool ParseVertexAttribType(VertexAttribType *,const char *);
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_VERTEX_ATTRIB_INCLUDE
