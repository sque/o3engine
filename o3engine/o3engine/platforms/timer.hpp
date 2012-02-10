#ifndef O3ENGINE_TIMER_HPP_INCLUDED
#define O3ENGINE_TIMER_HPP_INCLUDED

#include "../prereqs.hpp"
#include <time.h>

namespace o3engine
{
	//! [R4] A platform independent timer
	/**
	 * It is a timer to get real time passed or cpu time passed, and
	 * it is platform independent.
	 * @par Class Characteristics
	 * Timer is @ref noncopyable_page, @ref inherit_page and follows the @ref sfn_page
	 */
	class Timer
	{
	public:
		//! Type definition of milliseconds
		typedef unsigned long milliseconds_type;

		//! Type definition of microseconds
		typedef unsigned long microseconds_type;

	private:
		// Pimpl Idiom
		class impl;
		impl * pimpl;

		// Non Copyable
		Timer & operator=(const Timer &);
		Timer(const Timer &);

	public:
		//! Creates a timer.
		/**
		 * @remarks
		 * You must call reset() after creating it; the constructor cannot do it because the
		 * call would not be polymorphic.
		*/
		Timer();

		//! Destructor
		virtual ~Timer();

		//! Reset Timer
		void reset();

		//! Returns milliseconds since initialisation or last reset
		milliseconds_type getMilliseconds() const;

		//! Returns milliseconds since initialisation or last reset, only CPU time measured
		milliseconds_type getMillisecondsCPU() const;

		//! Returns microseconds since initialisation or last reset
		microseconds_type getMicroseconds() const;

		//! Returns microseconds since initialisation or last reset, only CPU time measured
		microseconds_type getMicrosecondsCPU() const;
	} ;
}

#endif
