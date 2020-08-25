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
        };//struct VertexAttribType

        /**
         * 根据字符串解晰顶点属性类型
         */
        bool ParseVertexAttribType(VertexAttribType *,const char *);
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_VERTEX_ATTRIB_INCLUDE
