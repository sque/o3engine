#include "./glut_state.hpp"
#include <stdexcept>
#include <GL/glx.h>

namespace o3engine {
	//- SINGLETON Initialization
	template<> GLUTState* Singleton<GLUTState>::ms_singleton = 0;


	bool GLUTState::initialize_glew() {
		if (m_glew_initialized)
			return false;

		// Start glew
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			/* Problem: glewInit failed, something is seriously wrong. */
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
			throw new std::runtime_error("Cannot initialize GLEW!");
		}

		// Get swap interval function
		mf_swap_interval = (void 	(*)(int)) glXGetProcAddress((const GLubyte*) "glXSwapIntervalSGI");
		if (!mf_swap_interval)
			mf_swap_interval = (void (*)(int)) glXGetProcAddress((const GLubyte*) "glXSwapIntervalMESA");

		m_glew_initialized = true;
		return true;
	}

	bool GLUTState::swapInterval(int v) {
		initialize_glew();
		mf_swap_interval(v);
	}
}
