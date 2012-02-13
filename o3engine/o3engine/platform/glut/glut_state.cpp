#include "./glut_state.hpp"

namespace o3engine {
	//- SINGLETON Initialization
	template<> GLUTState* Singleton<GLUTState>::ms_singleton = 0;

}
