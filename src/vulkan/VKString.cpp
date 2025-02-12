#include<hgl/graph/VKString.h>
#include<hgl/type/StrChar.h>

VK_NAMESPACE_BEGIN

template<typename E> struct VkEnumString
{
    E value;
    const char *str;
};

template<typename E> using VkEnumStringArray=VkEnumString<E>[];

class IVulkanEnumStringList
{
public:

    IVulkanEnumStringList()=default;
    virtual ~IVulkanEnumStringList()=default;

    virtual const char *to(const int &value)const=0;
    virtual const int to(const char *str,const int default_value=-1)const=0;
};//class IVulkanEnumStringList

template<typename E> IVulkanEnumStringList *VkGetEnumStringList();

template<typename E>
class VkEnumStringList:public IVulkanEnumStringList
{
    const VkEnumString<E> *list;
    int count;

    E def_value;

public:

    VkEnumStringList(const VkEnumString<E> *es_array,const int es_count,const E def)
    {
        list=es_array;
        count=es_count;
        def_value=def;
    }

    const char *to(const int &value)const override
    {
        for(int i=0;i<count;i++)
        {
            if(int(list[i].value)==value)
                return list[i].str;
        }

        return(nullptr);
    }

    const int to(const char *str,const int dv=-1)const override
    {
        for(int i=0;i<count;i++)
        {
            if(hgl::stricmp(list[i].str,str)==0)
                return int(list[i].value);
        }

        return (dv==-1)?def_value:dv;
    }
};//class VkEnumStringList

namespace
{
    const char true_string[]="true";
    const char false_string[]="false";
}

template<> const char *VkToString(const VkBool32 &value)
{
    return value?true_string:false_string;
}

template<> const VkBool32 VkToEnum(const char *str)
{
    if(hgl::stricmp(str,true_string)==0)return VK_TRUE;
    if(hgl::stricmp(str,false_string)==0)return VK_FALSE;
    return VK_FALSE;
}

template<typename E> IVulkanEnumStringList *VkGetEnumStringList();

constexpr const VkEnumString<VkPolygonMode> vk_polygon_mode_list[]=
{
    {VK_POLYGON_MODE_FILL,              "fill"},
    {VK_POLYGON_MODE_LINE,              "line"},
    {VK_POLYGON_MODE_POINT,             "point"},
    {VK_POLYGON_MODE_FILL_RECTANGLE_NV, "fill_rectangle"},
};

