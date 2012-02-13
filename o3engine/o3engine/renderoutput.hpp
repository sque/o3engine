#ifndef O3ENGINE_RENDEROUTPUT_HPP_INCLUDED
#define O3ENGINE_RENDEROUTPUT_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./overlay.hpp"
#include "./renderlink.hpp"

namespace o3engine {
	//! [R4] Class for defining a render output destination
	/**
	 * This the abstract definition of the output of 3d render queue. A standard
	 * render output has a size and supports overlays on it.
	 * @par Class Characteristics
	 * 	RendereOutput is @ref noncopyable_page, @ref inherit_page and follows the @ref sfn_page
	 */
	class RenderOutput {
	private:
		// Uncopiable
		RenderOutput(const RenderOutput &);
		RenderOutput & operator=(const RenderOutput &);

	protected:
		int m_width;			//!< Width of output
		int m_height;			//!< Height of output
		RenderLink * mp_rlink;	//! Next render link

	public:

		//! Default constructor (@b NOT activated)
		/**
		 * @remarks By default RenderOutput is not activated and you
		 * must enableRendering() to order engine to use this output.
		 */
		RenderOutput(int width, int height);

		//! Destructor
		virtual ~RenderOutput();

		//! Attach render link to this output
		inline void attachRenderLink(RenderLink & link) {
			mp_rlink = &link;
		}

		//! Detach the render link
		inline void detachRenderLink() {
			mp_rlink = NULL;
		}

		//! Get the current attached render link
		RenderLink * getAttachedRenderLink() {
			return mp_rlink;
		}

		inline void renderPipeline() {
			if (mp_rlink)
				mp_rlink->render();
		}

		//! @name Control this device status
		//! @{

		//! Activate this device
		/**
		 * @return
		 *  - @b true If the device got activated successfully
		 *  - @b false If the device was already activated
		 *  .
		 */
		bool enableRendering();

		//! Disable this device
		/**
		 * @return
		 *  - @b true If the device was previously activated
		 *  - @b false If the device was not activated at all.
		 *  .
		 */
		bool disableRendering();

		//! Check if device is activated
		bool isRenderingEnabled();
		//! @}

		//! @name Access attributes
		//! @{

		//! Get the current width of the output
		inline int getWidth() const {
			return m_width;
		}

		//! Get the current height of the output
		inline int getHeight() const {
			return m_height;
		}

		//! Change the current width
		inline void setWidth(int width) {
			setSize(width, m_height);
		}

		//! Change the current height
		inline void setHeight(int height) {
			setSize(m_width, height);
		}

		//! Change the size of output (width and height)
		void setSize(int width, int height);

		//! Get the current size
		inline Vector2 getSize() {
			return Vector2(m_width, m_height);
		}

		//! @}

		//! Calculate and return the aspect ratio of this output
		inline GLfloat aspectRatio() const {
			return (GLfloat) ((double) m_width / (double) m_height);
		}

		//! @name Events that must be handled by derived classes
		//! @{

		//! Raised before starting rendering on this output
		virtual void render() = 0;

		//! Raised when output window is resized
		virtual void onOutputResize(int new_width, int new_height) = 0;

		//! @}
	};
}
#endif
