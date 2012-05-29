#ifndef O3ENGINE_NODMATERIAL_MATHNODE_HPP_INCLUDED
#define O3ENGINE_NODMATERIAL_MATHNODE_HPP_INCLUDED

#include "node.hpp"

namespace o3engine {
namespace nodmaterial {

	class MathNode : public Node{
	public:

		enum class Op {
			Mix,
			Add
		};

		MathNode(NodeContainer * powner, const std::string & name) :
			Node(powner, name, typeid(name).name()){
			addInputSocket<Socket::ValueType::Vec4>("arg1", Vector4(1,1,1,1));
			addInputSocket<Socket::ValueType::Vec4>("arg2", Vector4(1,1,1,1));
			addOutputSocket<Socket::ValueType::Vec4>("result");
		}

		void setOperation(Op op) {
			m_operation = op;
		}

		const Op & getOperation() const {
			return m_operation;
		}

	private:
		Op m_operation;
	};
}
}


#endif
