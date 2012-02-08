#include "./framelistener.hpp"
#include "./o3engine.hpp"

namespace o3engine
{
	// Destructor
	FrameListener::~FrameListener()
	{   // Unregister from engine
		disableFrameListening();
	}

	// Activate FrameListener
    bool FrameListener::enableFrameListening()
    {
        // Registre this frame listener
        return O3Engine::getSingleton().registerFrameListener(this);
    }

    // Activate FrameListener
    bool FrameListener::disableFrameListening()
    {
        // Registre this frame listener
        return O3Engine::getSingleton().unregisterFrameListener(this);
    }

    // Activate FrameListener
    bool FrameListener::isFrameListeningEnabled()
    {
        // Registre this frame listener
        return O3Engine::getSingleton().isFrameListenerRegistered(this);
    }
}
