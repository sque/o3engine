#include "./../platform.hpp"
#include "./../window.hpp"
#include "./glut_state.hpp"
#include <map>

namespace o3engine {

	// Internal implementation of platform
	class Platform::impl {
	public:
		//! Pointer to glut state
		static GLUTState * mp_gstate;

		//! Pointer to loop idle listener
		static LoopIdleListener * mp_idlelistener;

		// Construct internal object
		impl() {
			mp_gstate = new GLUTState();
		}

		static void callbackIdleFunc() {
			mp_idlelistener->onLoopIdle();
			::glutPostRedisplay();
			if (mp_gstate->hasOffscreens()){
				mp_gstate->redisplayOffscreens();
				glFinish();
			}
		}

	};

	GLUTState * Platform::impl::mp_gstate = 0;
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
	bool Platform::initialize(int argc, char ** argv) {
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
		pimpl->mp_gstate->swapInterval(1);
	}

	//! Disable vsync while rendering
	void Platform::disableVSync() {
		pimpl->mp_gstate->swapInterval(0);
	}

	//! Start event loop (blocking)
	void Platform::startEventLoop(LoopIdleListener & listener){
		Platform::impl::mp_idlelistener = & listener;

		if (!pimpl->mp_gstate->hasWindows()) {
			// When no windows exist, create our own loop
			while(1) {
				if (impl::mp_gstate->hasOffscreens()){
					impl::mp_gstate->redisplayOffscreens();
					glFlush();
					glFinish();
				}
				listener.onLoopIdle();
				//::glutMainLoopEvent();
			}
		} else {
			::glutMainLoop();
		}
	}
}
