#include "./materialmanager.hpp"

namespace o3engine
{
	Material::Material(const string & name)
		:ManagedObject<MaterialManager, string, Material>(name)
	{
		/*// Set default values
		c_basic = Color::WHITE;
		c_diffuse = Color(0.8, 0.8, 0.8, 1.0);
		c_ambient = Color(0.2, 0.2, 0.2, 0.2);
		c_specular = Color::WHITE;
		c_emission = Color::BLACK;
		m_shininess = 50;
		f_lighting = b_depthwrite = true;
		seq = 1;
		p_Texture = NULL;*/
		// Default
		// Create default program
		mp_program = new ogl::program();
		ogl::shader * pdef_vert = new ogl::shader(ogl::shader_type::VERTEX,
				"#version 400\n"
				"layout(location=0) in vec4 aPosition;"
				""
				"layout(std140) uniform SceneMatrices {"
				"	mat4 ProjectionMatrix;"
				"	mat4 ViewMatrix;"
				"	mat4 ProjectionViewMatrix;"
				"};"

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
				//"	outColor = vec4(gl_FragDepth, gl_FragDepth, gl_FragDepth, 1);"
				"}");
		mp_program->attach_shader(*pdef_vert);
		mp_program->attach_shader(*pdef_frag);
		mp_program->build();
	}

	// Run opengl commands to setup material
	void Material::onPreDraw() const
	{
		/*return ;
		// Color
		if (f_lighting)
		{
			glEnable ( GL_COLOR_MATERIAL );

			// Diffuse
			glColorMaterial ( GL_FRONT_AND_BACK, GL_DIFFUSE ) ;
			glColor4(c_diffuse);

			// Ambient
			glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT ) ;
			glColor4(c_ambient);

			// Specular
			glColorMaterial ( GL_FRONT_AND_BACK, GL_SPECULAR ) ;
			glColor4(c_specular);

			// Emission
			glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
			glColor4(c_emission);

			// Disable color
			glDisable( GL_COLOR_MATERIAL ) ;

			// Shininess
			glMaterialf(GL_FRONT, GL_SHININESS, (GLfloat)m_shininess);
		}else
		{
			glColor4(c_basic);    // Basic color
			glDisable(GL_LIGHTING);
		}

		// Disable depth if it is transperant
		if (!b_depthwrite)
			glDepthMask(GL_FALSE);

		// Enable texturing
		if (p_Texture)
		{
			//p_Texture->glBind2d();
			//glEnable( GL_TEXTURE_2D );
		}*/
	}

	// Run opengl to post-set materials after object drawing
	void Material::onPostDraw() const
	{
		/*return;
		// Enable lighting again
		if (!f_lighting)
			glEnable(GL_LIGHTING);

		// Disable depth if it is transperant
		if (!b_depthwrite)
			glDepthMask(GL_TRUE);

		// Disable texturing
		if (p_Texture)
		{   glDisable( GL_TEXTURE_2D );    }

		*/
	}

	//! Get shader program
	const ogl::program & Material::getProgram() const {
		return * mp_program;
	}
}
