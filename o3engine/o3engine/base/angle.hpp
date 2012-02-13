#ifndef O3ENGINE_ANGLE_HPP_INCLUDED
#define O3ENGINE_ANGLE_HPP_INCLUDED

#include "./base_prereqs.hpp"

namespace o3engine
{
		//! [R5] Class representing radians
	/**
	 * @par Class Characteristics
	 * Radian is @ref copyable_page, @ref noninherit_page and follows the @ref sfn_page
	 * @ingroup base_group
	 */
	class Radian {
	private:
		Real m_angle;

	public:
		//! Constant Zero Radian
		const static Radian ZERO;

		//! Constructor (Initializes to 0)
		inline Radian() :
				m_angle(0) {
		}

		//! Construct from a radian value
		inline explicit Radian(Real r) :
				m_angle(r) {
		}

		//! @name Mathematical operators
		//! @{
		inline Radian operator+(const Radian & r) const {
			return Radian(m_angle + r.m_angle);
		}
		inline Radian operator-(const Radian & r) const {
			return Radian(m_angle - r.m_angle);
		}
		inline Radian operator*(const Radian & r) const {
			return Radian(m_angle * r.m_angle);
		}
		inline Radian operator*(Real f) const {
			return Radian(m_angle * f);
		}
		inline Radian operator/(const Radian & r) const {
			return Radian(m_angle / r.m_angle);
		}
		inline Radian & operator+=(const Radian & r) {
			m_angle += r.m_angle;
			return *this;
		}
		inline Radian & operator-=(const Radian & r) {
			m_angle -= r.m_angle;
			return *this;
		}
		inline Radian & operator*=(const Radian & r) {
			m_angle *= r.m_angle;
			return *this;
		}
		inline Radian & operator*=(Real f) {
			m_angle *= f;
			return *this;
		}
		inline Radian & operator/=(const Radian & r) {
			m_angle /= r.m_angle;
			return *this;
		}
		inline Radian & operator=(const Real f) {
			m_angle = f;
			return *this;
		}
		//! @}

		//! @name Comparison operators
		//! @{
		inline bool operator==(const Radian & r) const {
			return m_angle == r.m_angle;
		}
		inline bool operator!=(const Radian & r) const {
			return m_angle != r.m_angle;
		}
		inline bool operator<(const Radian & r) const {
			return m_angle < r.m_angle;
		}
		inline bool operator<=(const Radian & r) const {
			return m_angle <= r.m_angle;
		}
		inline bool operator>(const Radian & r) const {
			return m_angle > r.m_angle;
		}
		inline bool operator>=(const Radian & r) const {
			return m_angle >= r.m_angle;
		}
		//! @}

		//! Cast to Real operator
		operator Real() const {
			return m_angle;
		}

		//! Scale operator with a real number
		inline Radian & scale(Real factor) {
			m_angle *= factor;
			return *this;
		}
	};

	//! [R5] Class representing degrees
	/**
	 * @par Class Characteristics
	 * Degree is @ref copyable_page, @ref noninherit_page and follows the @ref sfn_page
	 * @ingroup base_group
	 */
	class Degree {
	private:
		Real m_angle;

	public:
		//! Constant Zero Degree
		const static Degree ZERO;

		//! Constructor (Initializes to 0)
		inline Degree() :
				m_angle(0) {
		}

		//! Construct from a real value of degrees
		inline explicit Degree(Real r) :
				m_angle(r) {
		}

		//! @name Mathematical operators
		//! @{
		inline Degree operator+(const Degree & r) const {
			return Degree(m_angle + r.m_angle);
		}
		inline Degree operator-(const Degree & r) const {
			return Degree(m_angle - r.m_angle);
		}
		inline Degree operator*(const Degree & r) const {
			return Degree(m_angle * r.m_angle);
		}
		inline Degree operator*(Real f) const {
			return Degree(m_angle * f);
		}
		inline Degree operator/(const Degree & r) const {
			return Degree(m_angle / r.m_angle);
		}
		inline Degree & operator+=(const Degree & r) {
			m_angle += r.m_angle;
			return *this;
		}
		inline Degree & operator-=(const Degree & r) {
			m_angle -= r.m_angle;
			return *this;
		}
		inline Degree & operator*=(const Degree & r) {
			m_angle *= r.m_angle;
			return *this;
		}
		inline Degree & operator*=(Real f) {
			m_angle *= f;
			return *this;
		}
		inline Degree & operator/=(const Degree & r) {
			m_angle /= r.m_angle;
			return *this;
		}
		inline Degree & operator=(Real f) {
			m_angle = f;
			return *this;
		}
		//! @}

