#include "./node.hpp"


namespace o3engine {
namespace materilizer {

Node::~Node() {
	for(auto & sock : m_input_sockets) {
		delete sock.second;
	}
	for(auto & sock : m_output_sockets) {
		delete sock.second;
	}
}

}}

