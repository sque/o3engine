#include "./output.hpp"

namespace o3engine {
namespace RenderLine {

	Output::Output(int width, int height) {
		m_state.width = width;
		m_state.height = height;

		// We need Node pointer to point at correct storage
		mp_state = &m_state;
	}

	Output::~Output() {
	}

	/* TODO: window fix

	 void RenderLineOutput::drawOverlays() {
	 // Disable not needed things
	 glDisable(GL_DEPTH_TEST);
	 glDisable(GL_LIGHTING);

	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 glOrtho(0, 1, 0, 1, -1.0, 1.0);
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();

	 // Render overlays
	 m_overlay_root.renderOverlay(Vector2(m_width, m_height));

	 // Re-enable everything
	 glEnable(GL_LIGHTING);
	 glEnable(GL_DEPTH_TEST);
	 }
	 */

	void Output::onStateAltered() {
		// No need to implement at output node
	}
}
}
