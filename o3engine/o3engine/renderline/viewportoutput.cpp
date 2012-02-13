#include "./viewportoutput.hpp"

namespace o3engine {
namespace RenderLine {
	// Constructor with parameters of viewport
	ViewportOutput::ViewportOutput(Window & wnd, int width, int height, int left, int bottom):
			RenderLine::Output(width, height),
			m_window(wnd){
		m_bottom_offset = bottom;
		m_left_offset = left;
		m_window.attachSurfaceListener(*this);
	}

	ViewportOutput::~ViewportOutput() {
	}

	void ViewportOutput::render(){
		::glViewport(m_left_offset, m_bottom_offset, getWidth(), getHeight());
		renderNext();
	}

	void ViewportOutput::onSurfaceResized(int old_width, int old_height, int new_width, int new_height){
		// By default make viewport full screen
		m_state.width = new_width;
		m_state.height = new_height;
		propagateStateAltered();
	}
}
}
