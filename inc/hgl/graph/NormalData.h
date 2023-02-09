#ifndef HGL_NORMAL_DATA_INCLUDE
#define HGL_NORMAL_DATA_INCLUDE

#include<hgl/math/Vector.h>

namespace hgl
{
    // Lambert Azimuthal Equal-Area projection
    // http://en.wikipedia.org/wiki/Lambert_azimuthal_equal-area_projection

    /**
    * 将float3型法线数据压缩为float2型
    */
    inline Vector2f Normal3to2(const Vector3f &input)
    {
        float f=sqrt(8.0f*input.z+8.0f);

        return Vector2f(input.x/f+0.5f,
                        input.y/f+0.5f);
    }

    /**
    * 解压float2型法线数据
    */
    inline Vector3f Normal2to3(const Vector2f &input)
    {
        Vector2f fenc(input*4.0f-2.0f);

        float f=dot(fenc,fenc);
        float g=sqrt(1.0f-f/4.0f);

        return Vector3f(fenc.x*g,
                        fenc.y*g,
                        1.0f-f/2.0f);
    }

    inline Vector2u8 Normal3to2(const Vector3u8 &input)
    {
        Vector3f fenc(  input.x/255.0f*2.0f-1.0f,
                        input.y/255.0f*2.0f-1.0f,
                        input.z/255.0f*2.0f-1.0f);

        float f=dot(fenc,fenc);
        float g=sqrt(1.0f-f/4.0f);

        return Vector2u8(   uint8((fenc.x*g+1.0f)*127.5f),
                            uint8((fenc.y*g+1.0f)*127.5f));
    }

    inline Vector3u8 Normal2to3(const Vector2u8 &input)
    {
        Vector2f fenc(  (input.x/127.5f-1.0f)*2.0f,
                        (input.y/127.5f-1.0f)*2.0f);

        float f=dot(fenc,fenc);
        float g=sqrt(1.0f-f/4.0f);

        return Vector3u8(   uint8((fenc.x*g+1.0f)*127.5f),
                            uint8((fenc.y*g+1.0f)*127.5f),
                            uint8((1.0f-f/2.0f)*127.5f));
    }

    inline Vector2u16 Normal3to2(const Vector3u16 &input)
    {
        Vector3f fenc(  input.x/65535.0f*2.0f-1.0f,
                        input.y/65535.0f*2.0f-1.0f,
                        input.z/65535.0f*2.0f-1.0f);

        float f=dot(fenc,fenc);
        float g=sqrt(1.0f-f/4.0f);

        return Vector2u16(  uint16((fenc.x*g+1.0f)*32767.5f),
                            uint16((fenc.y*g+1.0f)*32767.5f));
    }

    inline Vector3u16 Normal2to3(const Vector2u16 &input)
    {
        Vector2f fenc(  (input.x/32767.5f-1.0f)*2.0f,
                        (input.y/32767.5f-1.0f)*2.0f);

        float f=dot(fenc,fenc);
        float g=sqrt(1.0f-f/4.0f);

        return Vector3u16(  uint16((fenc.x*g+1.0f)*32767.5f),
                            uint16((fenc.y*g+1.0f)*32767.5f),
                            uint16((1.0f-f/2.0f)*32767.5f));
    }

    /**
    * 将float3型法线数据压缩为32位无符号整数(或两个16位无符号整数)
    */
    inline uint32 NormalToU32(const Vector3f &input)
    {
        float f=sqrt(8.0f*input.z+8.0f);

        float x=input.x/f+0.5f;
        float y=input.y/f+0.5f;

        return (uint32(x*65535.0f)<<16)
             | (uint32(y*65535.0f));
    }

    /**
    * 解压uint32型法线数据
    */
    inline Vector3f U32ToNormal(const uint32 &input)
    {
        float x=float(input>>16)/65535.0f;
        float y=float(input&0xFFFF)/65535.0f;

        Vector2f fenc((x-0.5f)*4.0f,
                      (y-0.5f)*4.0f);

        float f=dot(fenc,fenc);
        float g=sqrt(1.0f-f/4.0f);

        return Vector3f(fenc.x*g,
                        fenc.y*g,
                        1.0f-f/2.0f);
    }

    inline uint16 NormalToU16(const Vector3f &input)
    {
        float f=sqrt(8.0f*input.z+8.0f);

        float x=input.x/f+0.5f;
        float y=input.y/f+0.5f;

        return (uint16(x*255.0f)<<8)
             | (uint16(y*255.0f));
    }

    inline Vector3f U16ToNormal(const uint16 &input)
    {
        float x=float(input>>8)/255.0f;
        float y=float(input&0xFF)/255.0f;

        Vector2f fenc(  (x-0.5f)*4.0f,
                        (y-0.5f)*4.0f);

        float f=dot(fenc,fenc);
        float g=sqrt(1.0f-f/4.0f);

        return Vector3f(fenc.x*g,
                        fenc.y*g,
                        1.0f-f/2.0f);
    }
}//namespace hgl
#endif//HGL_NORMAL_DATA_INCLUDE

