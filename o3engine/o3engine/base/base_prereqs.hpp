#ifndef O3ENGINE_PREREQS_HPP_INCLUDED
#define O3ENGINE_PREREQS_HPP_INCLUDED

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <string>
#include <stdio.h>
#include <cstdint>

// Needed type definitions
namespace o3engine {
	//! Type definition of Real
	/**
	 * @ingroup base_group
	 */
	typedef double Real;

	// Basic Mathematics functions and constants
	namespace math {
		//! PI number
		const static Real PI = 3.14159265358979323846;
		//! Double PI number which means PIx2
		const static Real DOUBLE_PI = PI * 2;
		//! Half PI number which means PI/2
		const static Real HALF_PI = PI / 2;
		//! Multiply factor to convert radians to degrees
		const static Real RAD2DEG = 180.0 / PI;
		//! Multiply factor to convert degrees to radiasn
		const static Real DEG2RAD = PI / 180.0;

		//! Convert a radian number to degree
		inline Real radianToDegree(Real rad) {
			return rad * RAD2DEG;
		}
		//! Convert a degree number to radian
		inline Real degreeToRadian(Real deg) {
			return deg * DEG2RAD;
		}
		//! Return the "absolute" value of float-point number
		inline Real abs(Real fValue) {
			return (Real) ::fabs(fValue);
		}
		//! Square root
		inline Real sqrt(Real value) {
			return ::sqrt(value);
		}
		//! Modulus functions
		/**
		 * Compute the floating-point remainder of a / b
		 */
		inline Real mod(Real a, Real b) {
			return ::fmod(a, b);
		}

		//! Arc Cosine
		/**
		 * Computes the principle value of the arc cosine of x.
		 * @return The result is in the range [0, pi].
		 */
		inline Real arcCos(Real x) {
			return ::acos(x);
		}

		//! Arc Sine
		/**
		 * Computes the principle value of the arc sine of x.
		 * @return The result is in the range [0, pi].
		 */
		inline Real arcSin(Real x) {
			return ::asinf(x);
		}

		//! Cosine
		/**
		 * Compute the cosine of the angle given in radians.
		 * @see cos(const Angle &)
		 */
		inline Real cos(Real angle) {
			return ::cos(angle);
		}

		//! Sine
		/**
		 * Compute the sine of angle (Measured in radians)
		 * @see sin(const Angle &)
		 */
		inline Real sin(Real angle) {
			return ::sin(angle);
		}
	}
}

#endif
