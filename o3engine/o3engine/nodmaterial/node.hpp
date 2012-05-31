#ifndef O3ENGINE_NODMATERIAL_NODE_HPP_INCLUDED
#define O3ENGINE_NODMATERIAL_NODE_HPP_INCLUDED

#include "socket.hpp"

namespace o3engine {
namespace nodmaterial {

	//! Prototype of container class
	class NodeContainer;

	//! Prototype of program builder
	class ProgramBuilder;

	//! A node in NodMaterial system
	class Node {
	public:
		//! Container of input sockets
		typedef std::map<std::string, InputSocket *> inputsockets_container_type;

		//! Container of output sockets
		typedef std::map<std::string, OutputSocket *> outputsockets_container_type;

		//! Function type holder for predraw function
		typedef std::function<void(void)>  predraw_function_type;

		//! Construct a node
		Node(NodeContainer * powner, const std::string & instance_name, const std::string & type_name);

		//! Inheritable
		virtual ~Node();

		//! Get the name of this node instance
		const std::string & getName() const {
			return m_instance_name;
		}

		//! Get the name of this node type
		const std::string & getTypeName() const {
			return m_type_name;
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

		//! Get a function that must be executing before drawing with this material
		virtual const predraw_function_type getPreDrawFunction(){
			return predraw_function_type();
		};

		//! Executed before starting build process
		virtual void preBuild(ProgramBuilder & pm){}

		//! Executed after build process has finished
		virtual void postBuild(ProgramBuilder & pm){}
	protected:

		//! Add an input socket
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

		//! Get container owner of this now
		NodeContainer * getOwner() {
			return mp_owner;
		}

	private:

		//! Container owner of the node
		NodeContainer * mp_owner;

		//! Name of this node instance
		std::string m_instance_name;

		//! Name of node type
		std::string m_type_name;

		//! List with all input sockets
		inputsockets_container_type m_input_sockets;

		//! List with all output sockets
		outputsockets_container_type m_output_sockets;
	};
}
}


#endif
