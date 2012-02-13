#include "./timer.hpp"
#include <time.h>

namespace o3engine
{
    // Implementation of Posix timer
    class Timer::impl
    {
	public:
        clock_t m_cpuclock_zero;

        void reset()
        {
            // Reset cpu timer
            m_cpuclock_zero = clock();

        }

        Timer::milliseconds_type getMilliseconds() const
        {	
			return getMillisecondsCPU();
		}

        Timer::microseconds_type getMicroseconds() const
        {
            return getMicrosecondsCPU();
        }

        Timer::milliseconds_type getMillisecondsCPU() const
        {   clock_t now = clock();
            return (milliseconds_type)((float)(now - m_cpuclock_zero) / ((float)CLOCKS_PER_SEC/1000.0)) ;
        }

        Timer::microseconds_type getMicrosecondsCPU() const
        {   clock_t now = clock();
            return (microseconds_type)((float)(now-m_cpuclock_zero) / ((float)CLOCKS_PER_SEC/1000000.0)) ;
        }
    };

    Timer::Timer()
        :pimpl(new impl)
    {}

    Timer::~Timer()
    {   if (pimpl) delete pimpl;  }

    void Timer::reset()
    {   pimpl->reset();     }

    Timer::milliseconds_type Timer::getMilliseconds() const
    {   return pimpl->getMilliseconds();    }

	Timer::milliseconds_type Timer::getMillisecondsCPU() const
	{   return pimpl->getMillisecondsCPU();    }

    Timer::microseconds_type Timer::getMicroseconds() const
    {   return pimpl->getMicroseconds();    }

	Timer::microseconds_type Timer::getMicrosecondsCPU() const
	{   return pimpl->getMicrosecondsCPU();     }
}
