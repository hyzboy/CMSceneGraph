SET(CM_SG_INCLUDE_PATH  ${CMSCENEGRAPH_ROOT_INCLUDE_PATH}/hgl/graph)

SET(CM_SG_GEO_FILES     ${CMSCENEGRAPH_ROOT_INCLUDE_PATH}/hgl/geo/GeoLocation.h
                        Geo/GeoLocation.cpp)

SOURCE_GROUP("Geo" FILES ${CM_SG_GEO_FILES})

SET(CM_SG_HEADER    ${CM_SG_INCLUDE_PATH}/AABB.h
                    ${CM_SG_INCLUDE_PATH}/OBB.h
                    ${CM_SG_INCLUDE_PATH}/Sphere.h
                    ${CM_SG_INCLUDE_PATH}/BitmapData.h
                    ${CM_SG_INCLUDE_PATH}/ImageRegion.h
                    ${CM_SG_INCLUDE_PATH}/NormalData.h
                    ${CM_SG_INCLUDE_PATH}/Coordinate.h
                    ${CM_SG_INCLUDE_PATH}/Ray.h
                    ${CM_SG_INCLUDE_PATH}/LineSegment.h
                    ${CM_SG_INCLUDE_PATH}/Triangle.h
                    ${CM_SG_INCLUDE_PATH}/Capsule.h
                    ${CM_SG_INCLUDE_PATH}/Plane.h
                    ${CM_SG_INCLUDE_PATH}/Frustum.h
                    ${CM_SG_INCLUDE_PATH}/TransformFaceToCamera.h
                    ${CM_SG_INCLUDE_PATH}/VertexAttrib.h
                    ${CM_SG_INCLUDE_PATH}/Sky.h)

SET(CM_SG_VULKAN_HEADER     ${CM_SG_INCLUDE_PATH}/VKFormat.h
                            ${CM_SG_INCLUDE_PATH}/VKString.h
                            ${CM_SG_INCLUDE_PATH}/VKInterpolation.h
                            ${CM_SG_INCLUDE_PATH}/VKDescriptorSetType.h
                            ${CM_SG_INCLUDE_PATH}/VKShaderDescriptor.h
                            ${CM_SG_INCLUDE_PATH}/VKShaderDescriptorSet.h
                            ${CM_SG_INCLUDE_PATH}/VKVertexInputAttribute.h
                            ${CM_SG_INCLUDE_PATH}/VKImageCreateInfo.h
                            ${CM_SG_INCLUDE_PATH}/VKInlinePipeline.h
                            ${CM_SG_INCLUDE_PATH}/VKNamespace.h
                            ${CM_SG_INCLUDE_PATH}/VKPipelineData.h
                            ${CM_SG_INCLUDE_PATH}/VKPipelineHash.h
                            ${CM_SG_INCLUDE_PATH}/VKPrimitiveType.h
                            ${CM_SG_INCLUDE_PATH}/VKRenderbufferInfo.h
                            ${CM_SG_INCLUDE_PATH}/VKStruct.h
                            ${CM_SG_INCLUDE_PATH}/VKVertexInputConfig.h
                            ${CM_SG_INCLUDE_PATH}/VKVertexInput.h
                            ${CM_SG_INCLUDE_PATH}/VKVertexInputFormat.h
                            ${CM_SG_INCLUDE_PATH}/VKVertexInputLayout.h
                            ${CM_SG_INCLUDE_PATH}/VKVertexInputLayoutHash.h
                            ${CM_SG_INCLUDE_PATH}/VKSamplerType.h
                            ${CM_SG_INCLUDE_PATH}/VKImageType.h
)

SET(CM_SG_SOURCE    AABB.cpp
                    OBB.cpp
                    Coordinate.cpp
                    Ray.cpp
                    Plane.cpp
                    Frustum.cpp
                    VertexAttrib.cpp
                    Sky.cpp
                    ViewportInfo.cpp)

SET(CM_SG_VULKAN_SOURCE vulkan/VKFormat.cpp
                        vulkan/VKString.cpp
                        vulkan/VKPrimitiveType.cpp
                        vulkan/VKShaderStage.cpp
                        vulkan/VKShaderDescriptorSet.cpp
                        vulkan/VKVertexInput.cpp
                        vulkan/VKVertexInputLayout.cpp
                        vulkan/VKVertexInputLayoutHash.cpp
                        vulkan/VKPipelineCompare.cpp
                        vulkan/VKPipelineHash.cpp
                        vulkan/VKPipelineData.cpp
                        vulkan/VKPipelineDataManage.cpp
                        vulkan/VKPipelineDataSaveLoad.cpp)

source_group("SceneGraph" FILES ${CM_SG_HEADER} ${CM_SG_SOURCE})
source_group("SceneGraph\\Vulkan" FILES ${CM_SG_VULKAN_HEADER} ${CM_SG_VULKAN_SOURCE})


add_cm_library(CMSceneGraph "CM"    ${CM_SG_HEADER}
                                    ${CM_SG_SOURCE}
                                    ${CM_SG_GEO_FILES}
                                    ${CM_CAMERA_SOURCE}
                                    ${CM_SG_VULKAN_HEADER}
                                    ${CM_SG_VULKAN_SOURCE})
