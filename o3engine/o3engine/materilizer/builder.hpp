#ifndef O3ENGINE_MATERILIZER_BUILDER_HPP_INCLUDED
#define O3ENGINE_MATERILIZER_BUILDER_HPP_INCLUDED

#include "node.hpp"
#include "builder_tools.hpp"

namespace o3engine {
namespace materilizer {

	class Builder {
	public:

		Builder(Node * proot);

		bool build();

		const std::string & getVertexSource() const {
			return m_vert_source;
		}

		const std::string & getFragmentSource() const {
			return m_frag_source;
		}
	protected:

		//! Vertex shader produced source code
		std::string m_vert_source;

		//! Fragment shader produced source code;
		std::string m_frag_source;

		//! Type definition of container with all nodes
		typedef std::map<std::string, Node * > nodes_type;

		//! A container with all chained nodes
		nodes_type m_nodes;

		//! Root node to use for building
		Node * m_root_node;

		//! Traverse all node connections and gather nodes
		void gatherChainedNodes(Node * pnode);

		//! Traverse all node connections and gather static code
		void gatherStaticCode(std::string & vert_static_source, std::string & frag_static_source);

		void processNode(Node * pnode);
	};
}
}


#endif
