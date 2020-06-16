#ifndef HGL_GRAPH_COORDINATE_INCLUDE
#define HGL_GRAPH_COORDINATE_INCLUDE

#include<hgl/math/Math.h>

namespace hgl
{
    namespace graph
    {
        /*
         * OpenGL Coordinate System         Vulkan Coordinate System        My Coordinate System
         *
         *                                         /Z
         *     Y|    /Z                           /                             Z|    /Y
         *      |   /                            /                               |   /        
         *      |  /                            *------------                    |  /         
         *      | /                             |           X                    | /          
         *      |/                              |                                |/           
         *      *------------                   |                                *------------
         *                  X                   | Y                                          X
         */

        const Matrix4f gl2vk(const Matrix4f &ogl_matrix);               //将OpenGL坐标系矩阵变换到Vulkan坐标系
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_COORDINATE_INCLUDE
