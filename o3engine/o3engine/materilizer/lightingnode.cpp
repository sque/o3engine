#include "lightingnode.hpp"
#include <boost/format.hpp>

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
			return "phong_lit();\n";
		default:
			return "";
		}
	}

}
}
