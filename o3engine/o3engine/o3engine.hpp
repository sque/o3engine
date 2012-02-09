#ifndef O3ENGINE_O3ENGINE_HPP_INCLUDED
#define O3ENGINE_O3ENGINE_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./platforms/platform.hpp"
#include "./materialmanager.hpp"
#include "./framelistener.hpp"
#include "./renderer.hpp"
#include "./fontmanager.hpp"
#include "./texturemanager.hpp"
#include "./objectmanager.hpp"

// External
#include <map>
#include <vector>
#include <algorithm>

namespace o3engine
{
    //! [R4] The main object of the O3 engine
    /**
        To use the o3engine library you must create one O3Engine object. This is the
        root object of your framework and the main organizer. After allocating O3Engine
        you must initialize using init() before using any component of the library.
    @par Class Characteristics
        O3Engine is @ref noncopyable_page, @ref noninherit_page and follows the @ref sfn_page
    */
	class O3Engine
	    :protected WindowEventsListener,
	    private TimeSensitive,
        public Singleton<O3Engine>
	{

	friend class Renderer;    			//!< Affiliate with renderers
	friend class FrameListener;         //!< Affiliate with frame listeners
	friend class RenderOutput;          //!< Affiliate with render outputs

	private:
	    // General objects
		unsigned m_frame_counter;       //!< General frame counter, needed for fps counter
		bool m_frame_listeners_paused;	//!< A flag if framelisteners have been paused
		Renderer * mp_renderer;         //!< A pointer to renderer
		list<FrameListener *>::iterator m_fl_it;  //!< Framelistener iterator

		// Managers
		MaterialManager * mp_material_manager;  //!< The material manager
		FontManager * mp_font_manager;          //!< The font manager
		TextureManager * mp_texture_manager;    //!< Texture manager
		ObjectManager * mp_object_manager;      //!< Object manager
		Platform * mp_platform;                 //!< Platform manager

        //! All the activities that must be done on constructor
		void generalConstructor(int c, char** v);

		//! Setup opengl state
		void setupOpenGLState();

		//! @name Manager active render output
		//! @{

		//! Type definition of render output iterator
		typedef vector<RenderOutput *>::iterator RenderOutputIterator;

		//! The array with all active outputs
		vector<RenderOutput *> mv_render_outputs;

        //! Add a new output destination in render queue
		bool activateRenderOutput(RenderOutput * p_output);

		//! Remove an existing ouput destination
		bool deactivateRenderOutput(RenderOutput * p_output);

		//! Get an output by its name
		bool isRenderOutputActivated(RenderOutput * p_output);
        //! @}


        //! @name Events from WindowsEventsListener
        //! @{
        void onWindowResized(int old_width, int old_height, int new_width, int new_height);
        void onWindowRepaint();
		void onWindowIdle();
		//! @}

        //! @name Manage frame listeners
        //! @{

        //! List of all active frame listeners
		list<FrameListener *> mv_framelisteners;

        //! Register a new FrameListener
		bool registerFrameListener(FrameListener * p_fl);

		//! Remove a previous registered FrameListener
		bool unregisterFrameListener(FrameListener * p_fl);

		//! Check if a FrameListener is registered
		bool isFrameListenerRegistered(FrameListener * p_fl);
		//! @}

        // Uncopiable
        O3Engine(const O3Engine&);
        O3Engine& operator=(const O3Engine&);
	public:

		//! Default constructor
		O3Engine();

        //! @name Control general rendering
        //! @{

        //! Initialize engine
        /**
            This function must be called @b BEFORE using
            any component of the library.
        */
		int init(int argc, char ** argv);

		//! Start rendering
		/**
			This function will enter in an endless loop, updating window constantly
			and calling framelisteners between every frame.
		*/
		void startRendering();

        //! Stop rendering
        /**
        @bug This doesn't work on glut platform
        */
		void stopRendering();

		/**
		 * Render a frame
		 */
		void renderOneFrame();

        //! Calculate fps
		Real getFps();

        //! Pause all frame listeners
        inline void pauseFrameListeners()
		{   m_frame_listeners_paused = true;   }

        //! Unpause frame listeners
        inline void unpauseFrameListeners()
        {   m_frame_listeners_paused = false;   }

        //! Check if frame listeners are paused
		bool isFrameListenersPaused() const
		{	return m_frame_listeners_paused;	}

		//! @}

        //! @name Access sub components of the engine
        //! @{

		//! Reference to the material manager singleton
		inline MaterialManager & getMaterialManager(){   return * mp_material_manager;    }

		//! Reference to the texture manager singleton
		inline TextureManager & getTextureManager() { return * mp_texture_manager; }

		//! Reference to the object manager singleton
		inline ObjectManager & getObjectManager() { return * mp_object_manager;    }

		//! Reference to the platform module
		inline Platform & getPlatformManager() {    return * mp_platform;   }

		//! Set current renderer
		inline Renderer * setRenderer(Renderer * p_r)
		{   return mp_renderer = p_r;    }

		//! Reference to current renderer
		inline Renderer & getRenderer() {   return * mp_renderer; }

		//! Pointer to current renderer
		inline Renderer * getRendererPtr() {   return mp_renderer; }

		//! @}
	};
}
#endif
