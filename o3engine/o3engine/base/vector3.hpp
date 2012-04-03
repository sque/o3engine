#ifndef O3ENGINE_VECTOR3_HPP_INCLUDED
#define O3ENGINE_VECTOR3_HPP_INCLUDED

#include "./base_prereqs.hpp"
#include "./vector2.hpp"

namespace o3engine {
	//! [R5] Class representing a vector in 3D space
	/**
	 * This class is useful for representing any kind of vector in 3D space.
	 * It is light and generally fast and contains a number of feature
	 * very useful when working with vectors. It also provides overloaded arithmetic
	 * operators to facilitate the interaction of Vector3 objects.
	 *
	 * @par Class Characteristics
	 * 	Vector3 is @ref copyable_page, @ref noninherit_page and follows the @ref sfn_page
	 * @ingroup base_group
	 */
	class Vector3 {
	public:
		//! The value of X component.
		Real x;
		//! The value of Y component.
		Real y;
		//! The value of Z component.
		Real z;

		//! @name Common special vectors
		//! @{

		//! Constant value representing vector on xyz(0,0,0)
		static const Vector3 ZERO;
		//! Constant value representing vector on xyz(1,1,1)
		static const Vector3 IDENTITY;
		//! Constant value representing vector on xyz(1,0,0)
		static const Vector3 UNIT_X;
		//! Constant value representing vector on xyz(0,1,0)
		static const Vector3 UNIT_Y;
		//! Constant value representing vector on xyz(0,0,1)
		static const Vector3 UNIT_Z;
		//! Constant value representing vector on xyz(-1,-1,-1)
		static const Vector3 NEGATIVE_IDENTITY;
		//! Constant value representing vector on xyz(-1,0,0)
		static const Vector3 NEGATIVE_UNIT_X;
		//! Constant value representing vector on xyz(0,-1,0)
		static const Vector3 NEGATIVE_UNIT_Y;
		//! Constant value representing vector on xyz(0,0,-1)
		static const Vector3 NEGATIVE_UNIT_Z;
		//! @}

		//! Default constructor
		/**
		 * Creates a Vector3. Vector is <b>NOT</b> initialized for
		 * reasons of efficiency
		 */
		inline Vector3() {
		}

		//! Construct with predefined values
		/**
		 * Construct and initialize the Vector3 with custom values, which are passed
		 * as parameters at the constructor
		 * @param _x The X value of 3d vector.
		 * @param _y The Y value of 3d vector.
		 * @param _z The Z value of 3d vector
		 */
		inline Vector3(Real _x, Real _y, Real _z) :
				x(_x), y(_y), z(_z) {
		}

		//! Construct a Vector3 from Vector2
		/**
		 * Sometimes we want to upgrade from 2D space to 3D, this is a fast
		 * way to translate 2D coordinates on 3D on XY plane with Z = 0. This means
		 * that the new Vector3 object will have x and y values equal to those of
		 * Vector2 and z value equal to zero.
		 * @param v2 The Vector2 object that will use to initialize
		 * @param _z The Z factor of this object. By default it is initialized to zero.
		 */
		inline Vector3(const Vector2 & v2, Real _z = 0) :
				x(v2.x), y(v2.y), z(_z) {
		}

		//! @name Operators of Vector3 object (textual or algebraically)
		//! @{

		//! Translate the object based on 3 values representing the translation on 3 axis.
		/**
		 * @param _x The translation of Vector3 on X-axis.
		 * @param _y The translation of Vector3 on Y-axis.
		 * @param _z The translation of Vector3 on Z-axis.
		 */
		inline void translate(Real _x, Real _y, Real _z) {
			x += _x;
			y += _y;
			z += _z;
		}

		//! Translate the object based on a Vector3 representing the translation
		/**
		 * Translation will occur on 3-axis based on the values of the passed Vector3 object
		 * @param r The Vector3 object describing the translation
		 */
		inline void translate(const Vector3 & r) {
			x += r.x;
			y += r.y;
			z += r.z;
		}

		//! Direct member access operator (Constant)
		/**
		 * You can retrieve a parameter of Vector3 in a way that it
		 * was an array of 3 values. Lower (0) is <b>X</b> and higher (2) is <b>Z</b>
		 */
		inline Real operator[](int mem) const {
			return (&x)[mem];
		}

		//! Direct member access operator
		/**
		 * You can retrieve a parameter of Vector3 in a way that it
		 * was an array of 3 values. Lower (0) is <b>X</b> and higher (2) is <b>Z</b>
		 */
		inline Real & operator[](int mem) {
			return (&x)[mem];
		}

		//! Addition operator
		/**
		 * Performs a vector addition and returns the results. This action is exactly
		 * the same as the translation. The current objects remains the same after the operation.
		 * @param r The Vector3 object representing the r-value of the addition.
		 * @return A Vector3 object with the result
		 */
		inline Vector3 operator +(const Vector3 &r) const {
			return Vector3(x + r.x, y + r.y, z + r.z);
		}

