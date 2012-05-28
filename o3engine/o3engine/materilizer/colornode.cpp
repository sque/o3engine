#include "colornode.hpp"
#include "builder_tools.hpp"
#include <boost/format.hpp>

namespace o3engine {
namespace materilizer {

	std::string ColorNode::getStaticCode(ogl::shader_type type) {
		return "";
	}

	std::string ColorNode::getGeneratedCode(ogl::shader_type type) {

		switch(type){
		case ogl::shader_type::FRAGMENT:
			return (boost::format("%1% %2% = %3%;\n")
				% builder::variable_type(this->getOutputConnector("value")->getValueType())
				% builder::output_variable(this, "value")
				% builder::literal(m_color)).str();
		default:
			return "";
		}

	}

	std::string ColorNode::getGeneratedOutputValue(ogl::shader_type type, const std::string & connector_name) {
		return (boost::format("%1%") % builder::literal(m_color)).str();
	}

}
}
