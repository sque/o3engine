#ifndef O3ENGINE_NODMATERIAL_UNIQUENODE_HPP_INCLUDED
#define O3ENGINE_NODMATERIAL_UNIQUENODE_HPP_INCLUDED

#include "node.hpp"

namespace o3engine {
namespace nodmaterial {

	//! Abstract node that will return always the same object
	template<class Derivative>
	class UniqueNode : public Node{
	public:
		//! Construct a new texture node
		UniqueNode(const std::string & name);

	};

}}

#endif
