#include "./mathnode.hpp"
#include "builder_tools.hpp"
#include <boost/format.hpp>

namespace o3engine {
namespace nodmaterial {


	MathNode::MathNode(NodeContainer * powner, const std::string & name) :
		Node(powner, name, typeid(name).name()),
		m_operation(Op::POW){
		addInputSocket<Socket::ValueType::Vec4>("arg1", Vector4(1,1,1,1));
		addInputSocket<Socket::ValueType::Vec4>("arg2", Vector4(1,1,1,1));
		addOutputSocket<Socket::ValueType::Vec4>("result");

		// Different approach for each case. Operator, function, one argument, two arguments....
		m_map_to_glslfunc2 [Op::POW] = "pow";
		m_map_to_glslfunc1[Op::SQUARE] = "sqrt";
		m_map_to_glslfunc1[Op::SIN] = "sin";
		m_map_to_glslfunc1[Op::COS] = "cos";
		m_map_to_glslfunc1[Op::TAN] = "tan";
		m_map_to_glslop[Op::ADD] = "+";
		m_map_to_glslop[Op::SUBSTRACT] = "-";
		m_map_to_glslop[Op::DIVIDE] = "/";
		m_map_to_glslop[Op::MUL] = "*";
		m_map_to_glslop[Op::MOD] = "%";
		}


	std::string MathNode::getStaticCode(ogl::shader_type type) {
		return "";
	}

	std::string MathNode::getExecutedCode(ogl::shader_type type) {
		if (type != ogl::shader_type::FRAGMENT)
			return "";
		std::string str = builder::variable_type(Socket::ValueType::Vec4) + " "
				+ builder::output_variable_name(this, "result");

		map_op_function_type::iterator it1 = m_map_to_glslfunc1.find(m_operation);
		if (it1 != m_map_to_glslfunc1.end()) {
			return (boost::format("%1% = %2%(%3%);\n")
				% str
				% it1->second
				% builder::input_value(type, this, "arg1")).str();
		}

		map_op_function_type::iterator it2 = m_map_to_glslfunc2.find(m_operation);
		if (it2 != m_map_to_glslfunc2.end()) {
			return (boost::format("%1% = %2%(%3%, %4%);\n")
				% str
				% it2->second
				% builder::input_value(type, this, "arg1")
				% builder::input_value(type, this, "arg2")).str();
		}

		map_op_function_type::iterator itop = m_map_to_glslop.find(m_operation);
		if (itop != m_map_to_glslop.end()) {
			return (boost::format("%1% = %2% %3% %4%;\n")
				% str
				% builder::input_value(type, this, "arg1")
				% itop->second
				% builder::input_value(type, this, "arg2")).str();
		}
		return "";
	}

	std::string MathNode::getOutputSocketReference(ogl::shader_type type, const std::string & socket_name) {
		return builder::output_variable_name(this, socket_name);
	}
}
}
