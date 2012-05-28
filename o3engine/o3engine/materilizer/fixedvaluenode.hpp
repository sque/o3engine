#ifndef O3ENGINE_MATERILIZER_COLORNODE_HPP_INCLUDED
#define O3ENGINE_MATERILIZER_COLORNODE_HPP_INCLUDED

#include "node.hpp"
#include "builder_tools.hpp"

namespace o3engine {
namespace materilizer {

	template<class Type, Socket::ValueType SocketValueType, const Type & DefaultValue>
	class FixedValueNode : public Node{
	public:

		//! Type of value
		typedef Type value_type;

		//! Construct with specific value
		FixedValueNode(const std::string & name, const value_type & value) :
			Node(name),
			m_value(value){
			addOutputSocket<SocketValueType>("value");
		}

		//! Construct with default value
		FixedValueNode(const std::string & name):
			FixedValueNode(name, DefaultValue){
		}

		//! Set new value
		void setValue(const value_type & c) {
			m_value = c;
		}

		//! Get value const reference
		const value_type & getValue() const {
			return m_value;
		}

		std::string getStaticCode(ogl::shader_type type) {
			return "";
		}

		std::string getExecutedCode(ogl::shader_type type) {
			return "";
		}

		std::string getOutputSocketReference(ogl::shader_type type, const std::string & socket_name) {
			return builder::literal(m_value);
		}

	private:

		//! Storage for value
		value_type m_value;
	};

	typedef FixedValueNode<Color, Socket::ValueType::Vec4, Color::BLACK> ColorNode;
}
}


#endif
