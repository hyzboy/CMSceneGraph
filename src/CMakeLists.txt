file(GLOB CM_SCENEGRAPH_HEADER ${CMSCENEGRAPH_ROOT_INCLUDE_PATH}/hgl/graph/*.*)
file(GLOB CM_SCENEGRAPH_VULKAN_HEADER ${CMSCENEGRAPH_ROOT_INCLUDE_PATH}/hgl/graph/vulkan/*.*)

file(GLOB CM_SCENEGRAPH_SOURCE *.*)
file(GLOB CM_SCENEGRAPH_VULKAN_SOURCE vulkan/*.*)

source_group("SceneGraph" FILES ${CM_SCENEGRAPH_HEADER} ${CM_SCENEGRAPH_SOURCE})
source_group("SceneGraph\\Vulkan" FILES ${CM_SCENEGRAPH_VULKAN_HEADER} ${CM_SCENEGRAPH_VULKAN_SOURCE})

add_cm_library(CMSceneGraph "CM"    ${CM_SCENEGRAPH_HEADER}
                                    ${CM_SCENEGRAPH_SOURCE}
                                    ${CM_SCENEGRAPH_VULKAN_HEADER}
                                    ${CM_SCENEGRAPH_VULKAN_SOURCE})
