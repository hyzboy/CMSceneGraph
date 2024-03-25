#pragma once
#include<hgl/graph/VKFormat.h>
#include<hgl/graph/VertexAttrib.h>

VK_NAMESPACE_BEGIN

constexpr const char        MI_VIS_NAME[]       ="MaterialInstanceID";

constexpr const VAT         MI_VAT_FMT          =VAT_UINT;

constexpr const VkFormat    MI_VBO_FMT          =VF_V1U16;

constexpr const uint        MI_VBO_STRIDE_BYTES =2;     ///<材质实例ID VBO的每个节点的字节数

VK_NAMESPACE_END
