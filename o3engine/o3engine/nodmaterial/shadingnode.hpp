#ifndef O3ENGINE_NODMATERIAL_SHADINGNODE_HPP_INCLUDED
#define O3ENGINE_NODMATERIAL_SHADINGNODE_HPP_INCLUDED

#include "node.hpp"

namespace o3engine {
namespace nodmaterial {

	//! Node to implement lighting
	class ShadingNode : public Node{
	public:

		//! Construct a new node with basic lighting
		ShadingNode(NodeContainer * powner, const std::string & name);

		virtual std::string getStaticCode(ogl::shader_type type);

		virtual std::string getExecutedCode(ogl::shader_type type);

		virtual std::string getOutputSocketReference(ogl::shader_type type, const std::string & socket_name);

	};
}
}


#endif
