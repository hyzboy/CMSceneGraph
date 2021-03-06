﻿#ifndef HGL_GRAPH_COLOR_SPACE_INCLUDE
#define HGL_GRAPH_COLOR_SPACE_INCLUDE

#include<math.h>

namespace hgl
{
    namespace graph
    {
        enum class ColorSpace
        {
            Linear=0,
            sRGB,
            YCbCr,

            BEGIN_RANGE =Linear,
            END_RANGE   =YCbCr,
            RANGE_SIZE  =(END_RANGE-BEGIN_RANGE)+1
        };//enum class ColorSpace

        constexpr double SRGB_GAMMA         =1.0f/2.2f;
        constexpr double SRGB_INVERSE_GAMMA =2.2f;
        constexpr double SRGB_ALPHA         =0.055f;

        template<typename T>
        inline const T sRGB2Linear(const T &in)
        {
            if(in<=0.4045)
                return (double)in/12.92;
            else
                return pow((double(in)+SRGB_ALPHA)/(1.0f+SRGB_ALPHA),2.4f);
        }

        template<typename T>
        inline const T Linear2sRGB(const T &in)
        {
            if(in<=0.0031308f)
                return double(in)*12.92f;
            else
                return (1.0f+SRGB_ALPHA)*pow(double(in),1.0f/2.4f)-SRGB_ALPHA;
        }

        template<typename T>
        inline const T sRGB2LinearApprox(const T &in)
        {
            return (T)pow(double(in),SRGB_INVERSE_GAMMA);
        }

        template<typename T>
        inline const T Linear2sRGBApprox(const T &in)
        {
            return (T)pow((double)in,SRGB_GAMMA);
        }

        template<typename T>
        inline void sRGB2LinearFast(T &x,T &y,T &z,const T &r,const T &g,const T &b)
        {
            x=0.4124f*r+0.3576f*g+0.1805f*b;
            y=0.2126f*r+0.7152f*g+0.0722f*b;
            z=0.0193f*r+0.1192f*g+0.9505f*b;
        }

        template<typename T>
        inline void Linear2sRGBFast(T &r,T &g,T &b,const T &x,const T &y,const T &z)
        {
            r= 3.2406f*x-1.5373f*y-0.4986f*z;
            g=-0.9689f*x+1.8758f*y+0.0416f*z;
            b= 0.0557f*x-0.2040f*y+1.0570f*z;
        }

        template<typename T>
        inline T Clamp(const T &value,const T &min_value,const T &max_value)
        {
            if(value<min_value)return min_value;
            if(value>max_value)return max_value;

            return value;
        }

        template<typename T>
        inline T Clamp(const T &value)
        {
            return Clamp<T>(value,T(0),T(1));
        }

        template<> inline uint8 Clamp<uint8>(const uint8 &value)
        {
            return Clamp<uint8>(value,0,255);
        }
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_COLOR_SPACE_INCLUDE
