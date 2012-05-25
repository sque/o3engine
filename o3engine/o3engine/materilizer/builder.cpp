#include "builder.hpp"

namespace o3engine {
namespace materilizer {
	Builder::Builder(Node * proot) :
	m_root_node(proot){

	}

	void processNode(Node * pnode) {

		//if (has)
	}
	//! Traverse all node connections and gather nodes
	void Builder::gatherChainedNodes(Node * pnode) {

		// Add node to active
		if (m_nodes.find(pnode->getName()) != m_nodes.end()) {
			throw materilizer_build_error("Found duplicate name \"" + pnode->getName() + "\"");
		}
		m_nodes[pnode->getName()] = pnode;

		// Continue for every chained object
		for(auto & con : pnode->getInputConnectors()) {
			if (con.second->isConnected())
				gatherChainedNodes(con.second->getConnectedNode());
		}
	}

	bool Builder::build() {
		// Gather all nodes
		gatherChainedNodes(m_root_node);

		return true;
	}


}
}
