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
	std::string vert_source =
		"#version 330\n\n"
		""
		"#depend \"library/scene_parameters.vert\"\n"
		"#depend \"library/light.vert\"\n"
		"#depend \"library/attributes.vert\"\n"
		"void main(){\n"
		" gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * aPositionOs;";

	std::string frag_source =
		"#version 330\n\n"
		"out vec4 outColor;\n"
		"void main(){\n";

	materilizer::Builder mat_builder(this);
	mat_builder.build();

	vert_source += "\n}\n";
	frag_source += "\n}\n";


	setProgram(ProgramManager::getSingleton()
		.loadProgram("material_" + Material::getName(), mat_builder.getVertexSource(), mat_builder.getFragmentSource()));
}

}
