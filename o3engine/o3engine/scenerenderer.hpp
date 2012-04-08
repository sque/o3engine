#ifndef O3ENGINE_SCENERENDERER_HPP_INCLUDED
#define O3ENGINE_SCENERENDERER_HPP_INCLUDED

#include "prereqs.hpp"
#include "./renderline/node.hpp"

namespace o3engine {

class SceneRenderer:
	public RenderLine::Node{
public:

	SceneRenderer(Camera * pcamera);

	virtual void render();

	virtual void onStateAltered(){}

	GenericScene * getScenePtr() {
		return mp_scene;
	}

	Camera * getCameraPtr() {
		return mp_camera;
	}

	void setCamera(Camera * pcamera);

	ogl::program * mp_default_program;

	void setSceneUniforms(ogl::program * pprogram);

protected:

	GenericScene * mp_scene;

	Camera * mp_camera;
};

}

#endif
