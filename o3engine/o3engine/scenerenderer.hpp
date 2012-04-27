#ifndef O3ENGINE_SCENERENDERER_HPP_INCLUDED
#define O3ENGINE_SCENERENDERER_HPP_INCLUDED

#include "prereqs.hpp"
#include "./renderline/node.hpp"

namespace o3engine {

//! Early declaration of node visitor for this scene renderer.
struct SceneRendererNodeVisitor;

//! RenderLine node that renders a scene through a child camera.
class SceneRenderer:
	public RenderLine::Node{
public:

	//! Construct
	SceneRenderer(Camera * pcamera);

	//! Destructor
	~SceneRenderer();

	virtual void render();

	virtual void onStateAltered(){}

	//! Get rendered scene that camera is attached
	GenericScene * getScenePtr() {
		return mp_scene;
	}

	//! Get view camera
	Camera * getCameraPtr() {
		return mp_camera;
	}

	//! Set camera view
	void setCamera(Camera * pcamera);

protected:

	//! Pointer to the attached scene
	GenericScene * mp_scene;

	//! Pointer to the attached camera.
	Camera * mp_camera;

	//! Pointer to node visitor
	SceneRendererNodeVisitor * mp_scene_node_visitor;
};

}

#endif
