#ifndef EXAMPLEAPPLICATION_H_INCLUDED
#define EXAMPLEAPPLICATION_H_INCLUDED

#include "./o3engine.hpp"
#include "./simplerenderer.hpp"
#include "./renderoutputviewport.hpp"
#include "./genericscene.hpp"

namespace o3engine
{
	/**
	 * Example Application
	 */
	class ExampleApplication : public FrameListener, KeyboardListener, MouseListener
	{
	protected:

		O3Engine m_engine;      // The one and only one object
		bool m_paused;           // A flag if application is paused
		Real m_fps_secs;

		// Renderer's to use
		SimpleRenderer * mp_renderer;

		// Camera to use
		Camera * mp_camera;

		// Viewport
		RenderOutputViewport * mp_viewport;
		GenericScene * mp_genericscene;

		virtual void setupCamera(Camera *p_cam){}

		virtual void setupScene(){}

	private:
		void setupEngine()
		{
			// Initialize egine
			m_engine.init();
			enableFrameListening();
			enableKeyboardListening();
            enableMouseListening();

			// Set up some parameters
			Platform::getSingleton().setWindowTitle("O3Engine Example Application");
			Platform::getSingleton().setWindowBackColor(Color::BLACK);

			// Create renderer
			mp_renderer = new SimpleRenderer();
			m_engine.setRenderer(mp_renderer);

			// Create scenemanager
			mp_genericscene = new GenericScene();

			// Set up camera and viewport
			mp_viewport = new RenderOutputViewport(320, 240, 0, 0);
			mp_camera = new Camera(Vector3::NEGATIVE_UNIT_Z, Vector3::UNIT_Y, 60, 0.1, 40000);
			mp_viewport->setInputCamera(mp_camera);
			mp_viewport->enableRendering();
			mp_viewport->enableMouseListening();

			// Everything is ready, setup scene
			setupScene();

			// And now check the cam
			setupCamera(mp_camera);
		}

	protected:

		// Interval Renderer
		virtual void onRenderInterval(Real passed_interval)
		{
			// Show fps
			m_fps_secs += passed_interval;
			if (m_fps_secs > 2)
			{
				m_fps_secs = 0;
				printf("FPS: %f\n", m_engine.getFps());
			}

			if (m_paused) return;
		}

	public:
		// Default constructor
		ExampleApplication()
		{
			m_paused = false;    // No paused yet
			m_fps_secs = 0;       // No fps yet
		}


		// Start rendering
		void run(void)
		{
			// Setup engine and scene camera.. .bla bla
			setupEngine();

			// Start playing
			m_engine.startRendering();
		}
	};
}
#endif // EXAMPLEAPPLICATION_H_INCLUDED
