#include "nodmaterial.hpp"
#include "nodmaterial/builder_tools.hpp"
#include "nodmaterial/programbuilder.hpp"
#include "programmanager.hpp"

namespace o3engine {

NodMaterial::NodMaterial(const std::string & name) :
	Material(name),
	Node(this, name, typeid(this).name()){
	addInputSocket<nodmaterial::Socket::ValueType::Vec4>("color", Vector4(0, 0, 0, 1));
}

std::string NodMaterial::getStaticCode(ogl::shader_type type) {
	return "";
}

std::string NodMaterial::getExecutedCode(ogl::shader_type type) {
	return "";
}

std::string NodMaterial::getOutputSocketReference(ogl::shader_type type, const std::string & connector_name) {
	switch(type) {
	case ogl::shader_type::FRAGMENT:
		return "outColor = " + nodmaterial::builder::input_value(type, this, "color") + ";";
	default:
		return "";
	}
}

void NodMaterial::buildProgram() {

	nodmaterial::ProgramBuilder mat_builder(this);
	mat_builder.build();

	setProgram(ProgramManager::getSingleton()
		.loadProgram("material_" + Material::getName(), mat_builder.getVertexSource(), mat_builder.getFragmentSource()));
}

}
