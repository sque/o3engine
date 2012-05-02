#include "./materialmanager.hpp"
#include "./programmanager.hpp"

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
		mp_program = ProgramManager::getSingleton().getProgramPtr("default");
	}

	//! Get shader program
	const ogl::program & Material::getProgram() const {
		return * mp_program;
	}
}
