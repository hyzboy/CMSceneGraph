#include<hgl/graph/VKPrimitiveType.h>
#include<hgl/type/StrChar.h>

namespace
{
    struct PrimitiveNameInfo
    {
        const char *name;
        const int   len;
        Prim        prim;
    };

    #define PRIM_NAME(L,S) {S,sizeof(S)-1,Prim::L}

    constexpr const PrimitiveNameInfo PrimitiveInfoList[]=
    {
        PRIM_NAME(Points,           "points"),
        PRIM_NAME(Lines,            "lines"),
        PRIM_NAME(LineStrip,        "line_strip"),
        PRIM_NAME(Triangles,        "triangles"),
        PRIM_NAME(TriangleStrip,    "triangle_strip"),
        PRIM_NAME(Fan,              "fan"),
        PRIM_NAME(LinesAdj,         "lines_adjacency"),
        PRIM_NAME(LineStripAdj,     "line_strip_adjacency"),
        PRIM_NAME(TrianglesAdj,     "triangles_adjacency"),
        PRIM_NAME(TriangleStripAdj, "triangle_strip_adjacency"),
        PRIM_NAME(Patchs,           "patchs"),
    
        PRIM_NAME(SolidRectangles,  "solid_rectangles"),
        PRIM_NAME(WireRectangles,   "wire_rectangles"),
        PRIM_NAME(SolidCube,        "solid_cube"),
        PRIM_NAME(WireCube,         "wire_cube")
    };

    #undef PRIM_NAME
}//namespace

const char *GetPrimName(const Prim &prim)
{
    for(const auto &pni:PrimitiveInfoList)
        if(pni.prim==prim)
            return pni.name;

    return nullptr;
}

const Prim ParsePrimName(const char *name,int len)
{
    if(!name||!*name)return Prim::Error;

    if(len==0)
        len=hgl::strlen(name);

    for(const auto &pni:PrimitiveInfoList)
    {
        if(!hgl::stricmp(pni.name,name,len))
            return pni.prim;
    }

    return Prim::Error;
}

bool CheckGeometryShaderIn(const Prim &ip)
{
    if(ip==Prim::Points)return(true);
    if(ip==Prim::Lines)return(true);
    if(ip==Prim::LinesAdj)return(true);
    if(ip==Prim::Triangles)return(true);
    if(ip==Prim::TrianglesAdj)return(true);

    return(false);
}

bool CheckGeometryShaderOut(const Prim &op)
{
    if(op==Prim::Points)return(true);
    if(op==Prim::LineStrip)return(true);
    if(op==Prim::TriangleStrip)return(true);

    return(false);
}
