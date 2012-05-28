#include "materilizer.hpp"
#include "materilizer/builder_tools.hpp"
#include "materilizer/programbuilder.hpp"
#include "programmanager.hpp"

namespace o3engine {

Materilizer::Materilizer(const std::string & name) :
	Material(name),
	Node(name){
	addInputSocket<materilizer::Socket::ValueType::Vec4>("color", Vector4(0, 0, 0, 1));
}

std::string Materilizer::getStaticCode(ogl::shader_type type) {
	return "";
}

std::string Materilizer::getExecutedCode(ogl::shader_type type) {
	return "";
}

std::string Materilizer::getOutputSocketReference(ogl::shader_type type, const std::string & connector_name) {
	switch(type) {
	case ogl::shader_type::FRAGMENT:
		return "outColor = " + materilizer::builder::input_value(type, this, "color") + ";";
	default:
		return "";
	}
}

void Materilizer::buildProgram() {

	materilizer::ProgramBuilder mat_builder(this);
	mat_builder.build();

	setProgram(ProgramManager::getSingleton()
		.loadProgram("material_" + Material::getName(), mat_builder.getVertexSource(), mat_builder.getFragmentSource()));
}

}
