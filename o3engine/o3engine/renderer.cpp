#include "./o3engine.hpp"
#include "./renderer.hpp"

namespace o3engine
{
	// Default constructor
	Renderer::Renderer()
	{
		// Initialize pointers
		mp_outputs = &O3Engine::getSingletonPtr()->mv_render_outputs;
	}

}
