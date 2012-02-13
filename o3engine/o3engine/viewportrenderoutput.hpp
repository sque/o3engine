#ifndef O3ENGINE_VIEWPORTRENDEROUTPUT_HPP_INCLUDED
#define O3ENGINE_VIEWPORTRENDEROUTPUT_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./renderoutput.hpp"
#include "./platform/window.hpp"

namespace o3engine {

	//! [R4] An output to a viewport of a window
	/**
	 * Implementation of RenderOutput target on a window's viewport.
	 * @par Class Characteristics
	 * ViewportRenderOutput is @ref noncopyable_page, @ref inherit_page and follows the @ref sfn_page
	 */
	class ViewportRenderOutput: public RenderOutput, SurfaceListener {
	private:
		// Non copyable object
		ViewportRenderOutput(const ViewportRenderOutput &);
		ViewportRenderOutput& operator=(const ViewportRenderOutput &);

	protected:
		int m_bottom_offset;	//!< Bottom offset of viewport
		int m_left_offset;		//!< Left offset of viewport
		Window & m_window;		//!< Window handler

	public:

		//! Construct and initialize with desired parameters
		/**
		 * @param wnd The window that this viewport is binded at.
		 * @param width The width of the RenderOutput object.
		 * @param height The height of the RenderOutput object.
		 * @param left The left offset of viewport on the window.
		 * @param bottom The bottom offset of viewport on the window.
		 */
		ViewportRenderOutput(Window & wnd, int width, int height, int left, int bottom);

		//! Destructor
		virtual ~ViewportRenderOutput();

		//! Get bottom margin of viewport on the window
		inline void setBottomOffset(int bottom_offset) {
			m_bottom_offset = bottom_offset;
		}

		//! Set left margin of viewport on the window
		inline void setLeftOffset(int left_offset) {
			m_left_offset = left_offset;
		}

		//! Get bottom margin of viewport on the window
		inline int getBottomOffset() const {
			return m_bottom_offset;
		}

		//! Get left margin of viewport on the window
		inline int getLeftOffset() const {
			return m_left_offset;
		}

		//! @name Events from RenderOutput
		//! @{
		inline virtual void render() {
			::glViewport(m_left_offset, m_bottom_offset, m_width, m_height);
			renderPipeline();
		}


		virtual void onSurfaceResized(int old_width, int old_height, int new_width, int new_height){

		}

		virtual void onOutputResize(int new_w, int new_h){}

		//! Raised when window must be drawn
		virtual void onSurfaceRepaint(){
			render();
		}

		//! @}
	};
}
#endif
