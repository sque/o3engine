#include "scenerenderer.hpp"
#include "camera.hpp"
#include "genericnode.hpp"
#include "genericscene.hpp"
#include <boost/smart_ptr/shared_ptr.hpp>
#include <iostream>

namespace o3engine {

boost::shared_ptr<float> to_floatv(const Matrix4 &m) {
	boost::shared_ptr<float> fv(new float[16]);
	for(size_t i = 0; i < 16;i++) {
		(fv.get())[i] = (&m[0][0])[i];
	}
	return fv;
}

void set_dmat4_to_mat4(ogl::uniform & u, const Matrix4 &m) {
	float fv[16];
	for(size_t i = 0; i < 16;i++) {
		fv[i] = (&m[0][0])[i];
	}
	u.setmat4f(fv, true);
}

//! Implementation of SceneRenderVisitor
struct SceneRendererDrawVisitor:
	public SceneRendererVisitor {

	struct UniformGlobalMatrices {
		glm::mat4 ProjectionMatrix;
		glm::mat4 ViewMatrix;
		glm::mat4 ProjectionViewMatrix;
		glm::mat4 ModelMatrix;
	};

	//! Pointer to owner scene renderer
	SceneRenderer * mp_renderer;

	//! Pointer to the object's node
	GenericNode * mp_object_node;

	//! Uniform buffer object
	ogl::buffer * mp_ubo;

	SceneRendererDrawVisitor(SceneRenderer * prenderer):
		mp_renderer(prenderer),
		mp_ubo(new ogl::buffer(ogl::buffer_type::UNIFORM)){

		mp_ubo->define_data(sizeof(UniformGlobalMatrices), NULL, ogl::buffer_usage_pattern::STREAM_READ);
	}

	//! Populate programs parameters with uniform values
	virtual void setUniforms(ogl::program * pprog){
		/*set_dmat4_to_mat4(pprog->get_uniform("ProjectionMatrix"), mp_renderer->getCameraPtr()->getProjectionMatrix());
		Matrix4 view_matrix = mp_renderer->getCameraPtr()->getSceneNode()->getGlobalTransformation();
		view_matrix = view_matrix.inverse();
		view_matrix = view_matrix.transpose();
		set_dmat4_to_mat4(pprog->get_uniform("ViewMatrix"), view_matrix);
		set_dmat4_to_mat4(pprog->get_uniform("ModelMatrix"), mp_object_node->getGlobalTransformation());*/
	}
};

//! Implementation of SceneRenderer Node Visitor
struct SceneRendererNodeVisitor {
	SceneRenderer * mp_renderer;
	SceneRendererDrawVisitor  m_render_visitor;


	SceneRendererNodeVisitor(SceneRenderer * prenderer):
		m_render_visitor(prenderer){
		mp_renderer = prenderer;
	}

	void visitNode(GenericNode * pnode) {
	}

	void visitObject(GenericNode * pnode, DrawableObject * pobject) {
		m_render_visitor.mp_object_node = pnode;
		pobject->draw(&m_render_visitor);
	}
};

SceneRenderer::SceneRenderer(Camera * pcamera):
	mp_scene_node_visitor(new SceneRendererNodeVisitor(this)){
	setCamera(pcamera);
}

SceneRenderer::~SceneRenderer() {
	if (mp_scene_node_visitor)
		delete mp_scene_node_visitor;
}

void SceneRenderer::setCamera(Camera * pcamera) {
	mp_camera = pcamera;
	if (!mp_camera->getSceneNode())
		throw std::runtime_error("Cannot render from a detached camera.");
	mp_scene = dynamic_cast<GenericScene *>(mp_camera->getSceneNode()->getMySceneManager());
}

void SceneRenderer::render() {
	mp_scene->nextLoopCounterToBeChangedUglyFunction();

	mp_scene->navigateActiveObjects(*mp_scene_node_visitor);

	renderNext();	//! Continue render line
}
}
