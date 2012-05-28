#include "materilizer.hpp"
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

void Materilizer::buildProgram() {

	materilizer::Builder mat_builder(this);
	mat_builder.build();

	setProgram(ProgramManager::getSingleton()
		.loadProgram("material_" + Material::getName(), mat_builder.getVertexSource(), mat_builder.getFragmentSource()));
}

}
