#include "./timer.hpp"

#include <sys/time.h>
#include <time.h>
//#define POSIXTIMER_USE_CLOCK_GETTIME

namespace o3engine {
// Implementation of Posix timer
struct Timer::impl {
#ifdef POSIXTIMER_USE_CLOCK_GETTIME
	struct timespec m_realtime_zero;
#else
	struct timeval m_realtime_zero;
#endif
	clock_t m_cpuclock_zero;

	void reset() {
		// Reset cpu timer
		m_cpuclock_zero = clock();

		// Reset real timer
#ifdef POSIXTIMER_USE_CLOCK_GETTIME
		printf("Timer::Reset() with High-Precision CPU Timer\n");
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &m_realtime_zero);
#else
		printf("Timer::Reset() with High-Precision REAL Timer\n");
		gettimeofday(&m_realtime_zero, NULL);
#endif
	}

	Timer::milliseconds_type getMilliseconds() const {
#ifdef POSIXTIMER_USE_CLOCK_GETTIME
		// High-precision
		struct timespec now;
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &now);
		return (now.tv_sec - m_realtime_zero.tv_sec)*1000 + (now.tv_nsec-m_realtime_zero.tv_nsec)/1000000;
#else
		struct timeval now;
		gettimeofday(&now, NULL);
		return (now.tv_sec - m_realtime_zero.tv_sec) * 1000
				+ (now.tv_usec - m_realtime_zero.tv_usec) / 1000;
#endif
	}

	Timer::microseconds_type getMicroseconds() const {
#ifdef POSIXTIMER_USE_CLOCK_GETTIME
		// High-precision
		struct timespec now;
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &now);
		return (now.tv_sec - m_realtime_zero.tv_sec)*1000000 + (now.tv_nsec-m_realtime_zero.tv_nsec)/1000;
#else
		struct timeval now;
		gettimeofday(&now, NULL);
		return (now.tv_sec - m_realtime_zero.tv_sec) * 1000000
				+ (now.tv_usec - m_realtime_zero.tv_usec);
#endif
	}

	Timer::milliseconds_type getMillisecondsCPU() const {
		clock_t now = clock();
		return (milliseconds_type) ((float) (now - m_cpuclock_zero)
				/ ((float) CLOCKS_PER_SEC / 1000.0));
	}

	Timer::microseconds_type getMicrosecondsCPU() const {
		clock_t now = clock();
		return (microseconds_type) ((float) (now - m_cpuclock_zero)
				/ ((float) CLOCKS_PER_SEC / 1000000.0));
	}
};

Timer::Timer() :
		pimpl(new impl) {
}

Timer::~Timer() {
	if (pimpl)
		delete pimpl;
}

void Timer::reset() {
	pimpl->reset();
}

Timer::milliseconds_type Timer::getMilliseconds() const {
	return pimpl->getMilliseconds();
}

Timer::milliseconds_type Timer::getMillisecondsCPU() const {
	return pimpl->getMillisecondsCPU();
}

Timer::microseconds_type Timer::getMicroseconds() const {
	return pimpl->getMicroseconds();
}

Timer::microseconds_type Timer::getMicrosecondsCPU() const {
	return pimpl->getMicrosecondsCPU();
}
}
