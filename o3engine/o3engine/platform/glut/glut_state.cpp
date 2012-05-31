#include "./glut_state.hpp"
#include "../../materialmanager.hpp"
#include <stdexcept>
#include <GL/glx.h>

namespace o3engine {
	//- SINGLETON Initialization
	template<> GLUTState* Singleton<GLUTState>::ms_singleton = 0;


	bool GLUTState::initializeGlew() {
		if (m_glew_initialized)
			return false;

		// Start glew
		GLenum err = glewInit();
		if (err != GLEW_OK) {
						/* Problem: glewInit failed, something is seriously wrong. */
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
			throw new std::runtime_error("Cannot initialize GLEW!");
		}

		//TODO :Very ugly hack. Some stuff can only need be initialized if there is a output device
		ogl::context::create();
		MaterialManager::getSingletonPtr()->initialize();
		ogl::current_ctx().depth_test().enable();

		// Get swap interval function
		mf_swap_interval = (void 	(*)(int)) glXGetProcAddress((const GLubyte*) "glXSwapIntervalSGI");
		if (!mf_swap_interval)
			mf_swap_interval = (void (*)(int)) glXGetProcAddress((const GLubyte*) "glXSwapIntervalMESA");

		m_glew_initialized = true;
		return true;
	}

	bool GLUTState::swapInterval(int v) {
		initializeGlew();
		mf_swap_interval(v);
		return true;
	}
}
