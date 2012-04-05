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
				"	gl_Position = ProjectionMatrix * ViewMatrix * aPosition;"
				//"	gl_Position = aPosition;"
				"}");
		mp_default_program->attach_shader(*pdef_vert);
		mp_default_program->build();
	}

	// Destructor
	GenericScene::~GenericScene() {
		// Delete root node
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

		//Real rad90Deg = math::degreeToRadian(90);

		// Iterators
		GenericNode::active_nodes_type::iterator it;
		vector<GenericNode*>::iterator transIt;
		vector<GenericNode*>::iterator lightIt;

		// Camera's global position
		Quaternion camera_gorientation_ops = pRenderCamera->getSceneNode()->getGlobalOrientation().conjugate();
		Vector3 camera_gposition = pRenderCamera->getSceneNode()->getGlobalPosition();
		GenericNode * pnode;
		Vector3 camera_relpos;

		// Render Lighting
		//! @todo Write a better implementation of lighting
		/*glEnable(GL_LIGHTING);
		glLightModel(GL_LIGHT_MODEL_AMBIENT, m_ambient_light);
		GLint el = 0;
		for(lightIt = mv_light_nodes.begin();lightIt != mv_light_nodes.end(); lightIt++) {
			pnode = (*lightIt);
			// Update global positions/orientation
			pnode->_updateCachedGPos_GOrient(m_loop_counter);

			glPushMatrix();
				glTranslate(pnode->v3_gposition);
				glRotate(pnode->qu_gorientation);
				glLight((*lightIt)->getLight(), GL_LIGHT0 + el);
			glPopMatrix();
			el++;
		}*/

		// Render 1st Pass (Solid Objects)
		//setSceneUniforms(mp_default_program, pRenderCamera);
		setSceneUniforms(mp_default_program, pRenderCamera);
		m_trans_nodes.clear();
		for(it = m_activenodes.begin();it != m_activenodes.end(); it++) {
			pnode = *it;

			// Update global positions/orientation
			pnode->_updateCachedGPos_GOrient(m_loop_counter);

			camera_relpos = camera_gorientation_ops * (pnode->m_gposition - camera_gposition);

			// Scene angle clipping
			if (m_enabled_clipping)  {
				/*Real camFovRad = math::degreeToRadian(pRenderCamera->getFovY());

				if ((camera_relpos.z >= 0) || 	// Fast reject behind XY plane
					((rad90Deg - math::arcSin(-camera_relpos.normal().z)) > camFovRad) )	// Reject by camera's angle
				continue;*/
			}
			// Limit distance clipping
			if ((m_enabled_far_cutoff) && (camera_relpos.squaredLength() > m_farcutoff_sqdistance))
				continue;

			mp_default_program->use();
			mp_default_program->get_uniform("ModelMatrix").setmat4d(&pRenderCamera->getSceneNode()->getGlobalTransformation()[0][0]);
			pnode->drawObjects(true);

			// Add node if needed at 2n pass rendering
			if (pnode->hasTransperantObjects())
				m_trans_nodes.push_back(pnode);
		}

		// Render 2nd Pass (Transparent objects)
		for(transIt = m_trans_nodes.begin();transIt != m_trans_nodes.end();transIt++) {
			pnode = *transIt;


			pnode->drawObjects(false);
		}

	}
}
