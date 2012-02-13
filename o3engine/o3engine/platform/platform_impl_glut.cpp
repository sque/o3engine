#include "./platform.hpp"
#include "./window.hpp"
#include "./glut_state.hpp"
#include <map>
#include <GL/glx.h>

namespace o3engine {

	// Internal implementation of platform
	class Platform::impl {
	public:
		//! Pointer to glut state
		GLUTState * mp_gstate;

		//! Pointer to loop idle listener
		static LoopIdleListener * mp_idlelistener;

		//! Pointer to function for controlling swap interval (Vsync)
		void (*swapInterval)(int);

		// Construct internal object
		impl() {
			mp_gstate = GLUTState::getSingletonPtr();
			swapInterval = (void (*)(int))::glXGetProcAddress((const GLubyte*) "glXSwapIntervalMESA");
		}

		static void callbackIdleFunc() {
			mp_idlelistener->onLoopIdle();
			::glutPostRedisplay();
		}

	};

	LoopIdleListener * Platform::impl::mp_idlelistener = NULL;

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
	bool Platform::init(int argc, char ** argv) {
		// Start glut
		glutInit(&argc, argv);

		// Create timer
		mp_timer = new Timer();
		mp_timer->reset();

		// Setup callback functions
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

	//! Start event loop (blocking)
	void Platform::startEventLoop(LoopIdleListener & listener){
		Platform::impl::mp_idlelistener = & listener;

		if (!pimpl->mp_gstate->has_windows()) {
			// When no windows exist, create our own loop
			while(1) {
				listener.onLoopIdle();
				//::glutMainLoopEvent();
			}
		} else {
			::glutMainLoop();
		}
	}
}
