#ifndef O3ENGINE_VECTOR4_HPP_INCLUDED
#define O3ENGINE_VECTOR4_HPP_INCLUDED

#include "./base_prereqs.hpp"
#include "./vector3.hpp"

namespace o3engine
{
	//! [R5] Class representing a vector in 4D space
	/**
	 This class is usefull for representing any kind of vector in 4D space.
	 It is light and generally fast and containes a number of feature
	 very usefull when working with vectors.

	 @par Class Characteristics
         Vector4 is @ref copyable_page, @ref noninherit_page and follows the @ref sfn_page
     @ingroup base_group
	 */
	class Vector4
	{
	public:
        //! The X componment.
		Real x;
        //! The Y componment.
		Real y;
		//! The Z componment.
		Real z;
        //! The W componment.
		Real w;

		//! Constant value representing vector on xyzw(0,0,0,0)
		static const Vector4 ZERO;
		//! Constant value representing vector on xyzw(1,1,1,1)
		static const Vector4 IDENTITY;
		//! Constant value representing vector on xyzw(1,0,0,0)
		static const Vector4 UNIT_X;
		//! Constant value representing vector on xyzw(0,1,0,0)
		static const Vector4 UNIT_Y;
		//! Constant value representing vector on xyzw(0,0,1,0)
		static const Vector4 UNIT_Z;
		//! Constant value representing vector on xyzw(0,0,0,1)
		static const Vector4 UNIT_W;
		//! Constant value representing vector on xyzw(-1,-1,-1,-1)
		static const Vector4 NEGATIVE_IDENTITY;
		//! Constant value representing vector on xyzw(-1,0,0,0)
		static const Vector4 NEGATIVE_UNIT_X;
		//! Constant value representing vector on xyzw(0,-1,0,0)
		static const Vector4 NEGATIVE_UNIT_Y;
		//! Constant value representing vector on xyzw(0,0,-1,0)
		static const Vector4 NEGATIVE_UNIT_Z;
		//! Constant value representing vector on xyzw(0,0,0,-1)
		static const Vector4 NEGATIVE_UNIT_W;

        //! Default construct (@b NON-initialized)
        inline Vector4(){}

		//! Construct and initialize vector4
		inline Vector4(Real _x, Real _y, Real _z, Real _w)
            :x(_x),y(_y),z(_z),w(_w){}

		//! Construct from a vector3 and a parameter
		inline Vector4(const Vector3 & v3, Real _w)
            :x(v3.x), y(v3.y), z(v3.z), w(_w){}

        inline Vector4 opposite() const {   return Vector4(-x, -y, -z, -w); }
		inline Vector4 operator-() const {	return Vector4(-x, -y, -z, -w); }
		inline Real distance(const Vector4 & r) const {   return (*this - r).length();    }
		inline Real squaredDistance(const Vector4 & r) const {   return (*this - r).squaredLength();    }
		inline Vector4 interpolated(const Vector4 & dst, Real factor) const
		{   Vector4 tmp_v4 = *this;
			tmp_v4.x += ((dst.x - x) * factor);
			tmp_v4.y += ((dst.y - y) * factor);
			tmp_v4.z += ((dst.z - z) * factor);
			tmp_v4.w += ((dst.w - w) * factor);
			return tmp_v4;
		}

		//! @name math operators
		//! @{
		inline Vector4 operator + (const Vector4 &r) const {   Vector4 t = *this; t+= r; return r;	}
		inline Vector4 & operator += (const Vector4 &r) {   x += r.x; y += r.y; z += r.z; w += r.w; return *this;}
		inline Vector4 operator - (const Vector4 &r) const{   Vector4 t = *this; t-= r; return t;	}
		inline Vector4 & operator -= (const Vector4 &r) { x -= r.x; y -= r.y; z -= r.z; w -= r.w; return *this;	}
		inline Real length() const { return math::sqrt( x * x + y * y + z * z + w * w);	}
		inline Real squaredLength() const { return x * x + y * y + z * z + w * w;	}
		inline Real normalize()
		{   Real fLength = length();

			// Will also work for zero-sized vectors, but will change nothing
			if ( fLength > 1e-08 )
			{
				Real fInvLength = 1.0 / fLength;
				x *= fInvLength;
				y *= fInvLength;
				z *= fInvLength;
				w *= fInvLength;
			}
			return fLength;
		}
		//! @}
    };
}
#endif
