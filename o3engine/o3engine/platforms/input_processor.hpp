#ifndef O3ENGINE_INPUTPROCESSOR_HPP_INCLUDED
#define O3ENGINE_INPUTPROCESSOR_HPP_INCLUDED

#include "../prereqs.hpp"
#include "./mouse_listener.hpp"
#include "./keyboard_listener.hpp"
#include <vector>

namespace o3engine
{


	//! [R4] Engine for monitor and inform about mouse and keyboard events
	/**
        InputProcessor is used by Platform for input back-end, there is no need
        to create an object, it is done automatically by Platform at the initialization stage.
        To listen for events use KeyboardListener or MouseListener.
    @par Class Characteristics
        InputProcessor is @ref singleton_page, @ref noncopyable_page, @ref noninherit_page and follows the @ref sfn_page
    */
	class InputProcessor: public Singleton<InputProcessor>
	{
    friend class MouseListener;
    friend class KeyboardListener;
    friend class impl;
    private:
        // Pimp idiom
        class impl;
        impl * pimpl;

        // Uncopiable
        InputProcessor(const InputProcessor &);
        InputProcessor & operator=(const InputProcessor &);

        //! @name Mouse listeners management
        //! @{

        //! Mouse Listener iterator
		typedef vector<MouseListener *>::iterator MouseListenerIterator;

		//! Mouse listeners vector
		vector<MouseListener *> mv_mouse_listeners;

        //! Register a mouse listener
		bool registerListener(MouseListener * p_mlistener);

		//! Unregister a mouse listener
		bool unregisterListener(MouseListener * p_mlistener);

		//! Check if listener is registered
		bool isListenerRegistered(MouseListener * p_mlistener);
        //! @}

        //! @name Keyboard listeners management
        //! @{

		//! Keyboard listener iterator
		typedef vector<KeyboardListener *>::iterator KeyboardListenerIterator;

		//! Keyboard listeners vector
		vector<KeyboardListener *> mv_keyboard_listeners;

		//! Register keyboard listener
		bool registerListener(KeyboardListener * p_klistener);

		//! Unregister keyboard listener
		bool unregisterListener(KeyboardListener * p_klistener);

        //! Check if listener is registered
		bool isListenerRegistered(KeyboardListener * p_mlistener);
        //! @}

		//! Pointer to current mouse state
		MouseState m_mouse_state;

		//! A MouseEvent object to avoid create/delete for each event
		MouseEvent m_mouse_event;

		//! The array with the status of all keyboard keys
		bool mv_key_state[KB_VTKEY_MAX];

		//! Actions to take when we have new mouse coords (called by input implementor)
		void raiseMouseMoved(int new_x, int new_y);

		//! Actions to take when a mouse button is released (called by input implementor)
		void raiseMouseButtonReleased(E_MS_BUTTONS trig_button);

		//! Actions to take when a mouse button is pressed (called by input implementor)
		void raiseMouseButtonPressed(E_MS_BUTTONS trig_button);

		//! Actions to take when we have keyboard button release (called by input implementor)
		void raiseKeyboardReleased(E_KB_VIRTUALKEYS vtkey);

		//! Actions to take when we have keyboard button pressed (called by input implementor)
		void raiseKeyboardPressed(E_KB_VIRTUALKEYS vtkey);

		//! Actions to take when we a character is inserted after a button release (called by input implementor)
		void raiseKeyboardCharInsert(unsigned char ch);

	public:
		//! Constructor
		InputProcessor();

		//! Destructor
		~InputProcessor(){}

		//! Start capturing events
		void startCapture();

        //! Check if a keyboard key is pressed
		bool isVTKeyPressed(int vtk)
		{   return mv_key_state[vtk];    }
	};
}
#endif
