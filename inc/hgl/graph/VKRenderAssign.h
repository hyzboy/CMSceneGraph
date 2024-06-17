#pragma once
#include<hgl/graph/VKFormat.h>
#include<hgl/graph/VertexAttrib.h>

VK_NAMESPACE_BEGIN

/*

        LocalToWorld整体存于一个UBO/SSBO，然后Local to World ID和Material Instance ID一起存于一个VertexInputStream。

        好处是当大量模型共用一个LocalToWorld时，节省VBO生成量。
        坏处是当大量模型都使用各自独立的LocalToWorld时，会生成超大的UBO，使之不得不分开成多次绘制。

    分支原因

        在次世代游戏中，模型的面数极高。这种情况下，有一种做法是将模型拆成多个128-256的小模型。
        一是符合MeshShader的条件，二是拆成小模型后，独立深度排序以及裁剪，可以得到更高的渲染效率。
        而一个大模型拆出的小模型当然是共用一个LocalToWorld矩阵。这种情况下就造成了最终渲染模型个数海量，
*/

constexpr const char        ASSIGN_VIS_NAME[]       ="Assign";
constexpr const VAType      ASSIGN_VAT_FMT          =VAT_UVEC2;
constexpr const VkFormat    ASSIGN_VAB_FMT          =VF_V2U16;
constexpr const uint        ASSIGN_VAB_STRIDE_BYTES =4;                 ///<L2W ID与材质实例ID VBO的每个节点的字节数

VK_NAMESPACE_END
