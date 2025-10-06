#include <hgl/graph/TRS.h>

namespace hgl::graph
{
    glm::mat4 TRS::toMat4() const
    {
        glm::mat4 m=glm::mat4(1.0f);

        m =glm::translate(m,translation);
        m*=glm::mat4_cast(rotation);
        m =glm::scale(m,scale);

        return m;
    }
}//namespace hgl::graph
