#ifndef O3ENGINE_MATERILIZER_NODE_HPP_INCLUDED
#define O3ENGINE_MATERILIZER_NODE_HPP_INCLUDED

#include "connector.hpp"

namespace o3engine {
namespace materilizer {

	//! A node in materilizer system
	class Node {
	public:
		//! Container of Input connectors
		typedef std::map<std::string, InputConnector *> inputconnectors_container_type;

		//! Container of Output connectors
		typedef std::map<std::string, OutputConnector *> outputconnectors_container_type;

		//! Constructor
		Node(const std::string & name) :
			m_name(name) {
		}

		//! Inheritable
		virtual ~Node(){}

		//! Get the name of this node
		const std::string & getName() const {
			return m_name;
		}

		//! Get input connectors
		inputconnectors_container_type & getInputConnectors(){
			return m_input_connectors;
		}

		//! Get input connector
		InputConnector * getInputConnector(const std::string & name){
			return m_input_connectors[name];
		}

		//! Get output connectors
		outputconnectors_container_type & getOutputConnectors(){
			return m_output_connectors;
		}

		//! Get output connector
		OutputConnector * getOutputConnector(const std::string & name){
			return m_output_connectors[name];
		}

		//! Get source code that must be linked statically with final program
		virtual std::string getStaticCode(ogl::shader_type type) = 0;

		//! Get source code to generate output variables
		virtual std::string getGeneratedCode(ogl::shader_type type) = 0;

		//! Get generated output value
		virtual std::string getGeneratedOutputValue(ogl::shader_type type, const std::string & connector_name){};
	protected:

		//! Add an input connector
		void addInputConnector(const std::string & name, Connector::ValueType value_type) {
			if (m_input_connectors.find(name) != m_input_connectors.end())
				throw std::invalid_argument("Node::addInputConnector() each input connector must have unique name");
			m_input_connectors[name]= new InputConnector(name, value_type, this);
		}

		//! Add an output connector
		void addOutputConnector(const std::string & name, Connector::ValueType value_type) {
			if (m_output_connectors.find(name) != m_output_connectors.end())
				throw std::invalid_argument("Node::addOutputConnector() each input connector must have unique name");
			m_output_connectors[name]= new OutputConnector(name, value_type, this);
		}
	private:

		//! Name of this node
		std::string m_name;

		//! List with all input connectors
		inputconnectors_container_type m_input_connectors;

		//! List with all output connectors
		outputconnectors_container_type m_output_connectors;
	};
}
}


#endif
