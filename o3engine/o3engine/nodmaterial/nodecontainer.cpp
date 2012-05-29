#include "./nodecontainer.hpp"

namespace o3engine {
namespace nodmaterial {

NodeContainer::NodeContainer() {

}

NodeContainer::~NodeContainer() {

	// Delete all nodes
	for(auto & record : m_nodes ) {
		delete record.second;
	}
}

}
}
