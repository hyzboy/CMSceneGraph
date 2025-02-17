#include<hgl/type/String.h>
#include<hgl/graph/VKPipelineData.h>
#include<hgl/graph/VKInlinePipeline.h>
#include<hgl/filesystem/FileSystem.h>
#include<iostream>

VK_NAMESPACE::PipelineData *LoadPipeline(const hgl::OSString &filename);

VK_NAMESPACE_BEGIN
    bool SaveToFile(const OSString &filename,PipelineData *pd);

    std::string SavePipelineToToml(const PipelineData *data);

    void SaveToToml(const OSString &filename,const PipelineData &pd)
    {
        std::string str=SavePipelineToToml(&pd);

        if(hgl::filesystem::SaveMemoryToFile(filename,str.c_str(),str.length())>0)
        {
            os_out<<OS_TEXT("Save pipeline file: ")<<filename.c_str()<<OS_TEXT(" success!")<<std::endl;
        }
        else
        {
            os_err<<OS_TEXT("Save pipeline file: ")<<filename.c_str()<<OS_TEXT(" failed!")<<std::endl;
        }
    }

    void SaveInlinePipeline2Toml(const OSString &pathname)
    {
        if(!filesystem::IsDirectory(pathname))
        {
            os_err<<OS_TEXT("SaveInlinePipeline2Toml(")<<pathname.c_str()<<OS_TEXT(") failed, not a directory.")<<std::endl;
            return;
        }

        SaveToToml(filesystem::MergeFilename(pathname,OS_TEXT("Solid3D.pipeline.toml")),GetPipelineData(InlinePipeline::Solid3D));
        SaveToToml(filesystem::MergeFilename(pathname,OS_TEXT("Alpha3D.pipeline.toml")),GetPipelineData(InlinePipeline::Alpha3D));
        SaveToToml(filesystem::MergeFilename(pathname,OS_TEXT("Solid2D.pipeline.toml")),GetPipelineData(InlinePipeline::Solid2D));
        SaveToToml(filesystem::MergeFilename(pathname,OS_TEXT("Alpha2D.pipeline.toml")),GetPipelineData(InlinePipeline::Alpha2D));
        SaveToToml(filesystem::MergeFilename(pathname,OS_TEXT("Sky.pipeline.toml"    )),GetPipelineData(InlinePipeline::Sky));
    }
VK_NAMESPACE_END

int os_main(int argc,os_char **argv)
{
    std::cout<<"PipelineCompiler v1.01 (offical web: "<<HGL_OFFICAL_WEB<<")"<<std::endl<<std::endl;

    if(argc<2)
    {
        std::cout<<"example: PipelineCompiler init"<<std::endl;
            
        std::cout<<"example: PipelineCompiler [pipeline filename]"<<std::endl<<std::endl;
        return 0;
    }

    if(hgl::stricmp(argv[1],OS_TEXT("init"))==0)
    {
        hgl::OSString cur_path;

        hgl::filesystem::GetCurrentPath(cur_path);

        os_out<<OS_TEXT("Create Inline pipeline file at")<<cur_path.c_str()<<std::endl;

        VK_NAMESPACE::SaveInlinePipeline2Toml(cur_path);

        return 0;
    }

    //const hgl::OSString xml_filename=argv[1];

    //os_out<<OS_TEXT("pipeline filename: ")<<xml_filename.c_str()<<std::endl;

    //VK_NAMESPACE::PipelineData *pd=LoadPipeline(xml_filename);
    //
    //if(pd)
    //{
    //    const hgl::OSString filename=hgl::filesystem::TrimFileExtName(xml_filename)+OS_TEXT("pipeline");

    //    os_out<<OS_TEXT("save pipeline file: ")<<filename.c_str()<<std::endl;

    //    if(VK_NAMESPACE::SaveToFile(filename,pd))
    //        std::cout<<"save ok!"<<std::endl;
    //    else
    //        std::cerr<<"save failed!"<<std::endl;
    //}
    //else
    //{
    //    std::cerr<<"load pipeline xml file failed!"<<std::endl;
    //}

    return 0;
}
