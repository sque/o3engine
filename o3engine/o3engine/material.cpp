#include "./materialmanager.hpp"
#include "./programmanager.hpp"

namespace o3engine
{
	Material::Material(const string & name)
		:ManagedObject<MaterialManager, string, Material>(name)	{

		mp_program = ProgramManager::getSingleton().getProgramPtr("default");
	}

	//! Get shader program
	const ogl::program & Material::getProgram() const {
		return * mp_program;
	}
}
