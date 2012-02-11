#include "./platform.hpp"
#include "./inputprocessor.hpp"
#include <GL/glx.h>

namespace o3engine {

	// Internal implementation of platform
	class Platform::impl {
	public:

		void (*swapInterval)(int);

		impl() {
			swapInterval = (void (*)(int))glXGetProcAddress((const GLubyte*) "glXSwapIntervalMESA");
		}

		static void callbackIdleFunc() {
			::glutPostRedisplay();
		}

	};

	// Constructor
	Platform::Platform() :
			pimpl(NULL) {
		pimpl = new impl();
	}

	// Destructor
	Platform::~Platform() {
		if (pimpl)
			delete pimpl;
	}

	// Initialization
	bool Platform::init() {

		// Create timer
		mp_timer = new Timer();
		mp_timer->reset();

		// Setup Callback functions
		::glutIdleFunc(impl::callbackIdleFunc);
		return true;
	}

	// Enable vsync while rendering
	void Platform::enableVSync() {
		pimpl->swapInterval(1);
	}

	//! Disable vsync while rendering
	void Platform::disableVSync() {
		pimpl->swapInterval(0);
	}
}
