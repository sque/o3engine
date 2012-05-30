#ifndef O3ENGINE_NODMATERIAL_UNIQUENODE_HPP_INCLUDED
#define O3ENGINE_NODMATERIAL_UNIQUENODE_HPP_INCLUDED

#include "node.hpp"
#include "nodecontainer.hpp"

namespace o3engine {
namespace nodmaterial {

	//! Abstract node that will assert that there is only one instance of this node type per material
	template<class Derivative>
	class UniqueNode : public Node{
	public:
		//! Construct a new texture node
		UniqueNode(NodeContainer * powner, const std::string & instance_name, const std::string & type_name):
			Node(powner, instance_name, type_name){
				for(auto & record: powner->getNodes()) {
					if (record.second->getTypeName() == type_name) {
						throw std::runtime_error("There can be only one instance of \"" + type_name + "\" node.");
					}
				}
		}

		virtual ~UniqueNode(){}
	};

}}

#endif
