#include "lightingnode.hpp"
#include <boost/format.hpp>
#include "builder_tools.hpp"

namespace o3engine {
namespace materilizer {

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

	std::string LightingNode::getGeneratedCode(ogl::shader_type type) {
		switch (type) {
		case ogl::shader_type::VERTEX:
			return "phong_lit();\n";
		case ogl::shader_type::FRAGMENT:
			return (boost::format("%1% %2% = phong_for_all_lights(vec4(0,0,0,1), vec4(0,0,0,1), %3%, vec4(1,1,1,1), 50);\n")
				% builder::variable_type(getOutputConnector("color")->getValueType())
				% builder::output_variable(this, "color")
				% builder::input_data_value(type, this, "diffuse")
			).str();
		default:
			return "";
		}
	}

	std::string LightingNode::getGeneratedOutputValue(ogl::shader_type type, const std::string & connector_name) {
		switch (type) {
		case ogl::shader_type::VERTEX:
			return "";
		case ogl::shader_type::FRAGMENT:
			return builder::output_variable(this, "color");
		default:
			return "";
		}
	}

}
}
