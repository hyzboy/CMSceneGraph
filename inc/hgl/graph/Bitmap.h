#ifndef HGL_GRAPH_BITMAP_INCLUDE
#define HGL_GRAPH_BITMAP_INCLUDE

namespace hgl
{
    namespace graph
    {
        class Bitmap
        {
        public:

            int GetWidth()const;
            int GetHeight()const;
            int GetPixelFormat()const;
        };//class Bitmap

        template<typename T>
        class BitmapImp :public Bitmap
        {
        protected:

            T* data;

        public:

            bool DrawPixel(int, int, const Color4f &);
        };

        template<typename T> class BitmapR :public BitmapImp<T> {};
        template<typename T> class BitmapRG :public BitmapImp<T> {};
        template<typename T> class BitmapRGB :public BitmapImp<T> {};
        template<typename T> class BitmapRGBA :public BitmapImp<T> {};

        using Bitmap3u8     = BitmapRGB<uint8>;
        using Bitmap3u16    = BitmapRGB<uint16>;
        using Bitmap3hf     = BitmapRGB<half_float>;
        using Bitmap3f      = BitmapRGB<float>;

        using Bitmap4u8     = BitmapRGBA<uint8>;
        using Bitmap4u16    = BitmapRGBA<uint16>;
        using Bitmap4hf     = BitmapRGBA<half_float>;
        using Bitmap4f      = BitmapRGBA<float>;
    }//namespace graph
}//namespace hgl
#endif//HGL_GRAPH_BITMAP_INCLUDE
