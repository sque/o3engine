#include "./viewportrenderoutput.hpp"
#include "./camera.hpp"

namespace o3engine {

	// Constructor with parameters of viewport
	ViewportRenderOutput::ViewportRenderOutput(Window & wnd, int width, int height, int left, int bottom):
			RenderOutput(width, height),
			m_window(wnd){
		m_bottom_offset = bottom;
		m_left_offset = left;
		m_window.attachSurfaceListener(*this);
	}

	ViewportRenderOutput::~ViewportRenderOutput() {
	}


/*	void ViewportRenderOutput::onWindowResize(int new_width, int new_height) {
		// By default make viewport full screen
		setSize(new_width, new_height);

		// Change camera's aspect ratio
		// TODO: aspect camera mp_input_camera->setAspectRatio(aspectRatio());
	}*/

	/* TODO: aspect camera
	void ViewportRenderOutput::onInputCameraChanged() {
		// Change camera's aspect ratio
		mp_input_camera->setAspectRatio(aspectRatio());
	}
	*/
}