		//! Self-Addition operator
		/**
		 * Performs a vector addition on the current object and becomes the result of the operation.
		 * @param r The Vector3 object representing the r-value of the addition.
		 * @return A reference to the same object, which is also the result of the operation
		 */
		inline Vector3 & operator +=(const Vector3 &r) {
			x += r.x;
			y += r.y;
			z += r.z;
			return *this;
		}

		//! Subtraction operator
		/**
		 * Subtracts a vector from this one and returns the result.
		 * @param r The Vector3 object representing the r-value of the subtraction.
		 * @return A Vector3 object holding the result of the subtraction.
		 */
		inline Vector3 operator -(const Vector3 &r) const {
			return Vector3(x - r.x, y - r.y, z - r.z);
		}

		//! Self-Subtraction operator
		/**
		 * Subtracts a vector from this one and becomes the result of the operation.
		 * @param r The Vector3 object representing the r-value of the subtraction.
		 * @return A reference to the same object, which is also the result of the operation.
		 */
		inline Vector3 & operator -=(const Vector3 &r) {
			x -= r.x;
			y -= r.y;
			z -= r.z;
			return *this;
		}

		//! Scale operator
		/**
		 * Scales all values of the vector by a factor.
		 * @param scale_factor The factor by which the parameters of vector will be multiplied with.
		 * @return A Vector3 object holding the result of the operation.
		 */
		inline Vector3 operator *(Real scale_factor) const {
			return Vector3(x * scale_factor, y * scale_factor, z * scale_factor);
		}

		//! Multiply operator
		/**
		 * Multiplies two vectors by multiplying element-by-element.
		 * @param r The r-value of the operation
		 * @return A Vector3 object holding the result of the operation.
		 */
		inline Vector3 operator *(const Vector3 & r) const {
			return Vector3(x * r.x, y * r.y, z * r.z);
		}

		//! Self-Scale operator
		/**
		 * Scales all values of the vector by a factor and becomes the result of the operation.
		 * @param scale_factor The factor by which the parameters of vector will be multiplied with.
		 * @return A reference to the same object, which is also the result of the operation.
		 */
		inline const Vector3 & operator *=(Real scale_factor) {
			x *= scale_factor;
			y *= scale_factor;
			z *= scale_factor;
			return *this;
		}

		//! Self-Multiply operator
		/**
		 * Multiplies this vector and another by multiplying element-by-element.
		 * The result is saved in this object again.
		 * @param r The r-value of the operation
		 * @return A reference to the same object, which is also the result of the operation.
		 */
		inline Vector3 & operator *=(const Vector3 & r) {
			x *= r.x;
			y *= r.y;
			z *= r.z;
			return *this;
		}

		//! Opposite operator
		/**
		 * It will calculate and return the opposite vector.
		 * @return A Vector3 object holding the opposite vector
		 * @see getOpposite
		 */
		inline Vector3 operator -() const {
			return Vector3(-x, -y, -z);
		}

		//! Less comparison operator
		inline bool operator <(const Vector3 & rhv) const {
			return squaredLength() < rhv.squaredLength();
		}

		//! More comparison operator
		inline bool operator >(const Vector3 & rhv) const {
			return squaredLength() > rhv.squaredLength();
		}

		//! Get the opposite vector
		/**
		 * It will calculate and return the opposite vector.
		 * @return A Vector3 object holding the opposite vector
		 * @see operator-
		 */
		inline Vector3 opposite() const {
			return Vector3(-x, -y, -z);
		}

		//! Normalize vector
		/**
		 * It will calculate the unit vector that has the same direction as this one and
		 * replace the current values.
		 * @return The old length of this vector
		 * @see normal
		 */
		inline Real normalize() {
			Real fLength = math::sqrt(x * x + y * y + z * z);

			// Will also work for zero-sized vectors, but will change nothing
			if (fLength > 1e-08) {
				Real fInvLength = 1.0 / fLength;
				x *= fInvLength;
				y *= fInvLength;
				z *= fInvLength;
			}

			return fLength;
		}

		//! Get the normal vector of this vector
		/**
		 * It will calculate the unit vector the same direction as this one and return
		 * it without affecting this one.
		 * @return The normal vector.
		 * @see normalize
		 */
		inline Vector3 normal() const {
			Vector3 tmp_normalized(*this);
			tmp_normalized.normalize();
			return tmp_normalized;
		}

		//! @}

		//! @name Products of vectors
		//! @{

