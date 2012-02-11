#ifndef O3ENGINE_VIEWPORTRENDEROUTPUT_HPP_INCLUDED
#define O3ENGINE_VIEWPORTRENDEROUTPUT_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./renderoutput.hpp"
#include "./platforms/mouselistener.hpp"

namespace o3engine {

	//! [R4] An output to a viewport of a window
	/**
	 * Implementation of RenderOutput target on a window's viewport.
	 * @par Class Characteristics
	 * ViewportRenderOutput is @ref noncopyable_page, @ref inherit_page and follows the @ref sfn_page
	 */
	class ViewportRenderOutput: public RenderOutput, public MouseListener {
	private:
		// Non copyable object
		ViewportRenderOutput(const ViewportRenderOutput &);
		ViewportRenderOutput& operator=(const ViewportRenderOutput &);

	protected:
		int m_bottom_offset; 	//!< Bottom offset of viewport
		int m_left_offset; 		//!< Left offset of viewport

		virtual void onInputCameraChanged();
	public:

		//! Construct and initialize with desired parameters
		/**
		 * @param width The width of the RenderOutput object
		 * @param height The height of the RenderOutput object
		 * @param left The left offset of viewport on the window
		 * @param bottom The bottom offset of viewport on the window
		 */
		ViewportRenderOutput(int width, int height, int left, int bottom);

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
		inline virtual void onPreRender() {
			glViewport(m_left_offset, m_bottom_offset, m_width, m_height);
		}
		inline virtual void onPostRender() {
		}
		virtual void onWindowResize(int new_width, int new_height);
		//! @}

		//! @name Events from MouseListener
		//! @{
		virtual void onMouseMove(const MouseEvent & e);
		virtual void onMouseButtonPressed(const MouseEvent & e);
		virtual void onMouseButtonReleased(const MouseEvent & e);
		//! @}
	};
}
#endif
