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

SceneRenderer::SceneRenderer(Camera * pcamera){
	setCamera(pcamera);

	// Create default program
	mp_default_program = new ogl::program();
	ogl::shader * pdef_vert = new ogl::shader(ogl::shader_type::VERTEX,
			"#version 400\n"
			"layout(location=0) in vec4 aPosition;"
			""
			"uniform mat4 ProjectionMatrix;"
			"uniform mat4 ViewMatrix;"
			"uniform mat4 ProjectionViewMatrix;"
			"uniform mat4 ModelMatrix;"
			""
			"void main() {"
			"	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * aPosition;"
			//"	gl_Position = ViewMatrix * aPosition;"
			"}");
	ogl::shader * pdef_frag = new ogl::shader(ogl::shader_type::FRAGMENT,
			"#version 330\n"
			""
			"out vec4 outColor;"
			"void main() {"
			"	outColor = vec4(1, 1, 0, 1);"
			"	outColor = vec4(gl_FragDepth, gl_FragDepth, gl_FragDepth, 1);"
			"}");
	mp_default_program->attach_shader(*pdef_vert);
	mp_default_program->attach_shader(*pdef_frag);
	mp_default_program->build();
}

void SceneRenderer::setCamera(Camera * pcamera) {
	mp_camera = pcamera;
	if (!mp_camera->getSceneNode())
		throw std::runtime_error("Cannot render from a detached camera.");
	mp_scene = dynamic_cast<GenericScene *>(mp_camera->getSceneNode()->getMySceneManager());
}


void SceneRenderer::setSceneUniforms(ogl::program * pprogram) {
	set_dmat4_to_mat4(pprogram->get_uniform("ProjectionMatrix"), mp_camera->getProjectionMatrix());
	Matrix4 view_matrix = mp_camera->getSceneNode()->getGlobalTransformation();
	view_matrix = view_matrix.inverse();
	view_matrix = view_matrix.transpose();
	set_dmat4_to_mat4(pprogram->get_uniform("ViewMatrix"), view_matrix);
}
GenericNode * pLastNode = nullptr;

struct SceneRendererObjectVisitor:
	public SceneRendererVisitor {
	SceneRenderer * mp_renderer;

	SceneRendererObjectVisitor(SceneRenderer * prenderer){
		mp_renderer = prenderer;
		mp_renderer->setSceneUniforms(mp_renderer->mp_default_program);
	}

	virtual void populateSceneParameters(ogl::program * target){
		mp_renderer->setSceneUniforms(target);
		set_dmat4_to_mat4(target->get_uniform("ModelMatrix"), pLastNode->getGlobalTransformation());
	}
};

struct SceneRendererNodeVisitor {
	SceneRenderer * mp_renderer;
	SceneRendererObjectVisitor  m_object_visitor;

	SceneRendererNodeVisitor(SceneRenderer * prenderer):
		m_object_visitor(prenderer){
		mp_renderer = prenderer;
		mp_renderer->setSceneUniforms(mp_renderer->mp_default_program);
	}

	void visitNode(GenericNode * pnode) {
		pLastNode = pnode;
	}

	void visitObject(GenericNode * pnode, DrawableObject * pobject) {
		mp_renderer->mp_default_program->use();
		//std::cout << "Visiting object " << pobject->getName() << std::endl;
		pobject->draw(&m_object_visitor);
	}
};

void SceneRenderer::render() {
	mp_scene->nextLoopCounterToBeChangedUglyFunction();
	SceneRendererNodeVisitor visitor(this);
	mp_scene->navigateActiveObjects(visitor);
	renderNext();
}
}
