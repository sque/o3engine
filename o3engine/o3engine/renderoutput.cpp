#include "./renderoutput.hpp"
#include "./o3engine.hpp"

namespace o3engine {
	RenderOutput::RenderOutput(int width, int height):
		mp_rlink(NULL){
		setSize(width, height);
	}

	RenderOutput::~RenderOutput() {
		// Deactivate before destroying
		//disableRendering();
	}

	bool RenderOutput::enableRendering() {
		return O3Engine::getSingleton().activateRenderOutput(this);
	}

	bool RenderOutput::disableRendering() {
		return O3Engine::getSingleton().deactivateRenderOutput(this);
	}

	bool RenderOutput::isRenderingEnabled() {
		return O3Engine::getSingleton().isRenderOutputActivated(this);
	}

	void RenderOutput::setSize(int width, int height) {
		m_width = width;
		m_height = height;
	}


	/* TODO: window fix

	void RenderOutput::drawOverlays() {
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
}
