#ifndef O3ENGINE_NODMATERIAL_TIMENODE_HPP_INCLUDED
#define O3ENGINE_NODMATERIAL_TIMENODE_HPP_INCLUDED

#include "uniquenode.hpp"

namespace o3engine {
namespace nodmaterial {

	//! Node to access time
	class TimeNode : public UniqueNode<TimeNode>{
	public:
		//! Construct a new time node
		TimeNode(NodeContainer * powner, const std::string & name);

		virtual std::string getStaticCode(ogl::shader_type type);

		virtual std::string getExecutedCode(ogl::shader_type type);

		virtual std::string getOutputSocketReference(ogl::shader_type type, const std::string & socket_name);

		virtual const Node::predraw_function_type getPreDrawFunction() const;
	};
}
}


#endif
