#include "scenerenderer.hpp"
#include "camera.hpp"
#include "genericnode.hpp"
#include "genericscene.hpp"
#include <boost/smart_ptr/shared_ptr.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

template<class To, class From, bool Transpose = false>
struct convert_impl_mat4{
	static void op(To & dst, const From & src) {
		dst[0][0] = src[0][0];
		dst[0][1] = src[0][1];
		dst[0][2] = src[0][2];
		dst[0][3] = src[0][3];
		dst[1][0] = src[1][0];
		dst[1][1] = src[1][1];
		dst[1][2] = src[1][2];
		dst[1][3] = src[1][3];
		dst[2][0] = src[2][0];
		dst[2][1] = src[2][1];
		dst[2][2] = src[2][2];
		dst[2][3] = src[2][3];
		dst[3][0] = src[3][0];
		dst[3][1] = src[3][1];
		dst[3][2] = src[3][2];
		dst[3][3] = src[3][3];
	}
};

template<class To, class From>
struct convert_impl_mat4<To, From, true>{
	static void op(To & dst, const From & src) {
		dst[0][0] = src[0][0];
		dst[1][0] = src[0][1];
		dst[2][0] = src[0][2];
		dst[3][0] = src[0][3];
		dst[0][1] = src[1][0];
		dst[1][1] = src[1][1];
		dst[2][1] = src[1][2];
		dst[3][1] = src[1][3];
		dst[0][2] = src[2][0];
		dst[1][2] = src[2][1];
		dst[2][2] = src[2][2];
		dst[3][2] = src[2][3];
		dst[0][3] = src[3][0];
		dst[1][3] = src[3][1];
		dst[2][3] = src[3][2];
		dst[3][3] = src[3][3];
	}
};

template<bool Transpose = false, class To, class From>
void convert_mat4(To & dst, From & src) {
	convert_impl_mat4<To, From, Transpose>::op(dst, src);
}

//! Implementation of SceneRenderVisitor
struct SceneRendererDrawVisitor:
	public SceneRendererVisitor {

	struct UniformGlobalMatrices {
		glm::mat4 ProjectionMatrix;
		glm::mat4 ViewMatrix;
		glm::mat4 ProjectionViewMatrix;
	} m_ugm;

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

	void setSceneUniforms() {
		convert_mat4<true>(m_ugm.ProjectionMatrix, mp_renderer->getCameraPtr()->getProjectionMatrix());
		Matrix4 view_matrix = mp_renderer->getCameraPtr()->getSceneNode()->getGlobalTransformation();
				view_matrix = view_matrix.inverse();
		convert_mat4(m_ugm.ViewMatrix, view_matrix);
		mp_ubo->update_subdata(0, sizeof(UniformGlobalMatrices), &m_ugm);
		mp_ubo->bind_at_point(0);
	}

	//! Populate programs parameters with uniform values
	virtual void preDraw(ogl::program * pprog){
		set_dmat4_to_mat4(pprog->get_uniform("ModelMatrix"), mp_object_node->getGlobalTransformation());
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
	mp_scene_node_visitor->m_render_visitor.setSceneUniforms();
}

void SceneRenderer::render() {
	mp_scene->nextLoopCounterToBeChangedUglyFunction();
	mp_scene_node_visitor->m_render_visitor.setSceneUniforms();
	mp_scene->navigateActiveObjects(*mp_scene_node_visitor);
	renderNext();	//! Continue render line
}
}
