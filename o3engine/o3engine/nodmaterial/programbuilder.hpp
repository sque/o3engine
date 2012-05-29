#ifndef O3ENGINE_NODMATERIAL_BUILDER_HPP_INCLUDED
#define O3ENGINE_NODMATERIAL_BUILDER_HPP_INCLUDED

#include "node.hpp"
#include "builder_tools.hpp"

namespace o3engine {
namespace nodmaterial {

	//! Builder that will process a node structure and produce a GLSL program.
	class ProgramBuilder {
	public:

		//! Initialize builder on the root
		ProgramBuilder(Node * proot);

		//! Process structure and build program
		bool build();

		//! Check if program is built
		bool isBuilt() const{
			return m_built;
		}

		//! Get produced vertex source
		const std::string & getVertexSource() const;

		//! Get produces fragment source
		const std::string & getFragmentSource() const;

	protected:

		//! Flag if program is built
		bool m_built;

		//! Vertex shader produced source code
		std::string m_vert_source;

		//! Fragment shader produced source code;
		std::string m_frag_source;

		//! Type definition of container with all nodes
		typedef std::map<std::string, Node * > nodes_container_type;

		//! A container with all chained nodes
		nodes_container_type m_nodes;

		//! Root node to use for building
		Node * m_root_node;

		//! Traverse all node connections and gather nodes
		void gatherChainedNodes(Node * pnode);

		//! Traverse all node connections and gather static code
		void gatherStaticCode(std::string & vert_static_source, std::string & frag_static_source);

		//! Traverse all node connections and gather generated code
		void gatherExecutedCode(std::string & vert_source, std::string & fragc_source);
	};
}
}


#endif
