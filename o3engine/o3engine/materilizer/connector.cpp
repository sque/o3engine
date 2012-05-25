#include "connector.hpp"
namespace o3engine {
namespace materilizer {

//! Create a new connector
Connector::Connector(const std::string & name, ValueType vtype, Node * powner) :
		mp_owner_node(powner),
		m_value_type(vtype){
}

OutputConnector::OutputConnector(const std::string & name, ValueType vtype, Node * powner) :
		Connector(name, vtype, powner){

}

InputConnector::InputConnector(const std::string & name, ValueType vtype, Node * powner) :
		Connector(name, vtype, powner),
		mp_connected_at(nullptr) {

}

void InputConnector::connectTo(OutputConnector * pother) {
	if (getValueType() != pother->getValueType())
		throw std::runtime_error("materilizer::InputConnector::connect() Different value types");
	mp_connected_at = pother;
}
}}
