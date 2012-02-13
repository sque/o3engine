#ifndef O3ENGINE_MATH_HPP_INCLUDED
#define O3ENGINE_MATH_HPP_INCLUDED

#include "./base_prereqs.hpp"
#include "./quaternion.hpp"

//! The basic namespace of all
namespace o3engine {

	//! [R5] An organizational namespace for all math related functions
	/**
	 * @ingroup base_group
	 */
	namespace math {
		//! Get an integer random number with defined upper bound
		/**
		 * It will find a random number from 0 to max - 1 value.
		 * @param max The upper bound of random range
		 */
		inline int randomInt(int max) {
			return (int) (((Real) max * rand()) / (Real) RAND_MAX);
		}

		//! Get an Real random number with defined upper bound
		/**
		 * It will find a random number <b>between</b> 0 and max value.
		 * Resolution of float pointing number is defined by RAND_MAX.
		 * @param max The upper bound of random range
		 */
		inline Real randomReal(Real max) {
			return (((Real) rand() * (Real) max) / (Real) RAND_MAX);
		}

		//! Get a random quaternion
		/**
		 * It will return a random quaternion but normalized,
		 * representing a valid rotation/orientation
		 */
		Quaternion randomQuaternion();
	}
}

#endif
