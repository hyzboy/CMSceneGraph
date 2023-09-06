#pragma once
#include<hgl/graph/VKFormat.h>
#include<hgl/graph/VertexAttrib.h>

VK_NAMESPACE_BEGIN

constexpr const char        ASSIGN_VIS_NAME[]       ="Assign";

constexpr const VAT         ASSIGN_VAT_FMT          =VAT_UINT;

constexpr const VkFormat    ASSIGN_VBO_FMT          =VF_V1U16;

constexpr const uint        ASSIGN_VBO_STRIDE_BYTES =2;     ///<Assign VBO的每个节点的字节数

VK_NAMESPACE_END
