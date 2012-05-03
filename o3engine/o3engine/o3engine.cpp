#include <FreeImage.h>
#include "./o3engine.hpp"
#include <stdexcept>

namespace o3engine {

	//- SINGLETON Initialization
	template<> O3Engine* Singleton<O3Engine>::ms_singleton = 0;

	// Console output log for free image errors
	static void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message) {
		printf("\n*** ");
		if (fif != FIF_UNKNOWN)
			printf("%s Format\n", FreeImage_GetFormatFromFIF(fif));
		printf("%s", message);
		printf(" ***\n");
	}

	// General constructor
	void O3Engine::generalConstructor(int c, char** v) {
		// Initialize free image
		FreeImage_Initialise();
		FreeImage_SetOutputMessage(FreeImageErrorHandler);

		// Create random numbers
		srand(time(NULL));

		// Initialize variables
		m_frame_listeners_paused = false;
		m_frame_counter = 0;

		// Allocate managers
		mp_texture_manager = new TextureManager();
		mp_program_manager = new ProgramManager();
		mp_material_manager = new MaterialManager();
		mp_object_manager = new ObjectManager();
		mp_platform = new Platform();
	}

	// Default constructor
	O3Engine::O3Engine() {
		generalConstructor(0, NULL);
	}

	// Attach a framelistener
	bool O3Engine::attachFrameListener(FrameListener & framelistener) {
		framelisteners_type::iterator it;

		if ((it = find(mv_framelisteners.begin(), mv_framelisteners.end(), &framelistener))
				== mv_framelisteners.end()) { // Add frame listener to the list
			framelistener.timePassed();
			mv_framelisteners.push_back(&framelistener);
			return true;
		}

		return false;
	}

	// Detach framelistener
	bool O3Engine::detachFrameListener(FrameListener & framelistener) {
		framelisteners_type::iterator it;
		bool removed_current_listener = false;

		if ((it = find(mv_framelisteners.begin(), mv_framelisteners.end(), &framelistener))
				!= mv_framelisteners.end()) { // Correct idle render cycle before removal
			if (it == m_fl_it) {
				removed_current_listener = true;
				m_fl_it++;
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

	bool O3Engine::isFrameListenerAttached(FrameListener & framelistener) {
		if (find(mv_framelisteners.begin(), mv_framelisteners.end(), &framelistener)
				== mv_framelisteners.end())
			return false;
		return true;
	}

	Real O3Engine::getFps() {
		Real current_fps;
		current_fps = (Real) m_frame_counter / timePassed();
		m_frame_counter = 0;
		return current_fps;
	}

	int O3Engine::initialize(int argc, char ** argv, std::initializer_list<std::string> search_dirs ) {

		// Prepare search directories
		if (search_dirs.size() > 0) {
			for(auto sdir : search_dirs) {
				mp_program_manager->addSearchDirectory(sdir);
			}
		} else {
			mp_program_manager->addSearchDirectory("resources/shaders");
		}

		// Initialize platform (Window, Input, Timers)
		Platform::getSingleton().initialize(argc, argv);

		// Initialize opengl state
		setupOpenGLState();

		// Create font manager
		mp_font_manager = new FontManager();

		return 0;
	}

	// Start rendering
	void O3Engine::startRendering() {
		// Reset timer counter
		timePassed();

		// Get in main loop
		mp_platform->startEventLoop(*this);
	}

	void O3Engine::stopRendering() {
		// Setup Callback functions
		// TODO: glutLeaveMainLoop();
	}

	void O3Engine::onLoopIdle() {
		FrameListener * p_fl;

		if (m_frame_listeners_paused)
			return;

		// Call all frame listeners
		for (m_fl_it = mv_framelisteners.begin();
				m_fl_it != mv_framelisteners.end(); m_fl_it++) {
			p_fl = *m_fl_it;
			p_fl->raiseRenderInterval();
		}

		// Calculate FPS
		m_frame_counter++;
	}

	// Setup opengl state
	void O3Engine::setupOpenGLState() {
		// Set up OpenGL parameters
		ogl::context::create();
		ogl::current_ctx().depth_test().enable();
	}
}
