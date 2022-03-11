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

            void ZoomFOV(int adjust)
            {
                constexpr float MinFOV=10;
                constexpr float MaxFOV=180;

                camera->Yfov+=float(adjust)/10.0f;

                if(adjust<0&&camera->Yfov<MinFOV)camera->Yfov=MinFOV;else
                if(adjust>0&&camera->Yfov>MaxFOV)camera->Yfov=MaxFOV;
            }

            virtual void Refresh()=0;
        };//class CameraControl
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_CAMERA_CONTROL_INCLUDE
