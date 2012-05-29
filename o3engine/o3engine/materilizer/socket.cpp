#include "socket.hpp"
namespace o3engine {
namespace materilizer {


Socket::Socket(const std::string & name, ValueType vtype, Node * powner) :
	m_name(name),
	mp_owner_node(powner),
	m_value_type(vtype){
}


OutputSocket::OutputSocket(const std::string & name, ValueType vtype, Node * powner) :
	Socket(name, vtype, powner){

}

InputSocket::InputSocket(const std::string & name, ValueType vtype, Node * powner, const InputSocket::default_variant_type & def_value) :
	Socket(name, vtype, powner),
	mp_connected_at(nullptr),
	m_default_value(def_value){

	if (static_cast<int>(getValueType()) != m_default_value.which())
		throw std::runtime_error("InputSocket(): Default value must be of the same type as socket.");
}

InputSocket::~InputSocket() {
	if(isConnected())
		disconnect();
}

void InputSocket::connectTo(OutputSocket * pother) {
	if (getValueType() != pother->getValueType())
		throw std::runtime_error("materilizer::InputSocket::connect() Different value types");
	mp_connected_at = pother;
}
}}
