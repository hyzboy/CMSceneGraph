add_executable(PipelineCompiler PipelineCompiler.cpp SavePipeline2Toml.cpp LoadPipeline4Toml.cpp)

target_link_libraries(PipelineCompiler ${ULRE})
