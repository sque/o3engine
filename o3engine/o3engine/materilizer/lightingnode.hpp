#ifndef O3ENGINE_MATERILIZER_LIGHTINGNODE_HPP_INCLUDED
#define O3ENGINE_MATERILIZER_LIGHTINGNODE_HPP_INCLUDED

#include "node.hpp"

namespace o3engine {
namespace materilizer {

	class LightingNode : public Node{
	public:

		enum class Op {
			Mix,
			Add
		};

		LightingNode(const std::string & name):
			Node(name){
			addInputConnector("diffuse", Connector::ValueType::Vec4);
			addInputConnector("ambient", Connector::ValueType::Vec4);
			addInputConnector("shininess", Connector::ValueType::Float);
			addInputConnector("normal", Connector::ValueType::Vec3);

			addOutputConnector("color", Connector::ValueType::Vec4);
		}

		void setOperation(Op op) {
			m_operation = op;
		}

		const Op & getOperation() const {
			return m_operation;
		}

		virtual std::string getStaticCode(ogl::shader_type type);

		virtual std::string getGeneratedCode(ogl::shader_type type);


	private:
		Op m_operation;
	};
}
}


#endif /* LIGHTINGNODE_HPP_ */
