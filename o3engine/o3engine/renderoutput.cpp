#include "./renderoutput.hpp"
#include "./o3engine.hpp"

namespace o3engine
{
	RenderOutput::RenderOutput(int width, int height)
		:m_fade_color(1,1,1,0),
		m_overlay_root(NULL, Vector2(0,0), Vector2(1,1), Overlay::COORD_TYPE_UNIFORM)
	{
		mp_input_camera = NULL;
		setSize(width, height);
	}

	RenderOutput::~RenderOutput()
	{
	    // Deactivate before destroying
	    disableRendering();
	}

	bool RenderOutput::enableRendering()
	{   return O3Engine::getSingleton().activateRenderOutput(this);
	}

	bool RenderOutput::disableRendering()
	{   return O3Engine::getSingleton().deactivateRenderOutput(this);
	}

	bool RenderOutput::isRenderingEnabled()
	{   return O3Engine::getSingleton().isRenderOutputActivated(this);    }

	void RenderOutput::setSize(int width, int height)
	{
		m_width = width;
		m_height = height;
		m_overlay_root.renderOutputResized(m_width, m_height);
	}

	void RenderOutput::drawOverlays()
	{
		// Disable not needed things
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho (0, 1, 0, 1, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Add fade color
		if (m_fade_color.alpha != 0 )
		{
			glColor4(m_fade_color);
			glBegin(GL_POLYGON);
				glVertex2f(0, 0);
				glVertex2f(0, 1);
				glVertex2f(1, 1);
				glVertex2f(1, 0);
			glEnd();
		}

		// Render overlays
		m_overlay_root.renderOverlay(Vector2(m_width, m_height));

		// Renable everything
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	}
}
