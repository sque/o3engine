#include "./node.hpp"


namespace o3engine {
namespace nodmaterial {

Node::Node(NodeContainer * powner, const std::string & instance_name, const std::string & type_name) :
	mp_owner(powner),
	m_instance_name(instance_name),
	m_type_name(type_name){
}

Node::~Node() {
	for(auto & sock : m_input_sockets) {
		delete sock.second;
	}
	for(auto & sock : m_output_sockets) {
		delete sock.second;
	}
}

}}

