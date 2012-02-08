#include "./platform.hpp"

namespace o3engine
{
	//- SINGLETON Initialization
	template<> Platform* Singleton<Platform>::ms_singleton = 0;
}
