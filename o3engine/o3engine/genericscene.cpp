#include "./genericscene.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace o3engine
{
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
				"#version 330\n"
				"layout(location=0) in vec4 aPosition;"
				""
				"uniform mat4 ProjectionMatrix;"
				"uniform mat4 ViewMatrix;"
				"uniform mat4 ProjectionViewMatrix;"
				"uniform mat4 ModelMatrix;"
				""
				"void main() {"
				//"	gl_Position = ProjectionMatrix * ViewMatrix * aPosition;"
				"	gl_Position = aPosition;"
				"}");
		ogl::shader * pdef_frag = new ogl::shader(ogl::shader_type::FRAGMENT,
				"#version 330\n"
				""
				"out vec4 outColor;"
				"void main() {"
				"	outColor = vec4(0,0,0,1);"
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
		/*pprogram->get_uniform("ProjectionMatrix").setmat4d(&pRenderCamera->getProjectionMatrix()[0][0], true);
		Matrix4 view_matrix = pRenderCamera->getSceneNode()->getGlobalTransformation();
		view_matrix.transpose();
		Matrix4 proj_view_matrix = pRenderCamera->getProjectionMatrix() * view_matrix;
		pprogram->get_uniform("ViewMatrix").setmat4d(&view_matrix[0][0]);
		pprogram->get_uniform("ProjectionViewMatrix").setmat4d(&proj_view_matrix[0][0]);*/

		glm::mat4 proj_matrix =  glm::perspective(45.0f, 1.0f, 0.0f, 1000.0f);
		glm::mat4 ViewTranslate = glm::translate(
				glm::mat4(1.0f),
				glm::vec3(0,0,-10));
		pprogram->get_uniform("ProjectionMatrix").setmat4f(glm::value_ptr(proj_matrix), false);
		pprogram->get_uniform("ViewMatrix").setmat4f(glm::value_ptr(ViewTranslate), false);
	}

	void GenericScene::drawScene(Camera * pRenderCamera) {
		m_loop_counter++;	// Increase counter

		// Render 1st Pass (Solid Objects)
		setSceneUniforms(mp_default_program, pRenderCamera);
		for(auto & pnode : m_activenodes) {
			// Update global positions/orientation
			pnode->_updateCachedGPos_GOrient(m_loop_counter);

			mp_default_program->use();
			mp_default_program->get_uniform("ModelMatrix").setmat4d(&pRenderCamera->getSceneNode()->getGlobalTransformation()[0][0]);
			pnode->drawObjects();
		}
	}
}
