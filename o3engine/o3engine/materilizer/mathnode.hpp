#ifndef O3ENGINE_MATERILIZER_MATHNODE_HPP_INCLUDED
#define O3ENGINE_MATERILIZER_MATHNODE_HPP_INCLUDED

#include "node.hpp"

namespace o3engine {
namespace materilizer {

	class MathNode : public Node{
	public:

		enum class Op {
			Mix,
			Add
		};

		MathNode(const std::string & name) :
			Node(name){
			addInputConnector("arg1", Connector::ValueType::Vec4);
			addInputConnector("arg2", Connector::ValueType::Vec4);
			addOutputConnector("result", Connector::ValueType::Vec4);
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
