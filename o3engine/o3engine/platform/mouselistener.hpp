#ifndef O3ENGINE_MOUSELISTENER_HPP_INCLUDED
#define O3ENGINE_MOUSELISTENER_HPP_INCLUDED

#include "../prereqs.hpp"

namespace o3engine {
	//! Mouse button states
	enum E_MS_BUTTON_STATES {
		MS_BUTTON_UP = 32, MS_BUTTON_DOWN = 64
	};

	//! Mouse button enumeration
	enum E_MS_BUTTONS {
		MS_BUTTON_NONE = 0, //! A pseudo button corresponding to none
		MS_BUTTON_LEFT, //! Left button of mouse
		MS_BUTTON_MIDDLE, //! Middle or wheel down button
		MS_BUTTON_RIGHT, //! Right button
		MS_BUTTON_WHEELUP, //! Wheel scrolled up
		MS_BUTTON_WHEELDOWN, //! Wheel scrolled down
		MS_BUTTON_MAX
	//! A pseudo button corresponding to the maximum enumeration
	};

	//! [R4] Description of current mouse state
	/**
	 * An object giving detailed description of the current mouse state.
	 * @par Class Characteristics
	 * MouseState is @ref copyable_page, @ref noninherit_page and follows the @ref sfn_page
	 */
	class MouseState {
	public:
		//! Current position of mouse cursor on Axis X
		int m_pos_x;
		//! Current position of mouse cursor on Axis Y
		int m_pos_y;

		//! Current state of all buttons
		E_MS_BUTTON_STATES m_button_state[MS_BUTTON_MAX];

		//! A function to check if there is at least one button pressed
		inline bool isAnyButtonDown() const {
			for (int i = 0; i < MS_BUTTON_MAX; i++)
				if (m_button_state[i] == MS_BUTTON_DOWN)
					return true;
			return false;
		}

		//! Default constructor (Not initialized)
		/**
		 * @remarks Default constructor does not initialize object.
		 */
		inline MouseState() {
		}

		//! Copy constructor
		inline MouseState(const MouseState & r) :
				m_pos_x(r.m_pos_x), m_pos_y(r.m_pos_y) {
			for (long i = 0; i < MS_BUTTON_MAX; i++)
				m_button_state[i] = r.m_button_state[i];
		}

		//! Assignment operator
		inline MouseState & operator=(const MouseState & r) {
			m_pos_x = r.m_pos_x;
			m_pos_y = r.m_pos_y;
			for (long i = 0; i < MS_BUTTON_MAX; i++)
				m_button_state[i] = r.m_button_state[i];
			return *this;
		}
	};

	//! [R4] Description of mouse event
	/**
	 * An object holding detailed description about
	 * the mouse event. It also holds a reference
	 * to the mouse state.
	 * @par Class Characteristics
	 * MouseEvent is @ref copyable_page, @ref noninherit_page and follows the @ref sfn_page
	 */
	class MouseEvent {
	public:
		//! Relative movement since last event on Axis x
		int m_rel_x;
		//! Relative movement since last event on Axis Y
		int m_rel_y;

		//! Button that triggered the event (if any)
		E_MS_BUTTONS m_trigger_button;

		//! Constant reference to current mouse state
		const MouseState & ms_mouse_state;

		//! Default constructor
		/**
		 * Default constructor saves mouse_state reference internally.
		 * @remarks Default constructor does not initialize object.
		 */
		inline MouseEvent(const MouseState & mouse_state) :
				ms_mouse_state(mouse_state) {
		}

		//! Construct and initialize
		inline MouseEvent(int rel_x, int rel_y, E_MS_BUTTONS trigger_button,
				const MouseState & mouse_state) :
				m_rel_x(rel_x), m_rel_y(rel_y), m_trigger_button(trigger_button), ms_mouse_state(
						mouse_state) {
		}

		//! Copy constructor
		inline MouseEvent(const MouseEvent & r) :
				m_rel_x(r.m_rel_x), m_rel_y(r.m_rel_y), m_trigger_button(
						r.m_trigger_button), ms_mouse_state(r.ms_mouse_state) {
		}

		//! Assignment operator
		inline MouseEvent & operator=(const MouseEvent & r) {
			m_rel_x = r.m_rel_x;
			m_rel_y = r.m_rel_y;
			m_trigger_button = r.m_trigger_button;
			return *this;
		}
	};

	//! [R4] A mouse events listener interface
	/**
	 * @par Class Characteristics
	 * MouseListener is @ref copyable_page, @ref inherit_page and follows the @ref sfn_page
	 */
	class MouseListener {
	public:
		//! Virtual destructor
		virtual ~MouseListener();

		//! @name Events that can be implemented by derived classes
		//! @{

		//! Raised when there is an actual mouse movement
		virtual void onMouseMove(const MouseEvent & e) {
		}

		//! Raised when a button got pressed
		virtual void onMouseButtonPressed(const MouseEvent & e) {
		}

		//! Raised when a button was released
		virtual void onMouseButtonReleased(const MouseEvent & e) {
		}
		//! @}
	};
}
#endif
