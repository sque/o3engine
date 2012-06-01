#include "nodmaterial.hpp"
#include "nodmaterial/builder_tools.hpp"
#include "programmanager.hpp"

namespace o3engine {

	NodMaterial::NodMaterial(const std::string & name) :
		Material(name),
		Node(this, "material", typeid(this).name()){
		addInputSocket<nodmaterial::Socket::ValueType::Vec4>("color", Vector4(0, 0, 0, 1));

		m_nodes["material"] = this;	// Hack to self register our selfs to our-selfs container
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

	void NodMaterial::preUse() const {
		for(auto & func : m_predraw_functions) {
			func(getProgram());
		}
	}

	void NodMaterial::buildProgram() {

		// Build GLSL Program, and gather prepare functions
		nodmaterial::ProgramBuilder mat_builder(this);
		mat_builder.build();

		setProgram(ProgramManager::getSingleton()
			.loadProgram("material_" + Material::getName(), mat_builder.getVertexSource(), mat_builder.getFragmentSource()));
		m_predraw_functions = mat_builder.getPreDrawFunctions();
	}
}
