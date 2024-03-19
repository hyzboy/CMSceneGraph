cmake_minimum_required(VERSION 3.5)

project(CMSceneGraph)

include(path_config.cmake)
CMSceneGraphSetup(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${CMSCENEGRAPH_ROOT_SOURCE_PATH})
