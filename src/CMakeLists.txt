SET(CM_SG_INCLUDE_PATH  ${CMSCENEGRAPH_ROOT_INCLUDE_PATH}/hgl/graph)

SET(CM_SG_GEO_FILES     ${CMSCENEGRAPH_ROOT_INCLUDE_PATH}/hgl/geo/GeoLocation.h
                        Geo/GeoLocation.cpp)

SOURCE_GROUP("Geo" FILES ${CM_SG_GEO_FILES})

SET(CM_BOUNDING_FILES   ${CM_SG_INCLUDE_PATH}/AABB.h
                        ${CM_SG_INCLUDE_PATH}/OBB.h
                        ${CM_SG_INCLUDE_PATH}/BoundingSphere.h
                        ${CM_SG_INCLUDE_PATH}/BoundingVolumes.h
                        Bounding/AABB.cpp
                        Bounding/OBB.cpp
                        Bounding/OBB_SetFromPoints_AVX2.cpp
                        Bounding/BoundingSphere.cpp
                        Bounding/BoundingVolumes.cpp)

SOURCE_GROUP("Bounding Volumes" FILES ${CM_BOUNDING_FILES})

SET(CM_SG_HEADER    ${CM_SG_INCLUDE_PATH}/Sphere.h
                    ${CM_SG_INCLUDE_PATH}/TRS.h
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
                            ${CM_SG_INCLUDE_PATH}/VKNamespace.h
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

SET(CM_SG_SOURCE    TRS.cpp
                    Coordinate.cpp
                    Ray.cpp
                    Plane.cpp
                    Frustum.cpp
                    VertexAttrib.cpp
                    Sky.cpp)

SET(CM_SG_VULKAN_SOURCE vulkan/VKFormat.cpp
                        vulkan/VKString.cpp
                        vulkan/VKPrimitiveType.cpp
                        vulkan/VKShaderStage.cpp
                        vulkan/VKShaderDescriptorSet.cpp
                        vulkan/VKVertexInput.cpp
                        vulkan/VKVertexInputLayout.cpp
                        vulkan/VKVertexInputLayoutHash.cpp)

source_group("SceneGraph" FILES ${CM_SG_HEADER} ${CM_SG_SOURCE})
source_group("SceneGraph\\Vulkan" FILES ${CM_SG_VULKAN_HEADER} ${CM_SG_VULKAN_SOURCE})

add_cm_library(CMSceneGraph "CM"    ${CM_SG_HEADER}
                                    ${CM_SG_SOURCE}
                                    ${CM_SG_GEO_FILES}
                                    ${CM_CAMERA_SOURCE}
                                    ${CM_BOUNDING_FILES}
                                    ${CM_SG_VULKAN_HEADER}
                                    ${CM_SG_VULKAN_SOURCE})

# Optional Vulkan support: find Vulkan and link if available. Define HGL_VULKAN_AVAILABLE accordingly.
find_package(Vulkan QUIET)
if(Vulkan_FOUND)
    message(STATUS "Vulkan found: enabling Vulkan support for CMSceneGraph")
    target_link_libraries(CMSceneGraph PRIVATE Vulkan::Vulkan)
    target_compile_definitions(CMSceneGraph PRIVATE HGL_VULKAN_AVAILABLE=1)
else()
    message(STATUS "Vulkan not found: building CMSceneGraph without Vulkan linkage")
    target_compile_definitions(CMSceneGraph PRIVATE HGL_VULKAN_AVAILABLE=0)
endif()
