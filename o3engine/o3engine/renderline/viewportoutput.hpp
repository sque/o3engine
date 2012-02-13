#ifndef O3ENGINE_VIEWPORTRENDEROUTPUT_HPP_INCLUDED
#define O3ENGINE_VIEWPORTRENDEROUTPUT_HPP_INCLUDED

#include "./../prereqs.hpp"
#include "./output.hpp"
#include "./../platform/window.hpp"

namespace o3engine {
namespace RenderLine{

	//! [R4] An output to a viewport of a window
	/**
	 * Implementation of RenderOutput target on a window's viewport.
	 * @par Class Characteristics
	 * ViewportRenderOutput is @ref noncopyable_page, @ref inherit_page and follows the @ref sfn_page
	 */
	class ViewportOutput: public Output, SurfaceListener {
	private:
		// Non copyable object
		ViewportOutput(const ViewportOutput &);
		ViewportOutput& operator=(const ViewportOutput &);

	protected:

		//! Bottom offset of viewport
		int m_bottom_offset;

		//! Left offset of viewport
		int m_left_offset;

		//! Window handler
		Window & m_window;

	public:

		//! Construct and initialize with desired parameters
		/**
		 * @param wnd The window that this viewport belongs at.
		 * @param width The width of the RenderOutput object.
		 * @param height The height of the RenderOutput object.
		 * @param left The left offset of viewport on the window.
		 * @param bottom The bottom offset of viewport on the window.
		 */
		ViewportOutput(Window & wnd, int width, int height, int left, int bottom);

		//! Destructor
		virtual ~ViewportOutput();

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

		virtual void render();

		//! @name Events from SurfaceListener
		//! @{

		virtual void onSurfaceResized(int old_width, int old_height, int new_width, int new_height);

		//! Raised when window must be drawn
		inline virtual void onSurfaceRepaint(){
			render();
		}

		//! @}
	};
}
}
#endif
