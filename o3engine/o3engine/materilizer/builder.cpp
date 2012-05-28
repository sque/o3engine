#include "builder.hpp"

namespace o3engine {
namespace materilizer {
	Builder::Builder(Node * proot) :
	m_root_node(proot){

	}

	void processNode(Node * pnode) {

		//if (has)
	}

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

	//! Gather static code
	void Builder::gatherStaticCode(std::string & vert_static_source, std::string & frag_static_source) {

		// Add node to active
		for(auto & node : m_nodes) {
			vert_static_source += node.second->getStaticCode(ogl::shader_type::VERTEX);
			frag_static_source += node.second->getStaticCode(ogl::shader_type::FRAGMENT);
		}
	}

	//! Gather static code
	void Builder::gatherGeneratedCode(std::string & vert_source, std::string & frag_source) {

		// Add node to active
		for(auto & node : m_nodes) {
			vert_source += node.second->getGeneratedCode(ogl::shader_type::VERTEX);
			frag_source += node.second->getGeneratedCode(ogl::shader_type::FRAGMENT);
		}
	}

	bool Builder::build() {
		// Gather all nodes
		gatherChainedNodes(m_root_node);

		m_vert_source =
			"#version 330\n\n"
			""
			"#depend \"library/scene_parameters.vert\"\n"
			"#depend \"library/light.vert\"\n"
			"#depend \"library/attributes.vert\"\n";

		m_frag_source =
			"#version 330\n\n"
			"out vec4 outColor;\n";

		// static code
		gatherStaticCode(m_vert_source, m_frag_source);

		// Main entry points
		m_vert_source += "void main(){\n"
			" gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * aPositionOs;";
		m_frag_source +="void main(){\n";

		//! Generated code
		gatherGeneratedCode(m_vert_source, m_frag_source);

		//! Main call loop
		m_vert_source += m_root_node->getGeneratedOutputValue(ogl::shader_type::VERTEX, "color");
		m_frag_source +=
			"outColor = " + m_root_node->getGeneratedOutputValue(ogl::shader_type::FRAGMENT, "color") + ";";

		m_vert_source += "\n}\n";
		m_frag_source += "\n}\n";

		return true;
	}


}
}