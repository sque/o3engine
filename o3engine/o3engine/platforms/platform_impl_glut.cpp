#include "./platform.hpp"
#include "./input_processor.hpp"

namespace o3engine {
	// Internal implementation of platform
	class Platform::impl {
	public:

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

		// Create input system
		mp_inputproc = new InputProcessor();

		// Setup Callback functions
		// TODO: window fixglutIdleFunc(impl::glutFuncIdle);
		return true;
	}
}
