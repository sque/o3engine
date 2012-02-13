#ifndef O3ENGINE_INPUTPROCESSOR_HPP_INCLUDED
#define O3ENGINE_INPUTPROCESSOR_HPP_INCLUDED

#include "../prereqs.hpp"
#include "./mouselistener.hpp"
#include "./keyboardlistener.hpp"
#include <vector>

namespace o3engine {

	//! [R4] Engine for monitor and inform about mouse and keyboard events on a window
	/**
	 * InputProcessor is used by Platform for input back-end, there is no need
	 * to create an object, it is done automatically by Platform at the initialization stage.
	 * To listen for events use KeyboardListener or MouseListener.
	 * @par Class Characteristics
	 *  InputProcessor is @ref singleton_page, @ref noncopyable_page, @ref noninherit_page and follows the @ref sfn_page
	 */
	class InputProcessor{
	private:
		// Pimp idiom
		class impl;
		impl * pimpl;

		//! Window reference
		const Window & m_wnd;

		// Uncopiable
		InputProcessor(const InputProcessor &);
		InputProcessor & operator=(const InputProcessor &);

		//! Mouse Listener type
		typedef vector<MouseListener *> mouse_listeners_type;

		//! Mouse listeners vector
		mouse_listeners_type mv_mouse_listeners;

		//! Keyboard listener iterator
		typedef vector<KeyboardListener *> keyboard_listeners_type;

		//! Keyboard listeners vector
		keyboard_listeners_type mv_keyboard_listeners;

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
		InputProcessor(const Window & wnd);

		//! Destructor
		~InputProcessor() {
		}

		//! Get the associated Window
		inline const Window & getAssociatedWindow() const {
			return m_wnd;
		}

		//! Start capturing events
		void startCapturing();

		//! Stop capturing events;
		void stopCapturing();

		//! Check if a keyboard key is pressed
		bool isVTKeyPressed(int vtk) {
			return mv_key_state[vtk];
		}

		//! @name Keyboard listeners management
		//! @{

		//! Attach keyboard listener
		bool attachKeyboardListener(KeyboardListener & listener);

		//! Detach keyboard listener
		bool detachKeyboardListener(KeyboardListener & listener);

		//! Check if keyboard listener is attached
		bool isKeyboardListenerAttached(KeyboardListener & listener);
		//! @}

		//! @name Mouse listeners management
		//! @{

		//! Register a mouse listener
		bool attachMouseListener(MouseListener & listener);

		//! Unregister a mouse listener
		bool detachMouseListener(MouseListener & listener);

		//! Check if listener is registered
		bool isMouseListenerAttached(MouseListener & listener);
		//! @}
	};
}
#endif
