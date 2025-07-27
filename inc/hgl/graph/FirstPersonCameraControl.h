﻿#pragma once

/**
 * thank for LearnOpenGL
 * link: https://learnopengl.com/Getting-started/Camera
 */

#include<hgl/graph/CameraControl.h>
#include<hgl/io/event/KeyboardEvent.h>
#include<hgl/io/event/MouseEvent.h>
#include<hgl/Time.h>

namespace hgl::graph
{
    class FirstPersonCameraControl:public CameraControl
    {
        float pitch;        ///<抬头角度(绕X轴旋转角度(X轴左右))
        float yaw;          ///<左右角度(绕Z轴旋转角度(Z轴向上))
        float roll;         ///<歪头角度(绕Y轴旋转角度(Y轴向前))

        Vector3f front;
        Vector3f right;
        Vector3f up;

        Vector3f distance;          ///<相机到观察点的距离

        Vector3f target;            ///<目标点坐标

        Vector2f ReverseDirection;  ///<是否反转方向

    public:

        static CameraControlIDName StaticControlName()
        {
            static CameraControlIDName FPCC("FirstPersonCameraControl");

            return FPCC;
        }

        const CameraControlIDName GetControlName() const override 
        {
            return StaticControlName();
        }

    public:

        FirstPersonCameraControl(ViewportInfo *v,Camera *c,UBOCameraInfo *ci):CameraControl(v,c,ci)
        {
            target=Vector3f(0.0f);
            up=Vector3f(0,0,1);
            distance=Vector3f(0,0,0);

            pitch=0;
            yaw  =deg2rad(-90.0f);
            roll =0;

            ReverseDirection.x=-1;
            ReverseDirection.y=1;

            UpdateCameraVector();
        }
        virtual ~FirstPersonCameraControl()=default;
            
        void SetReserveDirection(bool x,bool y)
        {
            ReverseDirection.x=x?-1:1;
            ReverseDirection.y=y?-1:1;
        }

        void SetTarget(const Vector3f &t) override
        {
            front   =normalize(t-camera->pos);
            right   =normalize(cross(front,camera->world_up));
            up      =normalize(cross(right,front)); 

            camera->view_line=normalize(camera->pos-t);

            pitch   =asin(front.z);
            yaw     =atan2(front.x,front.y);

            UpdateCameraVector();

            distance=(t-camera->pos)/front;
        }

        void Refresh() override
        {
            target=camera->pos+front*distance;

            camera_info->view       =LookAtMatrix(camera->pos,target,camera->world_up);

            RefreshCameraInfo(camera_info,vi,camera);

            ubo_camera_info->Update();
        }

    public: //移动
            
        void UpdateCameraVector()
        {
            front   =PolarToVector(yaw,pitch);

            right   =normalize(cross(front,camera->world_up));
            up      =normalize(cross(right,front));
        }

        void Forward(float move_step)
        {
            camera->pos+=front*move_step;
        }

        void Backward(float move_step)
        {
            camera->pos-=front*move_step;
        }

        void Left(float move_step)
        {
            camera->pos-=right*move_step;
        }

        void Right(float move_step)
        {
            camera->pos+=right*move_step;
        }

    public: //旋转

        void Rotate(const Vector2f &axis)
        {
            constexpr double top_limit      =deg2rad( 89.0f);
            constexpr double bottom_limit   =deg2rad(-89.0f);

            yaw     -=axis.x*ReverseDirection.x/180.0f;
            pitch   -=axis.y*ReverseDirection.y/180.0f;

            if(pitch>top_limit      )pitch=top_limit;
            if(pitch<bottom_limit   )pitch=bottom_limit;
            
            UpdateCameraVector();
        }

        void Move(const Vector3f &delta)
        {
            camera->pos+=delta;
        }
    };//class FirstPersonCameraControl:public CameraControl

    class CameraKeyboardControl:public io::KeyboardStateEvent
    {
        FirstPersonCameraControl *camera;
        float move_speed;

    public:

        CameraKeyboardControl(FirstPersonCameraControl *wc)
        {
            camera=wc;
            move_speed=1.0f;
        }

        bool OnPressed(const io::KeyboardButton &kb)override
        {
            if(!KeyboardStateEvent::OnPressed(kb))
                return(false);

            if(kb==io::KeyboardButton::Minus    )move_speed*=0.9f;else
            if(kb==io::KeyboardButton::Equals   )move_speed*=1.1f;

            return(true);
        }

        bool Update() override
        {
            if(HasPressed(io::KeyboardButton::W     ))camera->Forward   (move_speed);else
            if(HasPressed(io::KeyboardButton::S     ))camera->Backward  (move_speed);else
            if(HasPressed(io::KeyboardButton::A     ))camera->Left      (move_speed);else
            if(HasPressed(io::KeyboardButton::D     ))camera->Right     (move_speed);else
            //if(HasPressed(io::KeyboardButton::R     ))camera->Up        (move_speed);else
            //if(HasPressed(io::KeyboardButton::F     ))camera->Down      (move_speed);else

            //if(HasPressed(io::KeyboardButton::Left  ))camera->HoriRotate( move_speed);else
            //if(HasPressed(io::KeyboardButton::Right ))camera->HoriRotate(-move_speed);else
            //if(HasPressed(io::KeyboardButton::Up    ))camera->VertRotate( move_speed);else
            //if(HasPressed(io::KeyboardButton::Down  ))camera->VertRotate(-move_speed);else
                return(true);

            return(true);
        }
    };//class CameraKeyboardControl:public io::KeyboardStateEvent

    class CameraMouseControl:public io::MouseEvent
    {
        FirstPersonCameraControl *camera;
        double cur_time;
        double last_time;

        Vector2f mouse_pos;
        Vector2f mouse_last_pos;

    protected:

        bool OnPressed(const Vector2i &mouse_coord,io::MouseButton) override
        {
            mouse_last_pos=mouse_coord;

            last_time=cur_time;

            return(true);
        }
    
        bool OnWheel(const Vector2i &mouse_coord) override
        {
            if(mouse_coord.y==0)return(false);

            camera->Forward(float(mouse_coord.y)/100.0f);

            return(true);
        }

        bool OnMove(const Vector2i &mouse_coord) override
        {
            mouse_pos=mouse_coord;

            bool left =HasPressed(io::MouseButton::Left);
            bool right=HasPressed(io::MouseButton::Right);
        
            Vector2f pos=mouse_coord;
            Vector2f gap=pos-mouse_last_pos;
        
            if(left)
            {
                gap/=-5.0f;

                camera->Rotate(gap);
            }
            else
            if(right)
            {
                gap/=10.0f;

                camera->Move(Vector3f(gap.x,0,gap.y));
            }

            last_time=cur_time;
            mouse_last_pos=pos;

            return(false);
        }

    public:

        CameraMouseControl(FirstPersonCameraControl *wc)
        {
            camera=wc;
            cur_time=0;
            last_time=0;
        }

        const Vector2f &GetMouseCoord()const{return mouse_pos;}

        bool Update() override
        {
            cur_time=GetPreciseTime();

            return(true);
        }
    };//class CameraMouseControl:public io::MouseEvent
}//namespace hgl::graph