		//! Calculate the cross-product of this vector with another
		/**
		 * The cross-product is normally used to calculate the normal
		 * vector of a plane, by calculating the cross-product of 2
		 * non-equivalent vectors which lie on the plane (e.g. 2 edges
		 * of a triangle).
		 * @param
		 * r Vector which, together with this one, will be used to
		 * calculate the cross-product.
		 * @return
		 * A vector which is the result of the cross-product. This
		 * vector will <b>NOT</b> be normalized, to maximize efficiency
		 * - call Vector3::normalize on the result if you wish this to
		 * be done. As for which side the resultant vector will be on, the
		 * returned vector will be on the side from which the arc from 'this'
		 * to rkVector is anticlockwise, e.g. UNIT_Y.crossProduct(UNIT_Z)
		 * = UNIT_X, whilst UNIT_Z.crossProduct(UNIT_Y) = -UNIT_X.
		 * This is because OGRE uses a right-handed coordinate system.
		 * @parFor a clearer explanation, look a the left and the bottom edges
		 * of your monitor's screen. Assume that the first vector is the
		 * left edge and the second vector is the bottom edge, both of
		 * them starting from the lower-left corner of the screen. The
		 * resulting vector is going to be perpendicular to both of them
		 * and will go <i>inside</i> the screen, towards the cathode tube
		 * (assuming you're using a CRT monitor, of course).
		 * @note This function is based on OGRE's implementation
		 */
		inline Vector3 crossProduct(const Vector3 & r) const {
			return Vector3(y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.x);
		}

		//! Calculates the dot (scalar) product of this vector with another.
		/**
		 * @param
		 * r Vector3 with which to calculate the dot product (together
		 * with this one).
		 * @return
		 * A float representing the dot product value.
		 * @remarks
		 * The dot product can be used to calculate the angle between 2
		 * vectors. If both are unit vectors, the dot product is the
		 * cosine of the angle; otherwise the dot product must be
		 * divided by the product of the lengths of both vectors to get
		 * the cosine of the angle. This result can further be used to
		 * calculate the distance of a point from a plane.
		 * @note This function is based on OGRE's implementation
		 */
		inline Real dotProduct(const Vector3 & r) const {
			return x * r.x + y * r.y + z * r.z;
		}

		//! Calculate the distance between this and another vector
		/**
		 * If you want to compare 2 distances use squaredDistance as
		 * it is less expensive to calculate than this.
		 * @param r The vector that will calculate how far is from us.
		 * @return The distance between two vectors.
		 * @see squaredDistance
		 */
		inline Real distance(const Vector3 & r) const {
			return (*this - r).length();
		}

		//! Calculate the squared distance between this and another vector
		/**
		 * If you want real distance use Vector3::distance instead of this
		 * but if you want to just compare distances this is better.
		 * @param r The vector that will calculate how far is from us.
		 * @return The squared distance between two vectors.
		 * @see distance
		 */
		inline Real squaredDistance(const Vector3 & r) const {
			return (*this - r).squaredLength();
		}

		//! @}

		//! Get the length of the vector
		/**
		 * It will calculate the length of this vector.
		 * @return The length of this vector
		 * @see getSquaredLength
		 */
		inline Real length() const {
			return math::sqrt(x * x + y * y + z * z);
		}

		//! Get the squared length of the vector
		/**
		 * It will calculate the squared length of this vector. Although this value is useless
		 * for direct usage, it is wise to use it when you want to compare lengths of vectors
		 * as it is quite faster operation. If you need real length use length()
		 * @return The squared length of this vector
		 * @see length
		 */
		inline Real squaredLength() const {
			return x * x + y * y + z * z;
		}

		//! Interpolated transaction to a destination Vector3 object.
		/**
		 * With interpolation you can easily calculate the intercalary vectors
		 * between this vector and a target one. Very useful for creating
		 * smooth movements on simulated world.
		 * @param dst The target Vector3 object
		 * @param factor The step of the transaction which is a value
		 * 	between 0.0 and 1.0. If the factor is 0 then the result is the current
		 * 	Vector3 object. If the value is 1 the result is the target Vector3 object and
		 * 	all the middle values provides the step of the transaction from current position
		 * 	to the target one.
		 * 	@return The result of the calculation.
		 */
		inline Vector3 interpolated(const Vector3 & dst, Real factor) const {
			return Vector3(x + ((dst.x - x) * factor), y + ((dst.y - y) * factor),
					z + ((dst.z - z) * factor));
		}

		//! Calculate the midpoint of this vector with another
		inline Vector3 midPoint(const Vector3 & r) const {
			return Vector3((x + r.x) * 0.5, (y + r.y) * 0.5, (z + r.z) * 0.5);
		}

		//! @name Comparison operators
		//! @{

		//! Comparison operator
		/**
		 * Compares this object with another Vector3 and returns if their parameters are all equal
		 * @param r The Vector3 object representing r-value of the assignment.
		 */
		inline bool operator ==(const Vector3 &r) const {
			return (x == r.x) && (y == r.y) && (z == r.z);
		}

		//! Difference comparison operator
		/**
		 * Compares if this object has different values from another Vector3 object.
		 * @param r The Vector3 object representing r-value of difference comparison.
		 */
		inline bool operator !=(const Vector3 &r) const {
			return !operator==(r);
		}

		//! @}
	};
}

#endif
