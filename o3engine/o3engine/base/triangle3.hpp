#ifndef O3ENGINE_TRIANGLE3_HPP_INCLUDED
#define O3ENGINE_TRIANGLE3_HPP_INCLUDED

#include "./base_prereqs.hpp"
#include "./vector3.hpp"

namespace o3engine
{
    //! [R5] Class representing a triangle in 3d space
    /**
	  This class is usefull for representing any kind of triangle in 3D space.
	  It is light and generally fast and containes a number of feature
	  very usefull when working with triangles.

     @par Class Characteristics
         Triangle3 is @ref copyable_page, @ref noninherit_page and follows the @ref sfn_page
     @ingroup base_group
	 */
    class Triangle3
    {
    public:
        //! Point A of triangle
        Vector3 point_a;

        //! Point B of triangle
        Vector3 point_b;

        //! Point C of triangle
        Vector3 point_c;

        //! Default constructor
        /**
            It does @b NOT initialize member values
         */
        inline Triangle3(){}

        //! Construct and initialize from Vector3 points
        inline Triangle3(const Vector3 & p_a, const Vector3 & p_b, const Vector3 & p_c)
            :point_a(p_a),
            point_b(p_b),
            point_c(p_c)
        {}

        //! Construct and initialize from an array of 9 Real numbers
        inline Triangle3(const Real coords[])
            :point_a(coords[0], coords[1], coords[2]),
            point_b(coords[3], coords[4], coords[5]),
            point_c(coords[6], coords[7], coords[8])
        {}

        //! Construct and initialize from an array of 3 Vector3 objects
        inline Triangle3(const Vector3 points[])
            :point_a(points[0]),
            point_b(points[1]),
            point_c(points[2])
        {}

        //! Set values from 3 Vector3 objects
        inline void set(const Vector3 & a, const Vector3 & b, const Vector3 & c)
        {   point_a = a; point_b = b; point_c = c;  }

        //! Set values from a C array of 3 Vector3 objects
        inline void set(const Vector3 points[])
        {   point_a = points[0]; point_b = points[1]; point_c = points[2]; }

        //! @name Math operations
		//! @{

		//! Move triangle to a relative position
		inline Triangle3 & translate(const Vector3 & trans)
		{   point_a += trans; point_b += trans; point_c += trans; return *this;   }

        //! Scale triangle based on a factor
		inline Triangle3 & scale(Real factor)
		{   point_a *= factor; point_b *= factor; point_c *= factor; return *this;    }

		//! Calculate area that the triangle covers
		inline Real area() const
		{   return (point_b - point_a).crossProduct(point_c - point_a).length() * 0.5f; }

        //! Calculate the normal of the triangle (@b UNORMILIZED)
        inline Vector3 normal() const
        {   return (point_b - point_a).crossProduct(point_c - point_a); }

        //! Calculate a new interpolated triangle
        inline Triangle3 interpolated(const Triangle3 & dst, Real factor) const
        {   return Triangle3(point_a.interpolated(dst.point_a, factor),
                        point_b.interpolated(dst.point_b, factor),
                        point_c.interpolated(dst.point_c, factor));
        }

        //! Self-scale operator
        inline Triangle3 & operator*=(Real factor)
        {   point_a *= factor; point_b *= factor; point_c *= factor; return *this;    }

        //! Scale operator
        inline Triangle3 operator*(Real factor) const
        {   Triangle3 tmp_t3(point_a * factor, point_b * factor, point_c * factor);
            return tmp_t3;
        }

        //! Move triangle
        inline Triangle3 & operator+=(const Vector3 & trans)
        {   point_a += trans; point_b += trans; point_c += trans; return *this;   }

        //! Translate a copy of this triangle
        inline Triangle3 operator+(const Vector3 & trans) const
        {   Triangle3 tmp_t3(point_a + trans, point_b + trans, point_c + trans);
            return tmp_t3;
        }
        //! @}

		//! @name Comparison operators
		//! @{

		inline bool operator==(const Triangle3 & r) const
		{   return (point_a == r.point_a && point_b == r.point_b && point_c == r.point_c);  }

		inline bool operator!=(const Triangle3 & r) const
		{   return !operator==(r);  }
		//! @}
    };
}
#endif
