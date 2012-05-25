#ifndef O3ENGINE_MATERILIZER_CONNECTOR_HPP_INCLUDED
#define O3ENGINE_MATERILIZER_CONNECTOR_HPP_INCLUDED

#include "../prereqs.hpp"

namespace o3engine {
namespace materilizer {

	//! Prototype of node class
	class Node;
	class InputConnector;
	class OutputConnector;

	//! Connector type
	class Connector {
	public:

		//! Enumeration of value types
		enum class ValueType {
			Float,
			Int,
			Uint,
			Vec3,
			Vec4,
			Mat4,
			Mat3
		};

		//! Get the type of value
		ValueType getValueType() const {
			return m_value_type;
		}

		//! Get owner
		Node * getOwner() const {
			return mp_owner_node;
		}

		//! Get name
		const std::string & getName() const {
			return m_name;
		}

	protected:
		//! Create a new connector
		Connector(const std::string & name, ValueType vtype, Node * powner);

		//! Pointer to node owner
		Node * mp_owner_node;

		//! Type of this
		ValueType m_value_type;

		//! Name of this connector
		std::string m_name;
	};

	//! Specialization for input connector
	class InputConnector : public Connector {
	public:
		InputConnector(const std::string & name, ValueType vtype, Node * powner);

		//! Connect to an output connector
		void connectTo(OutputConnector * pother);

		//! Check if it is connected
		bool isConnected() {
			return mp_connected_at != nullptr;
		}

		//! Disconnect
		void disconnect() {
			mp_connected_at = nullptr;
		}

		//! Get connected node
		Node * getConnectedNode() {
			if (!isConnected())
				throw std::runtime_error("materilizer::Connector::getConnectedNode(): connector is not attached.");
			return mp_connected_at->getOwner();
		}

	protected:
		//! Pointer to the other connector
		Connector * mp_connected_at;

	};

	class OutputConnector : public Connector {
	public:
		OutputConnector(const std::string & name, ValueType vtype, Node * powner);

	};
}
}


#endif
