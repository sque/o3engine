#ifndef O3ENGINE_SURFACELISTENER_HPP_INCLUDED
#define O3ENGINE_SURFACELISTENER_HPP_INCLUDED

#include "../prereqs.hpp"

namespace o3engine {

	//! [R4] Base class for object that need to get informed about surface events
	/**
	 * @par Class Characteristics
	 * SurfaceListener is @ref copyable_page, @ref inherit_page and follows the @ref sfn_page
	 */
	class SurfaceListener {
	public:
		//! Default virtual destructor
		virtual ~SurfaceListener() {
		}

		//! @name Events that can be implemented by derived classes
		//! @{

		//! Raised when the current surface gets resized
		/**
		 * @param old_width The previous width of window before reshaping.
		 * @param old_height The previous height of window before reshaping.
		 * @param new_width The new width of window after reshaping.
		 * @param new_height The new height of window after reshaping.
		 */
		virtual void onSurfaceResized(int old_width, int old_height, int new_width,
				int new_height) = 0;

		//! Raised when surface is asked to be painted
		virtual void onSurfaceRepaint() = 0;

		//! @}
	};

}
#endif
