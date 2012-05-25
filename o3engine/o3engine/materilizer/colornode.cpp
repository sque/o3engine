#include "colornode.hpp"
#include <boost/format.hpp>

namespace o3engine {
namespace materilizer {

	std::string ColorNode::getStaticCode(ogl::shader_type type) {
		return "";
	}

	std::string ColorNode::getGeneratedCode(ogl::shader_type type) {

		switch(type){
		case ogl::shader_type::FRAGMENT:
			return (boost::format("vec4 %1% = vec4(%2%, %3%, %4%, %5);\n")
						% getGeneratedOutputVariable("value")
						% m_color.red % m_color.green % m_color.blue % m_color.alpha).str();
		default:
			return "";
		}

	}

}
}
