#include "./simplerenderer.hpp"
#include "./skybox.hpp"
#include "./scenemanager.hpp"
#include "./scenenode.hpp"

namespace o3engine {
	// Function when window is reshaped
	void SimpleRenderer::reshape(int w, int h) {

	}

	// The main function to render all scene
	void SimpleRenderer::render() {
		// Clear window
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render all viewports
		for (it_output = mp_outputs->begin(); it_output != mp_outputs->end();
				it_output++) {
			mp_currentoutput = *it_output;

			// Initialize output
			mp_currentoutput->onPreRender();

			// If there is a camera attached draw 3d World
			if ((mp_currentcam = mp_currentoutput->getInputCameraPtr()) != NULL) {
				// Initialize matrices and camera
				mp_currentcam->drawCamera();

				// Draw skybox
				mp_currentcam->drawSkybox();

				// Draw scene
				mp_currentcam->getAttachedNode()->getMySceneManager()->drawScene(
						mp_currentcam);
			}

			// Render Overlays
			mp_currentoutput->drawOverlays();

			// Finish output
			mp_currentoutput->onPostRender();
		}
	}
}
