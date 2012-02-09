#include <FreeImage.h>
#include "./o3engine.hpp"

namespace o3engine
{
	//- SINGLETON Initialization
	template<> O3Engine* Singleton<O3Engine>::ms_singleton = 0;

    // Console output log for free image erros
    static void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message)
    {
        printf("\n*** ");
        if(fif != FIF_UNKNOWN)
            printf("%s Format\n", FreeImage_GetFormatFromFIF(fif));
        printf(message);
        printf(" ***\n");
    }

	// General constructor
	void O3Engine::generalConstructor(int c, char** v)
	{
		// Initialize free image
		FreeImage_Initialise();
		FreeImage_SetOutputMessage(FreeImageErrorHandler);

		// Create random numbers
		srand(time(NULL));

		// Initialize variables
		m_frame_listeners_paused = false;
		m_frame_counter = 0;
		mp_renderer = NULL;

		// Allocate managers
		mp_texture_manager = new TextureManager();
		mp_material_manager = new MaterialManager();
		mp_object_manager = new ObjectManager();
        mp_platform = new Platform();
	}

	// Default constructor
	O3Engine::O3Engine()
	{
		generalConstructor(0, NULL);
	}

 	// Attach a framelistener
	bool O3Engine::registerFrameListener(FrameListener * p_fl)
	{   list<FrameListener *>::iterator it;

	    if ((it = find(mv_framelisteners.begin(), mv_framelisteners.end(), p_fl))
            == mv_framelisteners.end())
		{   // Add frame listener to the list
            p_fl->timePassed();
            mv_framelisteners.push_back(p_fl);
            return true;
		}

		return false;
	}

	// Dettach framelistener
	bool O3Engine::unregisterFrameListener(FrameListener * p_fl)
	{   list<FrameListener *>::iterator it;
	    bool removed_current_listener = false;

		if ((it = find(mv_framelisteners.begin(), mv_framelisteners.end(), p_fl))
            != mv_framelisteners.end())
		{   // Correct idle render cycle before removal
		    if (it == m_fl_it)
		    {
		        removed_current_listener = true;
		        m_fl_it ++;
		    }

		    // Remove from list
			mv_framelisteners.erase(it);

            // Execute the next one
			if (removed_current_listener && (m_fl_it != mv_framelisteners.end()))
			    (*m_fl_it)->raiseRenderInterval();

			return true;
		}
		return false;
	}

    bool O3Engine::isFrameListenerRegistered(FrameListener * p_fl)
    {   if (find(mv_framelisteners.begin(), mv_framelisteners.end(), p_fl) == mv_framelisteners.end())
            return false;
        return true;
    }

	Real O3Engine::getFps()
	{
		Real current_fps;
		current_fps = (Real)m_frame_counter / timePassed();
		m_frame_counter = 0;
		return current_fps;
	}

	int O3Engine::init(int argc, char ** argv)
	{
		// Start glut
		glutInit(&argc, argv);

        // Initialize platform (Window, Input, Timers)
		Platform::getSingleton().init();

		// Set us as the window events listeners
        Platform::getSingleton().setWindowEventsListener(this);

		// Start glew
		glewInit();

        // Initialize opengl state
		setupOpenGLState();

		// Create font manager
		mp_font_manager = new FontManager();

		return 0;
	}

	// Start rendering
	void O3Engine::startRendering()
	{
		// Start input capturing
		Platform::getSingleton().getInputProcessor().startCapture();

		// Reset timer counter
		timePassed();

		// Get in main loop
		glutMainLoop();
	}

	void O3Engine::stopRendering()
	{
		// Setup Callback functions
		//glutLeaveMainLoop();
	}

    void O3Engine::onWindowResized(int old_width, int old_height, int new_width, int new_height)
	{
    	RenderOutputIterator it_output;

		// Call viewport's reshaped function
		for(it_output = mv_render_outputs.begin();it_output != mv_render_outputs.end();it_output++)
			(*it_output)->onWindowResize(new_width, new_height);

		// Call Renderer
		if (mp_renderer != NULL)
			mp_renderer->reshape(new_width, new_height);

		// Redraw
		glutPostRedisplay();
	}

	// Call back function for idle
	void O3Engine::onWindowIdle()
	{
		FrameListener * p_fl;

		if (m_frame_listeners_paused)
			return;

		// Call all frame listeners
		for(m_fl_it = mv_framelisteners.begin();m_fl_it != mv_framelisteners.end();m_fl_it++)
		{   p_fl = *m_fl_it;
			p_fl->raiseRenderInterval();
		}

		glutPostRedisplay();
	}

	/**
	 * Render a frame
	 */
	void O3Engine::renderOneFrame()
	{
		// Call renderer
		if (mp_renderer)
		   mp_renderer->render();

		glFlush();

		// Swap Buffers
		glutSwapBuffers();

		// Calculate fps
		m_frame_counter++;
	}

	void O3Engine::onWindowRepaint()
	{
		renderOneFrame();
	}

	// Setup opengl state
	void O3Engine::setupOpenGLState()
	{
		// Set up OpenGL parameters
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

    // Add a new output destination in render queue
    bool O3Engine::activateRenderOutput(RenderOutput * p_output)
    {   if (isRenderOutputActivated(p_output))
            return false;

        mv_render_outputs.push_back(p_output);

        // On activation we must raise window resize event to reinitialize if needed.
        p_output->onWindowResize(mp_platform->getWindowWidth(), mp_platform->getWindowHeight());

        return true;
    }

    // Remove an existing ouput destination
    bool O3Engine::deactivateRenderOutput(RenderOutput * p_output)
    {   RenderOutputIterator out_it;

        if ((out_it = find(mv_render_outputs.begin(), mv_render_outputs.end() ,p_output))
             == mv_render_outputs.end())
             return false;
        mv_render_outputs.erase(out_it);
        return true;
    }

    // Get an output by its name
    bool O3Engine::isRenderOutputActivated(RenderOutput * p_output)
    {   if (find(mv_render_outputs.begin(), mv_render_outputs.end() ,p_output)
             == mv_render_outputs.end())
            return false;
        return true;
    }
}
