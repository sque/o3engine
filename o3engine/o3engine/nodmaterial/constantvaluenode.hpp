#ifndef O3ENGINE_NODMATERIAL_COLORNODE_HPP_INCLUDED
#define O3ENGINE_NODMATERIAL_COLORNODE_HPP_INCLUDED

#include "node.hpp"
#include "builder_tools.hpp"

namespace o3engine {
namespace nodmaterial {

	//! Node representing constant value
	template<class Type, Socket::ValueType SocketValueType, const Type & DefaultValue>
	class ConstantValueNode : public Node{
	public:

		//! Type of value
		typedef Type value_type;


		//! Construct and initialize with a value
		ConstantValueNode(NodeContainer * powner, const std::string & name, const value_type & value) :
			Node(powner, name, typeid(this).name()),
			m_value(value){
			addOutputSocket<SocketValueType>("value");
		}

		//! Construct with default value
		ConstantValueNode(NodeContainer * powner, const std::string & name):
			ConstantValueNode(powner, name, DefaultValue){
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

	typedef ConstantValueNode<Color, Socket::ValueType::Vec4, Color::BLACK> ColorNode;
	typedef ConstantValueNode<Vector2, Socket::ValueType::Vec2, Vector2::IDENTITY> Vector2Node;
	typedef ConstantValueNode<Vector3, Socket::ValueType::Vec3, Vector3::IDENTITY> Vector3Node;
	typedef ConstantValueNode<Vector4, Socket::ValueType::Vec4, Vector4::IDENTITY> Vector4Node;
}
}


#endif
