#include "./keyboard_listener.hpp"
#include "./input_processor.hpp"

namespace o3engine
{
    KeyboardListener::~KeyboardListener()
    {   disableKeyboardListening();   }

    bool KeyboardListener::enableKeyboardListening()
    {
        return InputProcessor::getSingleton().registerListener(this);
    }

    // Stop monitoring for events
    bool KeyboardListener::disableKeyboardListening()
    {
        return InputProcessor::getSingleton().unregisterListener(this);
    }

    bool KeyboardListener::isKeyboardListeningEnabled()
    {
        return InputProcessor::getSingleton().isListenerRegistered(this);
    }
}
