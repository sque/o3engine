#ifndef O3ENGINE_DEBUG_STREAM_HPP_INCLUDED
#define O3ENGINE_DEBUG_STREAM_HPP_INCLUDED

#include "./base_prereqs.hpp"
#include "./vector2.hpp"
#include "./vector3.hpp"
#include "./vector4.hpp"
#include "./angle.hpp"
#include "./quaternion.hpp"
#include "./image.hpp"

namespace o3engine
{
    //! @name Extract information about objects in a human readable format
    //! @{
    inline std::string toString(const Vector2 & v2)
    {   char cStr[255];
        sprintf(cStr, "V2(x:%f y:%f)", v2.x, v2.y);
        return std::string(cStr);
    }

    inline std::string toString(const Vector3 & v3)
    {   char cStr[255];
        sprintf(cStr, "V3(x:%f y:%f z:%f)", v3.x, v3.y, v3.z);
        return std::string(cStr);
    }

    inline std::string toString(const Vector4 & v4)
    {   char cStr[255];
        sprintf(cStr, "V4(x:%f y:%f z:%f w:%f)", v4.x, v4.y, v4.z, v4.w);
        return std::string(cStr);
    }

    inline std::string toString(const Quaternion & q)
    {   char cStr[255];
        sprintf(cStr, "Qu(x:%f y:%f z:%f w:%f)", q.x, q.y, q.z, q.w);
        return std::string(cStr);
    }

    inline std::string toString(const Angle & a)
    {   char cStr[255];
        sprintf(cStr, "A(Rad:%f Deg:%f)", a.getRadian(), a.getDegrees());
        return std::string(cStr);
    }

    inline std::string toString(const Color & c)
    {   char cStr[255];
        sprintf(cStr, "Color(R:%f G:%f B:%f A:%f)", c.red, c.blue, c.green, c.alpha);
        return std::string(cStr);
    }

    inline std::string toString(const Image & i)
    {   char cStr[255];
        sprintf(cStr, "Image(W:%lu H:%lu)", i.getWidth(), i.getHeight());
        return std::string(cStr);
    }

    inline std::string toString(const Triangle3 & tri)
    {   char cStr[255];
        sprintf(cStr, "Tri3((%f, %f, %f) - (%f, %f, %f) - (%f, %f, %f) )",
            tri.point_a.x, tri.point_a.y, tri.point_a.z,
            tri.point_b.x, tri.point_b.y, tri.point_b.z,
            tri.point_c.x, tri.point_c.y, tri.point_c.z);
        return std::string(cStr);
    }
    //! @}

}
#endif
