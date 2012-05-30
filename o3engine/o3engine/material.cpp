#include "./materialmanager.hpp"
#include "./programmanager.hpp"

namespace o3engine{

	MaterialParameter::MaterialParameter(Material * powner, const std::string & name) :
		mp_owner(powner),
		m_name(name){

	}

	ogl::uniform & MaterialParameter::getUniform() {
		return mp_owner->getProgram().get_uniform(m_name);
	}

	Material::Material(const std::string & name)
		:ManagedObject<MaterialManager, string, Material>(name)	{
		mp_program = ProgramManager::getSingleton().getProgramPtr("default");
	}

	void Material::addParameter(const std::string & param_name) {
		if (hasParameter(param_name))
			throw std::runtime_error("Material: cannot add a parameter with same name");
		m_params[param_name] = MaterialParameter(this, param_name);
	}

	bool Material::hasParameter(const std::string & param_name) {
		return (m_params.find(param_name) != m_params.end());
	}

	Material::parameters_container_type Material::getParameters() {
		return m_params;
	}

	MaterialParameter & Material::getParameter(const std::string & param_name) {
		return m_params[param_name];
	}
}
