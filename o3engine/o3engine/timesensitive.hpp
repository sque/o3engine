/*
 Copied from the NAG Project (notagame.ath.cx)
 Copyright 2005 NAG Team
 */
#ifndef O3ENGINE_TIMESENSITIVE_HPP_INCLUDED
#define O3ENGINE_TIMESENSITIVE_HPP_INCLUDED

#include "./prereqs.hpp"

namespace o3engine {

	//! [R4] A function to create time sensitive objects.
	/**
	 * Very useful for objects that needs to know how much time passed since last action.
	 * @par Class Characteristics
	 * TimeSensitive is @ref noncopyable_page, @ref inherit_page and follows the @ref sfn_page
	 */
	class TimeSensitive {
	private:
		//! A number of seconds representing last time
		Real m_last_time;

		//! Timer object
		const Timer * mp_timer;

		// Uncopiable
		TimeSensitive(const TimeSensitive &);
		TimeSensitive& operator=(const TimeSensitive &);
	public:
		//! Default constructor
		TimeSensitive();

		//! Destructor
		virtual ~TimeSensitive();

		//! Returns how much time passed since last time that this function was called.
		/**
		 * This function returns REAL time and not CPU time. The timer is reseted at the construction of
		 * the object and every time this function is called. The accuracy of this function is near 1/1000 seconds.
		 * @return The time passed in seconds.
		 */
		Real timePassed();
	};

}

#endif
