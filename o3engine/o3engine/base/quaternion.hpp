#ifndef O3ENGINE_QUATERNION_HPP_INCLUDED
#define O3ENGINE_QUATERNION_HPP_INCLUDED

#include "./base_prereqs.hpp"
#include "./vector3.hpp"
#include "./vector4.hpp"
#include "./angle.hpp"

namespace o3engine
{
	//!	[R5] Data storage representing a mathematical quaternion.
	/**
        Representation of a quaternion, with a set of tools
		and operations specially optimized for unit quaternions.
		You can use a quaternion to represent a rotation/orientation
		and transform an existing Vector3 object.
	@par Rotation of a Vector
		To rotate a Vector3 (vin)by a rotation expressed with Quaternion (myrot) the formula is:
	@code
	vout = myrot * vin;	// Vout will now hold the rotated Vector3 vin by Quaternion myrot
	@endcode
	@par Adding rotations
		To calculate the final rotations by performing two rotations you just multiply the
		quaternions expressing those 2 rotations. e.g.
	@code
	Quaternion rotationFinal (rotationA * rotationB)
	@endcode
		More can be found at the Quaternion::operator* of documentation.
     @ingroup base_group
     @par Class Characteristics
         Quaternion is @ref copyable_page, @ref noninherit_page and follows the @ref sfn_page
	*/
	class Quaternion
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

		//! A constant representing the Identity (unit) quaternion
		static const Quaternion IDENTITY;

		//! Default constructor of a quaternion
		/**
		@remarks
			Quaternion is <b>NOT</b> initialized for reasons of performance.
		*/
		inline Quaternion(){}

		//! Construct with predefined values
		inline Quaternion(Real _w, Real _x, Real _y, Real _z)
		{	w = _w; x = _x; y = _y; z = _z;    }

		//! Construct from a vector3 object
		/**
			It will set all x,y,z as defined at vector and w part will be set to 0.
		*/
		explicit inline Quaternion(const Vector3 & v3)
		{	w = 0; x = v3.x; y = v3.y; z = v3.z;	}

		//! Construct from Angle-Axis rotation
		/**
			It will construct a quaternion representing the same
			rotation as the one defined by methond Angle-Axis
		@param axis The Axis around which the rotation will be performed
		@param angle The angle of the rotation that will be performed around the axis
		*/
		inline Quaternion(const Vector3 & axis,const Angle & angle)
		{   fromAxisAngle(axis, angle);     }

		//! @name Operators of Quaternion object (textual or argebrical)
		//! @{

		//! Scale operator
		inline Quaternion operator* (Real factor) const
		{   return Quaternion(factor*w, factor*x, factor*y, factor*z);  }

		//! Self-Scale operator
		inline Quaternion & operator*=(Real factor)
		{	w *= factor; x *= factor; y *= factor; z *= factor; return *this;	}

		//! Self-Scale operator
		inline Quaternion & scale(Real factor)
		{	w *= factor; x *= factor; y *= factor; z *= factor; return *this;	}

		//! Scale operator with scalar type on the left
		inline friend Quaternion operator* (Real factor, const Quaternion& r)
		{   return Quaternion(factor*r.w, factor*r.x, factor*r.y, factor*r.z);  }

		//! Multiply operation
		/**
			Quaternions are used for expressing rotations. Multiplication
			of two quaternions that represent 2 rotations will have a rotation result
			that is the same with the sum of two previous rotations.
		@remarks As the nature of rotations is non-commutative the multiplication of
			quaternions is not also. a*b has diferent result with b*a if a<>b.
		@see operator*=
		*/
		Quaternion operator*(const Quaternion & r) const;

		//! Rotate a vector
		/**
			This is a fast way to rotate a vector, by multipling quaternion with
			this you get a rotate vector by this quaternion
		@param rv The vector to rotate.
		@return The rotated vector
		@par Example
			We have Vector3 object vin and we want to rotate with Quaternion qu.
		@code Vector3 vout(qu * vin);	// vout will hold the result of the rotation @endcode
		*/
		Vector3 operator*(const Vector3 & rv) const;

		//! Self-multiply operation
		/**
			It is the same as multiplication operator but this object
			is replaced with result.
		@note See operator* for a brief explanation on multiplications
		*/
		inline Quaternion & operator*=(const Quaternion & r)
		{	return (*this = operator*(r));	}

		//! Additive operator
		inline Quaternion operator+(const Quaternion r) const
		{	return Quaternion(w + r.w, x + r.x, y + r.y, z + r.z);	}

		//! Self-Additive operator
		inline Quaternion & operator+=(const Quaternion r)
		{	w += r.w; x += r.x; y += r.y; z += r.z;	return *this;	}

		//! Compare operator
		inline bool operator==(const Quaternion & r) const
		{	return (x == r.x) && (y == r.y) && (z == r.z) && (w == r.w); 	}

		//! Compare difference operator
		inline bool operator!=(const Quaternion & r) const
		{	return !operator==(r); 	}

		//! Opposite operator
		/**
			Will create a new operator that has all its parts opposite (-w, -x, -y, -z)
		*/
		inline Quaternion operator-() const
		{   return Quaternion(-w, -x, -y, -z);  }

		//! Get the conjucate result of this quaternion (unit inverse)
		/**
			This is the unit inverse of quaternion, it has meaning only
			on unit quaternions and will return w, -x, -y, -z
		*/
		inline Quaternion conjugate() const
		{	return Quaternion(w, -x, -y, -z);	}

		//! Normalize quaternion to unit quaternion
		Quaternion & normalize();

		//! Get normal quaternion of this one
		inline Quaternion normal() const
		{	Quaternion tmp(*this); tmp.normalize(); return tmp;	}

		//! Get square length of quaternion (squared Magnitude)
		Real squaredLength() const
		{   return x*x + y*y + z*z + w*w;   }

		//! Get length of quaternion (Magnitude)
		Real length() const
		{   return math::sqrt(x*x + y*y + z*z + w*w);    }

		//! @}

        //! @name To/From other data types
        //! @{

		//! Cast to Vector3 object using x,y,z parts
		inline operator const Vector3 () const
		{   return Vector3(x, y, z);    }

		//! Replace this quaternion with a rotation expressed by Angle-Axis
		/**
		@param v The vector around which the rotation is performed.
		@param angle The angle of rotation to be performed.
		*/
		void fromAxisAngle(const Vector3 &v, const Angle & angle);

		//! Create an Angle-Axis rotation that has the same result
		/**
			It will convert the rotation expressed by this quaternion
			to an Angle-Axis format.
		@param axis A Vector3 object that the axis will be stored
		@param angle A Angle object that the angle will be stored
		*/
		void toAxisAngle(Vector3 & axis, Angle & angle) const;

		//! The dot product of two quaternions
		inline Real dotProduct(const Quaternion & r)
		{	return w*r.w + x*r.x + y*r.y + z*r.z;	}

		//! Spherical Linear interpolation
		/**
			With this function you can slerp from this quaternion
			to the one passed at dst parameter, the slerp will
			be done with almost linear speed.
		@param dst The target Quaternion of slerping.
		@param factor The current point of slerping in limit [0, 1].
			0 means starting slerping, and 1 finished slerping.
		@return The Quaternion expressing the desired intermediate stage of slerping.
		*/
		Quaternion slerp(const Quaternion & dst, Real factor);

		//! @}
	};
}
#endif
