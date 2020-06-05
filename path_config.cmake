macro(CMSceneGraphSetup source_path)

    message("CMSCENEGRAPH_ROOT_PATH: " ${source_path})

    set(CMSCENEGRAPH_ROOT_INCLUDE_PATH    ${source_path}/inc)
    set(CMSCENEGRAPH_ROOT_SOURCE_PATH     ${source_path}/src)

    include_directories(${CMSCENEGRAPH_ROOT_INCLUDE_PATH})
endmacro()
