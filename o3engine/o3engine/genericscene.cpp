#include "./genericscene.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <boost/smart_ptr/shared_ptr.hpp>

namespace o3engine
{
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
	// Constructor
	GenericScene::GenericScene() {
		// Initialize variable
		m_loop_counter = 0;
		m_farcutoff_distance = 1000;
		m_farcutoff_sqdistance = m_farcutoff_distance * m_farcutoff_distance;
		m_enabled_far_cutoff = true;
		m_enabled_clipping = true;
		m_ambient_light = Color(0.2, 0.2, 0.2, 1);

		// Create root node
		mp_root_node = new GenericNode("root", this);

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

	// Destructor
	GenericScene::~GenericScene() {
		delete mp_root_node;
	}

	void GenericScene::setSceneUniforms(ogl::program * pprogram, Camera * pRenderCamera) {
		set_dmat4_to_mat4(pprogram->get_uniform("ProjectionMatrix"), pRenderCamera->getProjectionMatrix());
		Matrix4 view_matrix = pRenderCamera->getSceneNode()->getGlobalTransformation();
		view_matrix = view_matrix.inverse();
		view_matrix = view_matrix.transpose();
		set_dmat4_to_mat4(pprogram->get_uniform("ViewMatrix"), view_matrix);
	}

	void GenericScene::drawScene(Camera * pRenderCamera) {
		m_loop_counter++;	// Increase counter

		// Render 1st Pass (Solid Objects)
		static_cast<GenericNode *>(pRenderCamera->getSceneNode())->_updateCachedGPos_GOrient(m_loop_counter);
		setSceneUniforms(mp_default_program, pRenderCamera);
		for(auto & pnode : m_activenodes) {
			// Update global positions/orientation
			pnode->_updateCachedGPos_GOrient(m_loop_counter);

			set_dmat4_to_mat4(mp_default_program->get_uniform("ModelMatrix"), pnode->getGlobalTransformation());
			ogl::gl_error_checkpoint("Boom");
			mp_default_program->use();
			pnode->drawObjects();
		}
	}
}
