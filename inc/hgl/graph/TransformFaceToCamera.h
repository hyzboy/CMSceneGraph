#pragma once

#include<hgl/math/Transform.h>

namespace hgl
{
    namespace graph
    {
        /**
        * 永远转向摄像机的变换节点
        */
        class TransformFaceToCamera:public TransformBase
        {
            CameraInfo *camera_info=nullptr;

            Matrix4f last_view_matrix;

        protected:

            void MakeNewestData(Matrix4f &mat) override
            {
                if(camera_info)
                    mat=ToMatrix(CalculateFacingRotationQuat(WorldPosition,camera_info->view,WorldNormal));
                else
                    mat=Identity4f;
            }

        public:

            using TransformBase::TransformBase;

            constexpr const size_t GetTypeHash()const override { return hgl::GetTypeHash<TransformFaceToCamera>(); }

            TransformFaceToCamera(CameraInfo *ci):TransformBase()
            {
                camera_info=ci;

                last_view_matrix=Identity4f;
            }

            TransformBase *CreateSelfCopy()const override
            {
                return(new TransformFaceToCamera(camera_info));
            }

            void SetCameraInfo(CameraInfo *ci) { camera_info=ci; }

            bool Update() override
            {
                if(!camera_info)
                    return(false);

                if(IsNearlyEqual(last_view_matrix,camera_info->view))
                    return(false);

                last_view_matrix=camera_info->view;

                UpdateVersion();
                return(true);
            }
        };//class TransformFaceToCamera:public TransformBase
    }//namespace graph
}//namespace hgl
