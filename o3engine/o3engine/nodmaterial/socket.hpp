#ifndef O3ENGINE_NODMATERIAL_SOCKET_HPP_INCLUDED
#define O3ENGINE_NODMATERIAL_SOCKET_HPP_INCLUDED

#include "../prereqs.hpp"
#include <boost/variant.hpp>

namespace o3engine {
namespace nodmaterial {

	//! Prototype of node class
	class Node;
	class InputSocket;
	class OutputSocket;

	//! Socket type
	class Socket {
	public:

		//! Enumeration of value types
		enum class ValueType {
			Float,
			Int,
			Uint,
			Vec2,
			Vec3,
			Vec4,
			Mat4,
			Mat3
		};

		//! Get the type of value
		ValueType getValueType() const {
			return m_value_type;
		}

		//! Get owner node
		Node * getOwner() const {
			return mp_owner_node;
		}

		//! Get name of this socket
		const std::string & getName() const {
			return m_name;
		}

	protected:

		//! Create new socket, it is called by derived classes
		Socket(const std::string & name, ValueType vtype, Node * powner);

		//! Inheritable
		virtual ~Socket(){}

		//! Name of this socket
		std::string m_name;

		//! Pointer to node owner
		Node * mp_owner_node;

		//! Type of this
		ValueType m_value_type;
	};

	//! Specialization for output socket
	class OutputSocket : public Socket {
	public:
		OutputSocket(const std::string & name, ValueType vtype, Node * powner);

	};

	//! Specialization for input socket
	class InputSocket : public Socket {
	public:

		//! Type of variant default type (these must be in the same order as ValueType)
		typedef boost::variant<float, std::int32_t, std::uint32_t, Vector2, Vector3, Vector4, Matrix3, Matrix4> default_variant_type;

		//! Construct an input socket
		InputSocket(const std::string & name, ValueType vtype, Node * powner, const default_variant_type & def_value);

		//! Clean up before destruction
		~InputSocket();

		//! Connect to an output socket
		void connectTo(OutputSocket * pother);

		//! Check if it is connected
		bool isConnected() {
			return mp_connected_at != nullptr;
		}

		//! Disconnect
		void disconnect() {
			mp_connected_at = nullptr;
		}

		//! Get the other node that is connected through this socket
		Node * getConnectedNode() {
			if (!isConnected())
				throw std::runtime_error("Socket::getConnectedNode(): socket is not attached.");
			return mp_connected_at->getOwner();
		}

		//! Get connected output socket
		OutputSocket * getConnectedSocket() {
			if (!isConnected())
				throw std::runtime_error("Socket::getConnectedSocket(): socket is not attached.");
			return mp_connected_at;
		}

		//! Get default value
		const default_variant_type & getDefaultValue() const{
			return m_default_value;
		}
	protected:

		//! Pointer to the other socket
		OutputSocket * mp_connected_at;

		//! Default value
		default_variant_type m_default_value;
	};

}
}


#endif
