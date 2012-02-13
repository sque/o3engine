#ifndef O3ENGINE_OFFSCREEN_HPP_INCLUDED
#define O3ENGINE_OFFSCREEN_HPP_INCLUDED

#include "../prereqs.hpp"
#include "./surface.hpp"
#include <vector>

namespace o3engine {

	//! [R4] Abstraction layer to platform off-screen surfaces
	/**
	 * Off-screen surfaces are needed to work with window-less event loops.
	 * @par Class Characteristics
	 * Platform is @ref noncopyable_page, @ref noninherit_page and follows the @ref sfn_page
	 */
	class OffScreen: public Surface {
	public:

		//! Create a new off-screen surface
		/**
		 * @param width The width of surface
		 * @param height The height of surface
		 */
		OffScreen(int width, int height);

		//! Permitting inheritance
		virtual ~OffScreen();

		//! @name Surface virtual methods
		//! @{
		int getHeight() const;

		int getWidth() const;

		void resize(int width, int height);

		virtual void setBackColor(const Color & col);

		virtual const Color & getBackColor() const;
		//! @}

	private:
		class impl;
		impl * pimpl;
	};
}


#endif
