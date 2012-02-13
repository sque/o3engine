#include "./framelistener.hpp"
#include "./o3engine.hpp"

namespace o3engine {
	// Destructor
	FrameListener::~FrameListener() { // Unregister from engine
		disableFrameListening();
	}

	// Activate FrameListener
	bool FrameListener::enableFrameListening() {
		return O3Engine::getSingleton().attachFrameListener(*this);
	}

	// Activate FrameListener
	bool FrameListener::disableFrameListening() {
		return O3Engine::getSingleton().detachFrameListener(*this);
	}

	// Activate FrameListener
	bool FrameListener::isFrameListeningEnabled() {
		return O3Engine::getSingleton().isFrameListenerAttached(*this);
	}
}
