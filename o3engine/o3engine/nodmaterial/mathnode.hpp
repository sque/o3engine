#ifndef O3ENGINE_NODMATERIAL_MATHNODE_HPP_INCLUDED
#define O3ENGINE_NODMATERIAL_MATHNODE_HPP_INCLUDED

#include "node.hpp"

namespace o3engine {
namespace nodmaterial {

	//! Generic math node for various types
	class MathNode : public Node{
	public:

		//! Enumeration with all operations
		enum class Op {
			MULTIPLY,
			ADD,
			POW,
			SUBSTRACT,
			SQUARE,
			DIVIDE,
			SIN,
			COS,
			TAN,
			MUL,
			MOD
		};

		MathNode(NodeContainer * powner, const std::string & name);

		//! Set mathematics operation
		void setOperation(Op op) {
			m_operation = op;
		}

		//! Get mathematics operation
		const Op & getOperation() const {
			return m_operation;
		}

		virtual std::string getStaticCode(ogl::shader_type type);

		virtual std::string getExecutedCode(ogl::shader_type type);

		virtual std::string getOutputSocketReference(ogl::shader_type type, const std::string & socket_name);

	private:

		//! Map operations to functions
		typedef std::map<Op, std::string> map_op_function_type;

		//! Map OP enum to GLSL function name argument1
		map_op_function_type m_map_to_glslfunc1;

		//! Map OP enum to GLSL function name argument2
		map_op_function_type m_map_to_glslfunc2;

		//! Map OP enum to GLSL operand
		map_op_function_type m_map_to_glslop;

		//! Operation to be done
		Op m_operation;
	};
}
}


#endif
