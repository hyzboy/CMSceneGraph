add_executable(PipelineCompiler PipelineCompiler.cpp LoadXMLPipeline.cpp)

target_link_libraries(PipelineCompiler ${HGL_MATH_LIB})
