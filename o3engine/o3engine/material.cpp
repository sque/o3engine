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
				"#version 420\n"
				"layout(location=0) in vec4 aPosition;"
				""
				"layout(std140, binding=0) uniform SceneMatrices {"
				"	mat4 ProjectionMatrix;"
				"	mat4 ViewMatrix;"
				"	mat4 ProjectionViewMatrix;"
				"};"

				"uniform mat4 ModelMatrix;"
				""
				"out float depth;"
				""
				"void main() {"
				"	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * aPosition;"
				"	depth = clamp((gl_Position.z - 5)/15, 0.0, 1.0);"
				"}");
		ogl::shader * pdef_frag = new ogl::shader(ogl::shader_type::FRAGMENT,
				"#version 330\n"
				""
				"in float depth;"
				"out vec4 outColor;"
				"void main() {"
				"	outColor = vec4(1, 1, 1, 1)*depth;"
				"}");
		mp_program->attach_shader(*pdef_vert);
		mp_program->attach_shader(*pdef_frag);
		mp_program->build();
	}

	//! Get shader program
	const ogl::program & Material::getProgram() const {
		return * mp_program;
	}
}
