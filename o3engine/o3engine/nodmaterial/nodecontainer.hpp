#ifndef O3ENGINE_NODMATERIAL_NODECONTAINER_HPP_INCLUDED
#define O3ENGINE_NODMATERIAL_NODECONTAINER_HPP_INCLUDED

#include "node.hpp"

namespace o3engine {
namespace nodmaterial {

	//! Container of nodes
	class NodeContainer {
	public:
		//! Type definition of all containers nodes
		typedef std::map<std::string, Node *> nodes_container_type;

		//! Constructor
		NodeContainer();

		//! Delete all nodes
		~NodeContainer();

		//! Construct a new node and register it in container
		template <class NodeType,typename... Args>
		NodeType * createNode(const std::string & name, Args... args) {

			// Assert different name
			if (m_nodes.find(name) != m_nodes.end()) {
				throw std::runtime_error("Cannot create nodes with same name.");
			}

			NodeType * pnode = new NodeType(this, name, args...);
			m_nodes[name] = pnode;
			return pnode;
		}

		//! Get node by name
		Node * getNodePtr(const std::string & name) {
			return m_nodes[name];
		}

		//! Get all nodes
		nodes_container_type & getNodes() {
			return m_nodes;
		}

	protected:

		//! Container of all nodes
		nodes_container_type m_nodes;
	};
}
}


#endif
