#ifndef O3ENGINE_MATERILIZER_NODE_HPP_INCLUDED
#define O3ENGINE_MATERILIZER_NODE_HPP_INCLUDED

#include "socket.hpp"

namespace o3engine {
namespace materilizer {

	//! A node in materilizer system
	class Node {
	public:
		//! Container of input sockets
		typedef std::map<std::string, InputSocket *> inputsockets_container_type;

		//! Container of output sockets
		typedef std::map<std::string, OutputSocket *> outputsockets_container_type;

		//! Constructor
		Node(const std::string & name) :
			m_name(name) {
		}

		//! Inheritable
		virtual ~Node();

		//! Get the name of this node
		const std::string & getName() const {
			return m_name;
		}

		//! Get input sockets
		inputsockets_container_type & getInputSockets(){
			return m_input_sockets;
		}

		//! Get a specific input socket
		InputSocket * getInputSocket(const std::string & name){
			return m_input_sockets.at(name);
		}

		//! Check if there is an input socket with specific name
		bool hasInputSocket(const std::string & name) const {
			return m_input_sockets.find(name) != m_input_sockets.end();
		}

		//! Get output sockets
		outputsockets_container_type & getOutputSockets(){
			return m_output_sockets;
		}

		//! Get specific output sockets
		OutputSocket * getOutputSocket(const std::string & name){
			return m_output_sockets.at(name);
		}

		//! Check if there is an output socket with specific name
		bool hasOutputSocket(const std::string & name) const {
			return m_output_sockets.find(name) != m_output_sockets.end();
		}

		//! Get GLSL source code that must be linked statically with final program
		virtual std::string getStaticCode(ogl::shader_type type) = 0;

		//! Get GLSL source code to be executed in the main loop
		virtual std::string getExecutedCode(ogl::shader_type type) = 0;

		//! Get GLSL reference code for specific output
		virtual std::string getOutputSocketReference(ogl::shader_type type, const std::string & socket_name) = 0;
	protected:

		template<Socket::ValueType value_type, class DefaultType>
		void addInputSocket(const std::string & name, const DefaultType & def_value) {
			if (m_input_sockets.find(name) != m_input_sockets.end())
				throw std::invalid_argument("Node::addInputSocket() each input socket must have unique name");
			m_input_sockets[name]= new InputSocket(name, value_type, this, def_value);
		}

		//! Add an output socket
		template<Socket::ValueType value_type>
		void addOutputSocket(const std::string & name) {
			if (m_output_sockets.find(name) != m_output_sockets.end())
				throw std::invalid_argument("Node::addOutputSocket() each input socket must have unique name");
			m_output_sockets[name]= new OutputSocket(name, value_type, this);
		}

	private:

		//! Name of this node
		std::string m_name;

		//! List with all input sockets
		inputsockets_container_type m_input_sockets;

		//! List with all output sockets
		outputsockets_container_type m_output_sockets;
	};
}
}


#endif
