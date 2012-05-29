#ifndef O3ENGINE_MATERILIZER_GEOMETRY_HPP_INCLUDED
#define O3ENGINE_MATERILIZER_GEOMETRY_HPP_INCLUDED

#include "node.hpp"

namespace o3engine {
namespace materilizer {

	//! Node to access geometry object information
	class GeometryNode : public Node{
	public:
		//! Construct a new texture node
		GeometryNode(const std::string & name);

		virtual std::string getStaticCode(ogl::shader_type type);

		virtual std::string getExecutedCode(ogl::shader_type type);

		virtual std::string getOutputSocketReference(ogl::shader_type type, const std::string & socket_name);

	private:

		//! Type definition of mapping
		typedef std::map<std::string, std::string> map_type;

		//! Static mapping of output socket name -> Vertex variable
		map_type m_map_socket_vert_variable;

		//! Static mapping of output socket name -> Fragment variable
		map_type m_map_socket_frag_variable;
	};
}
}


#endif
