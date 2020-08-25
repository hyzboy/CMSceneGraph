#include<hgl/graph/VertexAttrib.h>

namespace hgl
{
    namespace graph
    {
        bool ParseVertexAttribType(VertexAttribType *vat,const char *str)
        {
            if(!vat||!str||!*str)return(false);

            if(*str=='v')
            {
                vat->basetype=VertexAttribBaseType::Float;
                vat->vec_size=str[3]-'0';
            }
            else
            {
                if(*str=='f')vat->basetype=VertexAttribBaseType::Bool;else
                if(*str=='i')vat->basetype=VertexAttribBaseType::Bool;else
                if(*str=='u')vat->basetype=VertexAttribBaseType::Bool;else
                if(*str=='b')vat->basetype=VertexAttribBaseType::Bool;else
                if(*str=='d')vat->basetype=VertexAttribBaseType::Bool;else
                    return(false);

                if(str[1]!='v')
                {
                    vat->vec_size=1;
                    return(true);
                }
                
                vat->vec_size=str[4]-'0';
            }

            if(vat->vec_size<1
             ||vat->vec_size>4)return(false);

            return(true);
        }

        constexpr char vertex_attrib_vec_name[size_t(VertexAttribBaseType::RANGE_SIZE)][4][8]=
        {
            {"bool",  "bvec2","bvec3","bvec4"},
            {"int",   "ivec2","ivec3","ivec4"},
            {"uint",  "uvec2","uvec3","uvec4"},
            {"float",  "vec2", "vec3", "vec4"},
            {"double","dvec2","dvec3","dvec4"}
        };

        const char *GetVertexAttribName(const VertexAttribType *type)
        {
            if(!type||!type->Check())return(nullptr);            

            return vertex_attrib_vec_name[size_t(type->basetype)][type->vec_size-1];
        }
    }//namespace graph
}//namespace hgl
