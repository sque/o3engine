#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include "./prereqs.hpp"
#include "./renderoutputviewport.hpp"
#include "./camera.hpp"
#include "./scenenode.hpp"
#include "./renderoutput.hpp"

#include <vector>
#include <string>

namespace o3engine
{
	using namespace std;

	class Renderer
	{
	protected:
		vector<RenderOutput *>::iterator it_output;
		vector<RenderOutput *> * mp_outputs;
		Camera * mp_currentcam;           	// Pointer to camera
		RenderOutput * mp_currentoutput;		// Pointer to viewport

	public:

		// Default constructor
		Renderer();

		virtual ~Renderer(){}

		// Function to render everything
		virtual void render() = 0;

		// Function when window is reshaped
		virtual void reshape(int w, int h) = 0;

		// Get current rendering Camera
		inline Camera * getCurrentRenderingCamera()
		{   return mp_currentcam;    }

		// Get current rendering Camera global position
		inline Vector3 getCurrentRenderingCameraGPosition()
		{	SceneNode * pNodeCam = mp_currentcam->getAttachedNode();
			if (pNodeCam)
				return pNodeCam->getGlobalPosition();
			else
				return Vector3::ZERO;
		}

		// Get current rendering Camera global orientation
		inline Quaternion getCurrentRenderingCameraGOrientation()
		{   SceneNode * pNodeCam = mp_currentcam->getAttachedNode();
			if (pNodeCam)
				return pNodeCam->getGlobalOrientation();
			else
				return Quaternion::IDENTITY;
		}
	};
}
#endif // RENDERER_H_INCLUDED