		//! @name Comparison operators
		//! @{
		inline bool operator==(const Degree & r) const {
			return m_angle == r.m_angle;
		}
		inline bool operator!=(const Degree & r) const {
			return m_angle != r.m_angle;
		}
		inline bool operator<(const Degree & r) const {
			return m_angle < r.m_angle;
		}
		inline bool operator<=(const Degree & r) const {
			return m_angle <= r.m_angle;
		}
		inline bool operator>(const Degree & r) const {
			return m_angle > r.m_angle;
		}
		inline bool operator>=(const Degree & r) const {
			return m_angle >= r.m_angle;
		}
		//! @}

		//! Cast to Real operator
		inline operator Real() const {
			return m_angle;
		}

		//! Scale operator with a real number
		inline Degree & scale(Real factor) {
			m_angle *= factor;
			return *this;
		}
	};

	//! [R5] Class representing an angle
	/**
	 * The O3Engine uses this type for expressing angles.
	 * It is a flexible way to express angles without woring about
	 * in what form it is passed (degrees or radian). To create an
	 * angle object from a value , you must pass an object of type Degree or Radian.
	 * @par Class Characteristics
	 * Angle is @ref copyable_page, @ref noninherit_page and follows the @ref sfn_page
	 * @ingroup base_group
	 */
	class Angle {
	private:
		Real m_radAngle;

	public:
		//! Constant Zero Angle
		const static Angle ZERO;

		//! Constructor (Initializes to 0)
		inline Angle() :
				m_radAngle(0) {
		}

		//! Construct from a Radian object
		inline Angle(const Radian & r) :
				m_radAngle(r) {
		}

		//! Construct from a Degree object
		inline Angle(const Degree & r) :
				m_radAngle((Real) r * math::DEG2RAD) {
		}

		//! @name Mathematical operators
		//! @{
		inline Angle operator+(const Angle & r) const {
			return Angle(Radian(m_radAngle + r.m_radAngle));
		}
		inline Angle operator-(const Angle & r) const {
			return Angle(Radian(m_radAngle - r.m_radAngle));
		}
		inline Angle operator*(const Angle & r) const {
			return Angle(Radian(m_radAngle * r.m_radAngle));
		}
		inline Angle operator*(const Real & factor) const {
			return Angle(Radian(m_radAngle * factor));
		}
		inline Angle operator/(const Angle & r) const {
			return Angle(Radian(m_radAngle / r.m_radAngle));
		}
		inline Angle & operator+=(const Angle & r) {
			m_radAngle += r.m_radAngle;
			return *this;
		}
		inline Angle & operator-=(const Angle & r) {
			m_radAngle -= r.m_radAngle;
			return *this;
		}
		inline Angle & operator*=(const Angle & r) {
			m_radAngle *= r.m_radAngle;
			return *this;
		}
		inline Angle & operator*=(const Real & factor) {
			m_radAngle *= factor;
			return *this;
		}
		inline Angle & operator/=(const Angle & r) {
			m_radAngle /= r.m_radAngle;
			return *this;
		}
		//! @}

		//! @name Comparison operators
		//! @{
		inline bool operator==(const Angle & r) const {
			return m_radAngle == r.m_radAngle;
		}
		inline bool operator!=(const Angle & r) const {
			return m_radAngle != r.m_radAngle;
		}
		inline bool operator<(const Angle & r) const {
			return m_radAngle < r.m_radAngle;
		}
		inline bool operator<=(const Angle & r) const {
			return m_radAngle <= r.m_radAngle;
		}
		inline bool operator>(const Angle & r) const {
			return m_radAngle > r.m_radAngle;
		}
		inline bool operator>=(const Angle & r) const {
			return m_radAngle >= r.m_radAngle;
		}
		//! @}

		//! @name Cast operators
		//! @{
		inline operator Degree() const {
			return Degree(m_radAngle * math::RAD2DEG);
		}
		inline operator Radian() const {
			return Radian(m_radAngle);
		}
		inline Real getDegrees() const {
			return m_radAngle * math::RAD2DEG;
		}
		inline Real getRadian() const {
			return m_radAngle;
		}
		//! @}

		//! Scale operator with a real number
		inline Angle & scale(Real factor) {
			m_radAngle *= factor;
			return *this;
		}

		//! Normalize Angle to be part of a circle from 0-360 (in degrees)
		inline void normalize() {
			if ((m_radAngle > math::DOUBLE_PI) || (m_radAngle < (-math::DOUBLE_PI)))
				m_radAngle = math::mod(m_radAngle, math::DOUBLE_PI);
		}
	};

	// Extra math functions for Angle, Radian and Degree
	namespace math {
		//! Cosine (given in Angle)
		/**
		 * Compute the cosine of the angle given in Angle.
		 * @see cos(Real)
		 */
		inline Real cos(const Angle & angle) {
			return ::cos(angle.getRadian());
		}

		//! Sine (given in Angle)
		/**
		 * Compute the sine of angle given in Angle.
		 * @see sin(Real)
		 */
		inline Real sin(const Angle & angle) {
			return ::sin(angle.getRadian());
		}
	}
}
#endif
