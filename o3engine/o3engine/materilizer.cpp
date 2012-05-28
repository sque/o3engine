#include "materilizer.hpp"
#include "materilizer/builder_tools.hpp"
#include "materilizer/builder.hpp"
#include "programmanager.hpp"

namespace o3engine {

Materilizer::Materilizer(const std::string & name) :
	Material(name),
	Node(name){
	addInputConnector("color", materilizer::Connector::ValueType::Vec4);
}

std::string Materilizer::getStaticCode(ogl::shader_type type) {
	return "";
}

std::string Materilizer::getGeneratedCode(ogl::shader_type type) {
	return "";
}

std::string Materilizer::getGeneratedOutputValue(ogl::shader_type type, const std::string & connector_name) {
	switch(type) {
	case ogl::shader_type::FRAGMENT:
		return "outColor = " + materilizer::builder::input_data_value(type, this, "color") + ";";
	default:
		return "";
	}
}

void Materilizer::buildProgram() {

	materilizer::Builder mat_builder(this);
	mat_builder.build();

	setProgram(ProgramManager::getSingleton()
		.loadProgram("material_" + Material::getName(), mat_builder.getVertexSource(), mat_builder.getFragmentSource()));
}

}
