#ifndef O3ENGINE_NODMATERIAL_BUILDER_HPP_INCLUDED
#define O3ENGINE_NODMATERIAL_BUILDER_HPP_INCLUDED

#include "node.hpp"
#include "builder_tools.hpp"

namespace o3engine {
namespace nodmaterial {

	//! Builder that will process a node structure and produce a GLSL program.
	class ProgramBuilder {
	public:
		//! Type definition of container with all nodes
		typedef std::map<std::string, Node * > nodes_container_type;

		//! Type definition of dynamic build flags
		typedef std::map<std::string, std::string> dynamic_build_flags_container_type;

		//! Initialize builder on the root
		ProgramBuilder(Node * proot);

		//! Process structure and build program
		bool build();

		//! Check if program is built
		bool isBuilt() const{
			return m_built;
		}

		typedef std::vector<Node::predraw_function_type> predraw_functions_type;
		//! Get produced vertex source
		const std::string & getVertexSource() const;

		//! Get produced fragment source
		const std::string & getFragmentSource() const;

		//! Get produced material predraw functions
		const predraw_functions_type getPreDrawFunctions() const;

		//! Get root node that is in build processing
		Node * getRootNode() {
			return m_root_node;
		}

		//! Get all active nodes (that are part of the main chain)
		nodes_container_type & getActiveNodes() {
			return m_nodes;
		}

		//! Access dynamic build flags
		dynamic_build_flags_container_type & getDynamicBuildFlags(){
			return m_dynamic_build_flags;
		}

		//! Get dynamic build flag
		const std::string & getDynamicBuildFlag(const std::string &name, const std::string & def_value){
			if (m_dynamic_build_flags.find(name) == m_dynamic_build_flags.end()) {
				return def_value;
			}
			return m_dynamic_build_flags[name];
		}
	protected:

		//! Flag if program is built
		bool m_built;

		//! Vertex shader produced source code
		std::string m_vert_source;

		//! Fragment shader produced source code;
		std::string m_frag_source;

		//! Predraw functions
		predraw_functions_type m_predraw_functions;

		//! A container with all chained nodes
		nodes_container_type m_nodes;

		//! Root node to use for building
		Node * m_root_node;

		//! Container of dynamic build flags
		dynamic_build_flags_container_type m_dynamic_build_flags;

		//! Traverse all node connections and gather nodes
		void gatherChainedNodes(Node * pnode);

		//! Traverse all chained nodes and gather predraw functions
		void gatherPredrawFunctions();

		//! Traverse all node connections and gather static code
		void gatherStaticCode(std::string & vert_static_source, std::string & frag_static_source);

		//! Traverse all node connections and gather generated code
		void gatherExecutedCode(std::string & vert_source, std::string & fragc_source);
	};
}
}


#endif
