#ifndef O3ENGINE_VECTOR2_HPP_INCLUDED
#define O3ENGINE_VECTOR2_HPP_INCLUDED

#include "./base_prereqs.hpp"

namespace o3engine
{
	//! [R5] Class representing a vector in 2D space
	/**
	  This class is usefull for representing any kind of vector in 2D space.
	  It is light and generally fast and containes a number of feature
	  very usefull when working with vectors. It also provides casting
	  operators to faciliate the interaction of Vector2 objects.

     @par Class Characteristics
         Vector2 is @ref copyable_page, @ref noninherit_page and follows the @ref sfn_page
     @ingroup base_group
	 */
	class Vector2
	{
	public:
	    //! The value of X componment
		Real x;
		//! The value of Y componment
		Real y;

		//! @name Common special vectors
		//! @{

		//! Constant value representing vector on xy(0,0)
		static const Vector2 ZERO;
		//! Constant value representing vector on xy(1,1)
		static const Vector2 IDENTITY;
		//! Constant value representing vector on xy(1,0)
		static const Vector2 UNIT_X;
		//! Constant value representing vector on xy(0,1)
		static const Vector2 UNIT_Y;
		//! Constant value representing vector on xy(-1,-1)
		static const Vector2 NEGATIVE_IDENTITY;
		//! Constant value representing vector on xy(-1,0)
		static const Vector2 NEGATIVE_UNIT_X;
		//! Constant value representing vector on xy(0,-1)
		static const Vector2 NEGATIVE_UNIT_Y;
		//! @}

        //! Default constructor
        /**
            It does @b NOT initialize member values
         */
        inline Vector2(){}

		//! Custom constructor
		inline Vector2(Real _x, Real _y):x(_x),y(_y){}

        inline Real squaredLength() const { return x * x + y * y; }
		inline Real length() const {	return math::sqrt(x * x + y * y);	}
		inline Vector2 operator - () const {   return Vector2(-x, -y); }
		inline Vector2 opposite() const {   return Vector2(-x,-y);  }
		inline Real distance(const Vector2 & r) const {   return (*this - r).length();    }
		inline Real squaredDistance(const Vector2 & r) const {   return (*this - r).squaredLength();    }
		inline Vector2 interpolated(const Vector2 & dst, Real factor) const
		{   Vector2 tmp_v2 = *this;
			tmp_v2.x += ((dst.x - x) * factor);
			tmp_v2.y += ((dst.y - y) * factor);
			return tmp_v2;
		}

		//! @name Math operations
		//! @{
		inline Vector2 & operator*=(Real factor) { x *= factor; y *= factor; return *this;  }
		inline Vector2 operator*(Real factor) const { return Vector2(x * factor, y * factor);  }
		inline Vector2 & operator*=(const Vector2 & r) { x *= r.x; y *= r.y; return *this; }
		inline Vector2 operator*(const Vector2 & r) const { return Vector2(x * r.x, y * r.y);  }
		inline Vector2 operator+(const Vector2 & r) const { return Vector2(x + r.x, y + r.y);  }
		inline Vector2 operator-(const Vector2 & r) const { return Vector2(x - r.x, y - r.y);  }
		inline Vector2 & operator-=(const Vector2 & r) { x -= r.x; y -= r.y; return *this;  }
		inline Vector2 & operator+=(const Vector2 & r) { x += r.x; y += r.y; return *this;  }
		inline Real normalize()
		{   Real fLength = math::sqrt( x * x + y * y);

			// Will also work for zero-sized vectors, but will change nothing
			if ( fLength > 1e-08 )
			{
				Real fInvLength = 1.0 / fLength;
				x *= fInvLength;
				y *= fInvLength;
			}
			return fLength;
		}

		//! Calculate the midpoint of this vector with another
		inline Vector2 midPoint(const Vector2 & r) const
		{   return Vector2(
                ( x + r.x ) * 0.5,
                ( y + r.y ) * 0.5);
		}
		//! @}

		//! @name Comparison operators
        //! @{
		inline bool operator==(const Vector2 & r) const { return (x == r.x) && (y == r.y); }
		inline bool operator!=(const Vector2 & r) const {  return !operator==(r); }
        //! @}
	};
}
#endif
