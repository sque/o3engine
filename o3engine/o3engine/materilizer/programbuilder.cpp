#include "programbuilder.hpp"

namespace o3engine {
namespace materilizer {

	ProgramBuilder::ProgramBuilder(Node * proot) :
		m_built(false),
		m_root_node(proot){

	}

	const std::string & ProgramBuilder::getVertexSource() const {
		if (!isBuilt())
			throw std::runtime_error("ProgramBuilder: use build() before requesting source.");
		return m_vert_source;
	}

	const std::string & ProgramBuilder::getFragmentSource() const {
		if (!isBuilt())
			throw std::runtime_error("ProgramBuilder: use build() before requesting source.");
		return m_frag_source;
	}

	void ProgramBuilder::gatherChainedNodes(Node * pnode) {

		// Add this node to the active chained nodes
		nodes_container_type::iterator it = m_nodes.find(pnode->getName());
		if (it != m_nodes.end()) {
			// Two nodes with the chain with same name, are either the same or synonymous
			if (it->second != pnode)
				throw materilizer_build_error("Found duplicate name \"" + pnode->getName() + "\"");
		}
		m_nodes[pnode->getName()] = pnode;

		// Continue for every chained object
		for(auto & con : pnode->getInputSockets()) {
			if (con.second->isConnected())
				gatherChainedNodes(con.second->getConnectedNode());
		}
	}

	void ProgramBuilder::gatherStaticCode(std::string & vert_static_source, std::string & frag_static_source) {

		// Add node to active
		for(auto & node : m_nodes) {
			vert_static_source += node.second->getStaticCode(ogl::shader_type::VERTEX);
			frag_static_source += node.second->getStaticCode(ogl::shader_type::FRAGMENT);
		}
	}

	void ProgramBuilder::gatherExecutedCode(std::string & vert_source, std::string & frag_source) {

		// Add node to active
		for(auto & node : m_nodes) {
			vert_source += node.second->getExecutedCode(ogl::shader_type::VERTEX);
			frag_source += node.second->getExecutedCode(ogl::shader_type::FRAGMENT);
		}
	}

	bool ProgramBuilder::build() {

		// Gather all nodes
		m_nodes.clear();
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
		gatherExecutedCode(m_vert_source, m_frag_source);

		//! Main call loop
		m_vert_source += m_root_node->getOutputSocketReference(ogl::shader_type::VERTEX, "color");
		m_frag_source +=
			"outColor = " + m_root_node->getOutputSocketReference(ogl::shader_type::FRAGMENT, "color") + ";";

		m_vert_source += "\n}\n";
		m_frag_source += "\n}\n";

		return m_built = true;
	}


}
}
