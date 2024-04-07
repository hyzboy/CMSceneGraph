#pragma once

#include<hgl/math/Vector.h>

namespace hgl
{
    namespace graph
    {
        /**
        * 线段
        */
        class LineSegment
        {
        protected:

            Vector3f start;
            Vector3f end;

        public:

            const Vector3f &GetStart()const{return start;}
            const Vector3f &GetEnd()const{return end;}

            const Vector3f GetStartDirection()const{return normalized(end-start);}
            const Vector3f GetEndDirection()const{return normalized(start-end);}

            const float DistanceSquared()const{return length_squared(start,end);}
            const float Distance()const{return length(start,end);}
        };//class LineSegment
    }//namespace graph
}//namespace hgl
