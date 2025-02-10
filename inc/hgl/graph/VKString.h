#pragma once

#include<hgl/graph/VKNamespace.h>
#include<vulkan/vulkan.h>

VK_NAMESPACE_BEGIN

// the following enum are to support

// VkPolygonMode
// VkCullModeFlagBits
// VkFrontFace
// VkStencilOp
// VkCompareOp
// VkLogicOp
// VkBlendFactor
// VkBlendOp

template<typename E> const char *VkToString(const E &value);
template<typename E> const E VkToEnum(const char *);

VK_NAMESPACE_END
