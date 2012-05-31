#include "./mathnode.hpp"


namespace o3engine {
namespace nodmaterial {


	MathNode::MathNode(NodeContainer * powner, const std::string & name) :
		Node(powner, name, typeid(name).name()){
		addInputSocket<Socket::ValueType::Vec4>("arg1", Vector4(1,1,1,1));
		addInputSocket<Socket::ValueType::Vec4>("arg2", Vector4(1,1,1,1));
		addOutputSocket<Socket::ValueType::Vec4>("result");


		// Different approach for each case. Operator, function, one argument, two arguments....
		m_map_op_to_glslfunctions[Op::POWER] = "pow";
		m_map_op_to_glslfunctions[Op::SQUARE] = "sqrt";
			/*ADD,
			POWER,
			SUBSTRACT,
			SQUARE,
			DIVIDE,
			SIN,
			COS,
			TAN,"]*/
	}


	std::string MathNode::getStaticCode(ogl::shader_type type) {
		return "";
	}

	std::string MathNode::getExecutedCode(ogl::shader_type type) {
		return "";
	}

	std::string MathNode::getOutputSocketReference(ogl::shader_type type, const std::string & socket_name) {
		return "";
	}
}
}
