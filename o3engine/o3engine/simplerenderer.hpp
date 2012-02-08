#ifndef SIMPLERENDERER_H_INCLUDED
#define SIMPLERENDERER_H_INCLUDED

#include "./prereqs.hpp"
#include "./renderer.hpp"

namespace o3engine
{
	class SimpleRenderer: public Renderer
	{
	public:

		SimpleRenderer()
		{    }

		// The main function to render all scene
		virtual void render();

		// Function when window is reshaped
		virtual void reshape(int w, int h);
	};
}
#endif
