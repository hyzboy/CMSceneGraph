SET(CM_SG_INCLUDE_PATH  ${CMSCENEGRAPH_ROOT_INCLUDE_PATH}/hgl/graph)

SET(CM_SG_HEADER    ${CM_SG_INCLUDE_PATH}/AABB.h
                    ${CM_SG_INCLUDE_PATH}/Bitmap.h
                    ${CM_SG_INCLUDE_PATH}/Coordinate.h
                    ${CM_SG_INCLUDE_PATH}/Ray.h
                    ${CM_SG_INCLUDE_PATH}/Plane.h
                    ${CM_SG_INCLUDE_PATH}/Frustum.h
                    ${CM_SG_INCLUDE_PATH}/VertexAttrib.h)

SET(CM_SG_VULKAN_HEADER     ${CM_SG_INCLUDE_PATH}/VKFormat.h
                            ${CM_SG_INCLUDE_PATH}/VKImageCreateInfo.h
                            ${CM_SG_INCLUDE_PATH}/VKInlinePipeline.h
                            ${CM_SG_INCLUDE_PATH}/VKNamespace.h
                            ${CM_SG_INCLUDE_PATH}/VKPipelineData.h
                            ${CM_SG_INCLUDE_PATH}/VKPrimivate.h
                            ${CM_SG_INCLUDE_PATH}/VKRenderbufferInfo.h
                            ${CM_SG_INCLUDE_PATH}/VKStruct.h
                            ${CM_SG_INCLUDE_PATH}/VKVertexAttributeBinding.h)

SET(CM_SG_SOURCE    AABB.cpp
                    Coordinate.cpp
                    Ray.cpp
                    Plane.cpp
                    Frustum.cpp
                    VertexAttrib.cpp)

SET(CM_CAMERA_SOURCE    ${CM_SG_INCLUDE_PATH}/Camera.h
                        ${CM_SG_INCLUDE_PATH}/CameraInfo.h
                        ${CM_SG_INCLUDE_PATH}/CameraControl.h
                        ${CM_SG_INCLUDE_PATH}/LookAtCameraControl.h
                        ${CM_SG_INCLUDE_PATH}/FirstPersonCameraControl.h
                        Camera.cpp)

SOURCE_GROUP("SceneGraph\\Camera" FILES ${CM_CAMERA_SOURCE})

SET(CM_SG_VULKAN_SOURCE vulkan/VKFormat.cpp
                        vulkan/VKVertexAttributeBinding.cpp
                        vulkan/VKPipelineData.cpp
                        vulkan/VKPipelineDataManage.cpp
                        vulkan/VKPipelineDataSaveLoad.cpp)

source_group("SceneGraph" FILES ${CM_SG_HEADER} ${CM_SG_SOURCE})
source_group("SceneGraph\\Vulkan" FILES ${CM_SG_VULKAN_HEADER} ${CM_SG_VULKAN_SOURCE})

add_cm_library(CMSceneGraph "CM"    ${CM_SG_HEADER}
                                    ${CM_SG_SOURCE}
                                    ${CM_CAMERA_SOURCE}
                                    ${CM_SG_VULKAN_HEADER}
                                    ${CM_SG_VULKAN_SOURCE})
