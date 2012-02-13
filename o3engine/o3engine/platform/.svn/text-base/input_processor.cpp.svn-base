#include "./input_processor.hpp"
#include "../o3engine.hpp"
#include <algorithm>

namespace o3engine
{
	//- SINGLETON Initialization
	template<> InputProcessor* Singleton<InputProcessor>::ms_singleton = 0;

	// Constructor
	InputProcessor::InputProcessor()
        :m_mouse_event(m_mouse_state)
	{
	    // Initiliaze mouse state
		m_mouse_state.m_pos_x = m_mouse_state.m_pos_y = 0;

		// Reset mouse buttons
		for(int i =0;i < MS_BUTTON_MAX;i++)
			m_mouse_state.m_button_state[i]= MS_BUTTON_UP;

		// Reset kb buttons
		for(int i =0;i < KB_VTKEY_MAX;i++)
			mv_key_state[i]= false;
	}

	// Actions to take when new mouse move
	void InputProcessor::raiseMouseMoved(int new_pos_x, int new_pos_y)
	{	MouseListenerIterator mit;

		// Create event
		m_mouse_event.m_rel_x = new_pos_x - m_mouse_state.m_pos_x;
		m_mouse_event.m_rel_y = new_pos_y - m_mouse_state.m_pos_y;

		// We don't want to spawn events for nothing
		if ((m_mouse_event.m_rel_x == 0) && (m_mouse_event.m_rel_y == 0))
			return;

		// Save new state
		m_mouse_state.m_pos_x = new_pos_x;
		m_mouse_state.m_pos_y = new_pos_y;

		for(mit = mv_mouse_listeners.begin();mit != mv_mouse_listeners.end();mit++)
		{
			(*mit)->onMouseMove(m_mouse_event);
		}
	}

	// Actions to take when new mouse move
	void InputProcessor::raiseMouseButtonReleased(E_MS_BUTTONS trigger_button)
	{	MouseListenerIterator mit;

		// Create event
		m_mouse_event.m_rel_x = m_mouse_event.m_rel_y = 0;
		m_mouse_event.m_trigger_button = trigger_button;

		// Broadcast event
		for(mit = mv_mouse_listeners.begin();mit != mv_mouse_listeners.end();mit++)
		{
			(*mit)->onMouseButtonReleased(m_mouse_event);
		}
	}

	// Actions to take when new mouse move
	void InputProcessor::raiseMouseButtonPressed(E_MS_BUTTONS trigger_button)
	{	MouseListenerIterator mit;

		// Create event
		m_mouse_event.m_rel_x = m_mouse_event.m_rel_y = 0;
		m_mouse_event.m_trigger_button = trigger_button;

		// Broadcast event
		for(mit = mv_mouse_listeners.begin();mit != mv_mouse_listeners.end();mit++)
		{
			(*mit)->onMouseButtonPressed(m_mouse_event);
		}
	}

	// Triger keyboard released event
	void InputProcessor::raiseKeyboardReleased(E_KB_VIRTUALKEYS vtkey)
	{	KeyboardListenerIterator kit;
		for (kit = mv_keyboard_listeners.begin();kit != mv_keyboard_listeners.end();kit++)
			(*kit)->onKeyboardButtonReleased(vtkey);
	}

	// Trigger keyboard press event
	void InputProcessor::raiseKeyboardPressed(E_KB_VIRTUALKEYS vtkey)
	{	KeyboardListenerIterator kit;
		for (kit = mv_keyboard_listeners.begin();kit != mv_keyboard_listeners.end();kit++)
			(*kit)->onKeyboardButtonPressed(vtkey);
	}

	// Trigger keyboard character insert
	void InputProcessor::raiseKeyboardCharInsert(unsigned char ch)
	{	KeyboardListenerIterator kit;
		for (kit = mv_keyboard_listeners.begin();kit != mv_keyboard_listeners.end();kit++)
			(*kit)->onKeyboardCharInsert(ch);
	}

	// Register mouse listener
	bool InputProcessor::registerListener(MouseListener * p_mlistener)
	{
	    if (isListenerRegistered(p_mlistener))
	        return false;

		mv_mouse_listeners.push_back(p_mlistener);
		return true;
	}

	// Unregister mouse listener
	bool InputProcessor::unregisterListener(MouseListener * p_mlistener)
	{	MouseListenerIterator it_m;

		if ((it_m = std::find(mv_mouse_listeners.begin(), mv_mouse_listeners.end(), p_mlistener)) == mv_mouse_listeners.end())
			return false;

		mv_mouse_listeners.erase(it_m);
		return true;
	}

    // Check if listener is registered
    bool InputProcessor::isListenerRegistered(MouseListener * p_mlistener)
    {   if (std::find(mv_mouse_listeners.begin(), mv_mouse_listeners.end(), p_mlistener) == mv_mouse_listeners.end())
			return false;

        return true;
    }

	bool InputProcessor::registerListener(KeyboardListener * p_klistener)
	{
	    if (isListenerRegistered(p_klistener))
	        return false;

		mv_keyboard_listeners.push_back(p_klistener);
		return true;
	}

	// Unregister keyboard listener
	bool InputProcessor::unregisterListener(KeyboardListener * p_klistener)
	{	KeyboardListenerIterator it_m;

		if ((it_m = std::find(mv_keyboard_listeners.begin(), mv_keyboard_listeners.end(), p_klistener))
		    == mv_keyboard_listeners.end())
			return false;

		mv_keyboard_listeners.erase(it_m);
		return true;
	}

    // Check if listener is registered
    bool InputProcessor::isListenerRegistered(KeyboardListener * p_klistener)
    {   if (std::find(mv_keyboard_listeners.begin(), mv_keyboard_listeners.end(), p_klistener)
            == mv_keyboard_listeners.end())
			return false;

        return true;
    }
}
