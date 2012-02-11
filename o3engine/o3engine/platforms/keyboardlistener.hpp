#ifndef O3ENGINE_KEYBOARDLISTENER_HPP_INCLUDED
#define O3ENGINE_KEYBOARDLISTENER_HPP_INCLUDED

namespace o3engine {
	//! Keyboard virtual keys enumeration
	enum E_KB_VIRTUALKEYS {
		KB_VTKEY_ESC = 0,
		KB_VTKEY_FN1,
		KB_VTKEY_FN2,
		KB_VTKEY_FN3,
		KB_VTKEY_FN4,
		KB_VTKEY_FN5,
		KB_VTKEY_FN6,
		KB_VTKEY_FN7,
		KB_VTKEY_FN8,
		KB_VTKEY_FN9,
		KB_VTKEY_FN10,
		KB_VTKEY_FN11,
		KB_VTKEY_FN12,
		KB_VTKEY_TAB,
		KB_VTKEY_BACKSPACE,
		KB_VTKEY_SPACE,
		KB_VTKEY_ENTER,
		KB_VTKEY_LSHIFT,
		KB_VTKEY_RSHIFT,
		KB_VTKEY_LALT,
		KB_VTKEY_RALT,
		KB_VTKEY_LCTRL,
		KB_VTKEY_RCTRL,
		KB_VTKEY_UP,
		KB_VTKEY_DOWN,
		KB_VTKEY_LEFT,
		KB_VTKEY_RIGHT,
		KB_VTKEY_HOME,
		KB_VTKEY_PGUP,
		KB_VTKEY_PGDOWN,
		KB_VTKEY_END,
		KB_VTKEY_MINUS,
		KB_VTKEY_PLUS,
		KB_VTKEY_0,
		KB_VTKEY_1,
		KB_VTKEY_2,
		KB_VTKEY_3,
		KB_VTKEY_4,
		KB_VTKEY_5,
		KB_VTKEY_6,
		KB_VTKEY_7,
		KB_VTKEY_8,
		KB_VTKEY_9,
		KB_VTKEY_A,
		KB_VTKEY_B,
		KB_VTKEY_C,
		KB_VTKEY_D,
		KB_VTKEY_E,
		KB_VTKEY_F,
		KB_VTKEY_G,
		KB_VTKEY_H,
		KB_VTKEY_I,
		KB_VTKEY_J,
		KB_VTKEY_K,
		KB_VTKEY_L,
		KB_VTKEY_M,
		KB_VTKEY_N,
		KB_VTKEY_O,
		KB_VTKEY_P,
		KB_VTKEY_Q,
		KB_VTKEY_R,
		KB_VTKEY_S,
		KB_VTKEY_T,
		KB_VTKEY_U,
		KB_VTKEY_V,
		KB_VTKEY_W,
		KB_VTKEY_X,
		KB_VTKEY_Y,
		KB_VTKEY_Z,
		KB_VTKEY_UNKNOWN, // Unknown key
		KB_VTKEY_MAX
	// The bottom!
	};

	//! Keyboard virtual key states
	enum E_KB_VTKEY_STATES {
		KB_KEY_UP = 0, // Key is up
		KB_KEY_DOWN = 1
	// Key is down
	};

	//! [R4] A keyboard events listener interface
	/**
	 * @par Class Characteristics
	 * KeyboardListener is @ref copyable_page, @ref inherit_page and follows the @ref sfn_page
	 */
	class KeyboardListener {
	public:
		virtual ~KeyboardListener();

		//! @name Events that can be implemented by derived classes
		//! @{

		//! Raised when a keyboard key is pressed
		inline virtual void onKeyboardButtonPressed(E_KB_VIRTUALKEYS vt_key) {
		}
		;

		//! Raised when a keyboard key is released
		inline virtual void onKeyboardButtonReleased(E_KB_VIRTUALKEYS vt_key) {
		}
		;

		//! Raised when a keyboard key that was released produced a character insertation
		inline virtual void onKeyboardCharInsert(unsigned char ch) {
		}
		;

		//! @}
	};
}

#endif