#define VK_ENUM_STRING_LIST(VK_TYPE,VK_LIST,VK_DEFAULT)    \
    static VkEnumStringList<Vk##VK_TYPE> Vk##VK_TYPE##ESL(vk_##VK_LIST##_list,sizeof(vk_##VK_LIST##_list)/sizeof(VkEnumString<Vk##VK_TYPE>),VK_DEFAULT);   \
    template<> IVulkanEnumStringList *VkGetEnumStringList<Vk##VK_TYPE>(){return &Vk##VK_TYPE##ESL;} \
    template<> const char *VkToString(const Vk##VK_TYPE &value){return Vk##VK_TYPE##ESL.to(value);} \
    template<> const Vk##VK_TYPE VkToEnum(const char *str){return (Vk##VK_TYPE)Vk##VK_TYPE##ESL.to(str);}

VK_ENUM_STRING_LIST(PolygonMode,polygon_mode,VK_POLYGON_MODE_FILL)

constexpr const VkEnumString<VkCullModeFlagBits> vk_cull_mode_list[]=
{
    {VK_CULL_MODE_NONE,                 "none"},
    {VK_CULL_MODE_FRONT_BIT,            "front"},
    {VK_CULL_MODE_BACK_BIT,             "back"},
    {VK_CULL_MODE_FRONT_AND_BACK,       "front_and_back"},
};

VK_ENUM_STRING_LIST(CullModeFlagBits,cull_mode,VK_CULL_MODE_BACK_BIT)

constexpr const VkEnumString<VkFrontFace> vk_front_face_list[]=
{
    {VK_FRONT_FACE_COUNTER_CLOCKWISE,   "ccw"},
    {VK_FRONT_FACE_CLOCKWISE,           "cw"},

    {VK_FRONT_FACE_COUNTER_CLOCKWISE,   "CounterClockWise"},
    {VK_FRONT_FACE_CLOCKWISE,           "CloseWise"},
};

VK_ENUM_STRING_LIST(FrontFace,front_face,VK_FRONT_FACE_CLOCKWISE)

constexpr const VkEnumString<VkStencilOp> vk_stencil_op_list[]=
{
    {VK_STENCIL_OP_KEEP,                "keep"},

    {VK_STENCIL_OP_ZERO,                "zero"},
    {VK_STENCIL_OP_ZERO,                "0"},

    {VK_STENCIL_OP_REPLACE,             "replace"},

    {VK_STENCIL_OP_INCREMENT_AND_CLAMP, "inc_clamp"},
    {VK_STENCIL_OP_DECREMENT_AND_CLAMP, "dec_clamp"},

    {VK_STENCIL_OP_INCREMENT_AND_CLAMP, "+clamp"},
    {VK_STENCIL_OP_DECREMENT_AND_CLAMP, "-clamp"},

    {VK_STENCIL_OP_INVERT,              "invert"},

    {VK_STENCIL_OP_INCREMENT_AND_WRAP,  "inc_wrap"},
    {VK_STENCIL_OP_DECREMENT_AND_WRAP,  "dec_wrap"},

    {VK_STENCIL_OP_INCREMENT_AND_WRAP,  "+wrap"},
    {VK_STENCIL_OP_DECREMENT_AND_WRAP,  "-wrap"},
};

VK_ENUM_STRING_LIST(StencilOp,stencil_op,VK_STENCIL_OP_KEEP)

constexpr const VkEnumString<VkCompareOp> vk_compare_op_list[]=
{
    {VK_COMPARE_OP_NEVER,               "never"},

    {VK_COMPARE_OP_LESS,                "less"},
    {VK_COMPARE_OP_EQUAL,               "equal"},
    {VK_COMPARE_OP_LESS_OR_EQUAL,       "less_or_equal"},
    {VK_COMPARE_OP_GREATER,             "greater"},
    {VK_COMPARE_OP_NOT_EQUAL,           "not_equal"},
    {VK_COMPARE_OP_GREATER_OR_EQUAL,    "greater_or_equal"},

    {VK_COMPARE_OP_LESS,                "<"},
    {VK_COMPARE_OP_EQUAL,               "=="},
    {VK_COMPARE_OP_LESS_OR_EQUAL,       "<="},
    {VK_COMPARE_OP_GREATER,             ">"},
    {VK_COMPARE_OP_NOT_EQUAL,           "!="},
    {VK_COMPARE_OP_GREATER_OR_EQUAL,    ">="},

    {VK_COMPARE_OP_ALWAYS,              "always"},
};

VK_ENUM_STRING_LIST(CompareOp,compare_op,VK_COMPARE_OP_NEVER)

constexpr const VkEnumString<VkLogicOp> vk_logic_op_list[]=
{
    {VK_LOGIC_OP_CLEAR,                 "clear"},
    {VK_LOGIC_OP_AND,                   "and"},
    {VK_LOGIC_OP_AND_REVERSE,           "and_reverse"},
    {VK_LOGIC_OP_COPY,                  "copy"},
    {VK_LOGIC_OP_AND_INVERTED,          "and_inverted"},
    {VK_LOGIC_OP_NO_OP,                 "no_op"},
    {VK_LOGIC_OP_XOR,                   "xor"},
    {VK_LOGIC_OP_OR,                    "or"},
    {VK_LOGIC_OP_NOR,                   "nor"},
    {VK_LOGIC_OP_EQUIVALENT,            "equivalent"},
    {VK_LOGIC_OP_INVERT,                "invert"},
    {VK_LOGIC_OP_OR_REVERSE,            "or_reverse"},
    {VK_LOGIC_OP_COPY_INVERTED,         "copy_inverted"},
    {VK_LOGIC_OP_OR_INVERTED,           "or_inverted"},
    {VK_LOGIC_OP_NAND,                  "nand"},
    {VK_LOGIC_OP_SET,                   "set"},
};

VK_ENUM_STRING_LIST(LogicOp,logic_op,VK_LOGIC_OP_CLEAR)

constexpr const VkEnumString<VkBlendFactor> vk_blend_factor_list[]=
{
    {VK_BLEND_FACTOR_ZERO,                      "zero"},
    {VK_BLEND_FACTOR_ONE,                       "one"},

    {VK_BLEND_FACTOR_ZERO,                      "0"},
    {VK_BLEND_FACTOR_ONE,                       "1"},

    {VK_BLEND_FACTOR_SRC_COLOR,                 "src_color"},
    {VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR,       "one_minus_src_color"},
    {VK_BLEND_FACTOR_DST_COLOR,                 "dst_color"},
    {VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR,       "one_minus_dst_color"},
    {VK_BLEND_FACTOR_SRC_ALPHA,                 "src_alpha"},
    {VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,       "one_minus_src_alpha"},
    {VK_BLEND_FACTOR_DST_ALPHA,                 "dst_alpha"},
    {VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA,       "one_minus_dst_alpha"},
    {VK_BLEND_FACTOR_CONSTANT_COLOR,            "constant_color"},
    {VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR,  "one_minus_constant_color"},
    {VK_BLEND_FACTOR_CONSTANT_ALPHA,            "constant_alpha"},
    {VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA,  "one_minus_constant_alpha"},
    {VK_BLEND_FACTOR_SRC_ALPHA_SATURATE,        "src_alpha_saturate"},
    {VK_BLEND_FACTOR_SRC1_COLOR,                "src1_color"},
    {VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR,      "one_minus_src1_color"},
    {VK_BLEND_FACTOR_SRC1_ALPHA,                "src1_alpha"},
    {VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA,      "one_minus_src1_alpha"},
};

VK_ENUM_STRING_LIST(BlendFactor,blend_factor,VK_BLEND_FACTOR_ZERO)

constexpr const VkEnumString<VkBlendOp> vk_blend_op_list[]=
{
    {VK_BLEND_OP_ADD,               "add"},
    {VK_BLEND_OP_SUBTRACT,          "subtract"},
    {VK_BLEND_OP_REVERSE_SUBTRACT,  "reverse_subtract"},
    {VK_BLEND_OP_MIN,               "min"},
    {VK_BLEND_OP_MAX,               "max"},
    {VK_BLEND_OP_ZERO_EXT,          "zero"},
    {VK_BLEND_OP_SRC_EXT,           "src"},
    {VK_BLEND_OP_DST_EXT,           "dst"},
    {VK_BLEND_OP_SRC_OVER_EXT,      "src_over"},
    {VK_BLEND_OP_DST_OVER_EXT,      "dst_over"},
    {VK_BLEND_OP_SRC_IN_EXT,        "src_in"},
    {VK_BLEND_OP_DST_IN_EXT,        "dst_in"},
    {VK_BLEND_OP_SRC_OUT_EXT,       "src_out"},
    {VK_BLEND_OP_DST_OUT_EXT,       "dst_out"},
    {VK_BLEND_OP_SRC_ATOP_EXT,      "src_atop"},
    {VK_BLEND_OP_DST_ATOP_EXT,      "dst_atop"},
    {VK_BLEND_OP_XOR_EXT,           "xor"},
    {VK_BLEND_OP_MULTIPLY_EXT,      "multiply"},
    {VK_BLEND_OP_SCREEN_EXT,        "screen"},
    {VK_BLEND_OP_OVERLAY_EXT,       "overlay"},
    {VK_BLEND_OP_DARKEN_EXT,        "darken"},
    {VK_BLEND_OP_LIGHTEN_EXT,       "lighten"},
    {VK_BLEND_OP_COLORDODGE_EXT,    "colordodge"},
    {VK_BLEND_OP_COLORBURN_EXT,     "colorburn"},
    {VK_BLEND_OP_HARDLIGHT_EXT,     "hardlight"},
    {VK_BLEND_OP_SOFTLIGHT_EXT,     "softlight"},
    {VK_BLEND_OP_DIFFERENCE_EXT,    "difference"},
    {VK_BLEND_OP_EXCLUSION_EXT,     "exclusion"},
    {VK_BLEND_OP_INVERT_EXT,        "invert"},
    {VK_BLEND_OP_INVERT_RGB_EXT,    "invert_rgb"},
    {VK_BLEND_OP_LINEARDODGE_EXT,   "lineardodge"},
    {VK_BLEND_OP_LINEARBURN_EXT,    "linearburn"},
    {VK_BLEND_OP_VIVIDLIGHT_EXT,    "vividlight"},
    {VK_BLEND_OP_LINEARLIGHT_EXT,   "linearlight"},
    {VK_BLEND_OP_PINLIGHT_EXT,      "pinlight"},
    {VK_BLEND_OP_HARDMIX_EXT,       "hardmix"},
    {VK_BLEND_OP_HSL_HUE_EXT,       "hsl_hue"},
    {VK_BLEND_OP_HSL_SATURATION_EXT,"hsl_saturation"},
    {VK_BLEND_OP_HSL_COLOR_EXT,     "hsl_color"},
    {VK_BLEND_OP_HSL_LUMINOSITY_EXT,"hsl_luminosity"},
    {VK_BLEND_OP_PLUS_EXT,          "plus"},
    {VK_BLEND_OP_PLUS_CLAMPED_EXT,  "plus_clamped"},
    {VK_BLEND_OP_PLUS_CLAMPED_ALPHA_EXT,"plus_clamped_alpha"},
    {VK_BLEND_OP_PLUS_DARKER_EXT,   "plus_darker"},
    {VK_BLEND_OP_MINUS_EXT,         "minus"},
    {VK_BLEND_OP_MINUS_CLAMPED_EXT, "minus_clamped"},
    {VK_BLEND_OP_CONTRAST_EXT,      "contrast"},
    {VK_BLEND_OP_INVERT_OVG_EXT,    "invert_ovg"},
    {VK_BLEND_OP_RED_EXT,           "red"},
    {VK_BLEND_OP_GREEN_EXT,         "green"},
    {VK_BLEND_OP_BLUE_EXT,          "blue"}
};

VK_ENUM_STRING_LIST(BlendOp,blend_op,VK_BLEND_OP_ADD)

VK_NAMESPACE_END
