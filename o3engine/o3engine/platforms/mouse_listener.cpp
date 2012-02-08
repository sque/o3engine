#include "./mouse_listener.hpp"
#include "./input_processor.hpp"

namespace o3engine
{
    MouseListener::~MouseListener()
    {   disableMouseListening();       }

    bool MouseListener::enableMouseListening()
    {
        return InputProcessor::getSingleton().registerListener(this);
    }

    // Stop monitoring for events
    bool MouseListener::disableMouseListening()
    {
        return InputProcessor::getSingleton().unregisterListener(this);
    }

    bool MouseListener::isMouseListeningEnabled()
    {
        return InputProcessor::getSingleton().isListenerRegistered(this);
    }
}
