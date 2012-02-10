#ifndef O3ENGINE_WINDOWLISTENER_HPP_INCLUDED
#define O3ENGINE_WINDOWLISTENER_HPP_INCLUDED

#include "../prereqs.hpp"

namespace o3engine {

//! [R4] Base class for object that need to get informed about windows events
	/**
	 * @remarks Currently only one window listener is supported and this is reserved
	 * for internal reasons, so this function is useless at the moment for the user
	 * of the library.
	 * @par Class Characteristics
	 * WindowEventsListener is @ref copyable_page, @ref inherit_page and follows the @ref sfn_page
	 */
	class WindowEventsListener {
	public:
		//! Default virtual destructor
		virtual ~WindowEventsListener() {
		}

		//! @name Events that can be implemented by derived classes
		//! @{

		//! Raised when the current window gets resized
		/**
		 * @param old_width The previous width of window before reshaping.
		 * @param old_height The previous height of window before reshaping.
		 * @param new_width The new width of window after reshaping.
		 * @param new_height The new height of window after reshaping.
		 */
		virtual void onWindowResized(int old_width, int old_height, int new_width,
				int new_height) = 0;

		//! Raised when window must be drawn
		virtual void onWindowRepaint() = 0;

		//! @}
	};

}
#endif /* O3ENGINE_WINDOWLISTENER_HPP_INCLUDED */
