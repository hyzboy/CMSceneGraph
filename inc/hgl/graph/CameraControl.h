#ifndef HGL_GRAPH_CAMERA_CONTROL_INCLUDE
#define HGL_GRAPH_CAMERA_CONTROL_INCLUDE

#include<hgl/graph/Camera.h>
namespace hgl
{
    namespace graph
    {
        class CameraControl
        {
        protected:

            Camera *camera;

        public:

            CameraControl(Camera *c)
            {
                camera=c;
            }

            void SetCamera(Camera *c)
            {
                camera=c;
            }

            virtual void Refresh()=0;
        };//class CameraControl
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_CAMERA_CONTROL_INCLUDE
