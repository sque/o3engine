#include "./timesensitive.hpp"
#include "./platforms/platform.hpp"

namespace o3engine {

	// Default constructor
	TimeSensitive::TimeSensitive() {
		// Set pointer to timer zero
		mp_timer = NULL;
	}

	// Destructor
	TimeSensitive::~TimeSensitive() {
		// Don't delete pTimer!!! We shared the pointer of timer by platform manager
		// let him delete it, when everything is ok
	}

	// Get the time passed in seconds
	Real TimeSensitive::timePassed() {
		Real new_time, diff_time;

		// Request a timer if needed
		if (!mp_timer) {
			Platform * p_pl = &Platform::getSingleton();
			mp_timer = & p_pl->getTimer();

			// Get last time
			m_last_time = mp_timer->getMilliseconds();
		}

		new_time = (Real) mp_timer->getMilliseconds();

		diff_time = new_time - m_last_time;
		m_last_time = new_time;
		return diff_time / 1000;
	}

}
