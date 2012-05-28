#include "lightingnode.hpp"
#include <boost/format.hpp>
#include "builder_tools.hpp"

namespace o3engine {
namespace materilizer {

	LightingNode::LightingNode(const std::string & name):
			Node(name){
		addInputSocket<Socket::ValueType::Vec4>("emission", Vector4(0, 0, 0, 1));
		addInputSocket<Socket::ValueType::Vec4>("ambient", Vector4(0.15, 0.15, 0.15, 1));
		addInputSocket<Socket::ValueType::Vec4>("diffuse", Vector4(0.8, 0.8, 0.8, 1));
		addInputSocket<Socket::ValueType::Vec4>("specular", Vector4(0.8, 0.8, 0.8, 1));
		addInputSocket<Socket::ValueType::Float>("shininess", 50.0f);
		addInputSocket<Socket::ValueType::Vec3>("normal", Vector3(0, 1, 0));
		addOutputSocket<Socket::ValueType::Vec4>("color");
	}

	std::string LightingNode::getStaticCode(ogl::shader_type type) {
		switch (type) {
		case ogl::shader_type::VERTEX:
			return "#depend \"library/phong.vert\"\n";
		case ogl::shader_type::FRAGMENT:
			return "#depend \"library/phong.frag\"\n";
		default:
			return "";
		}

	}

	std::string LightingNode::getExecutedCode(ogl::shader_type type) {
		switch (type) {
		case ogl::shader_type::VERTEX:
			return "phong_lit();\n";
		case ogl::shader_type::FRAGMENT:
			return (boost::format("%1% %2% = phong_for_all_lights(%3%, %4%, %5%, %6%, %7%);\n")
				% builder::variable_type(getOutputSocket("color")->getValueType())
				% builder::output_variable_name(this, "color")
				% builder::input_value(type, this, "emission")
				% builder::input_value(type, this, "ambient")
				% builder::input_value(type, this, "diffuse")
				% builder::input_value(type, this, "specular")
				% builder::input_value(type, this, "shininess")
			).str();
		default:
			return "";
		}
	}

	std::string LightingNode::getOutputSocketReference(ogl::shader_type type, const std::string & connector_name) {
		switch (type) {
		case ogl::shader_type::VERTEX:
			return "";
		case ogl::shader_type::FRAGMENT:
			return builder::output_variable_name(this, "color");
		default:
			return "";
		}
	}

}
}
