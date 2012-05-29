#include "geometrynode.hpp"

namespace o3engine {
namespace nodmaterial {

GeometryNode::GeometryNode(NodeContainer * powner, const std::string & name) :
		Node(powner, name, typeid(this).name()){
		addOutputSocket<Socket::ValueType::Vec4>("position");
		addOutputSocket<Socket::ValueType::Vec4>("normal");
		addOutputSocket<Socket::ValueType::Vec4>("tangent");
		addOutputSocket<Socket::ValueType::Vec4>("bitangent");
		addOutputSocket<Socket::ValueType::Vec4>("texcoord0");
		addOutputSocket<Socket::ValueType::Vec4>("texcoord1");
		addOutputSocket<Socket::ValueType::Vec4>("texcoord2");
		addOutputSocket<Socket::ValueType::Vec4>("texcoord3");
		addOutputSocket<Socket::ValueType::Vec4>("texcoord4");
		addOutputSocket<Socket::ValueType::Vec4>("texcoord5");

		m_map_socket_vert_variable["position"] = "aPositionOs";
		m_map_socket_vert_variable["normal"] = "aNormalOs";
		m_map_socket_vert_variable["tangent"] = "aTangentOs";
		m_map_socket_vert_variable["bitangent"] = "aBitangentOs";
		m_map_socket_vert_variable["texcoord0"] = "aTexCoord0Os";
		m_map_socket_vert_variable["texcoord1"] = "aTexCoord1Os";
		m_map_socket_vert_variable["texcoord2"] = "aTexCoord2Os";
		m_map_socket_vert_variable["texcoord3"] = "aTexCoord3Os";
		m_map_socket_vert_variable["texcoord4"] = "aTexCoord4Os";
		m_map_socket_vert_variable["texcoord5"] = "aTexCoord5Os";

		m_map_socket_frag_variable["position"] = "vtPositionOs";
		m_map_socket_frag_variable["normal"] = "vtNormalOs";
		m_map_socket_frag_variable["tangent"] = "vtTangentOs";
		m_map_socket_frag_variable["bitangent"] = "vtBitangentOs";
		m_map_socket_frag_variable["texcoord0"] = "vtTexCoord0Os";
		m_map_socket_frag_variable["texcoord1"] = "vtTexCoord1Os";
		m_map_socket_frag_variable["texcoord2"] = "vtTexCoord2Os";
		m_map_socket_frag_variable["texcoord3"] = "vtTexCoord3Os";
		m_map_socket_frag_variable["texcoord4"] = "vtTexCoord4Os";
		m_map_socket_frag_variable["texcoord5"] = "vtTexCoord5Os";

	}

	std::string GeometryNode::getStaticCode(ogl::shader_type type) {
		std::string code, direction;

		// Set up in/out from vertex to fragment
		switch(type) {
		case ogl::shader_type::VERTEX:
			direction = "out";
			break;
		case ogl::shader_type::FRAGMENT:
			direction = "in";
			break;
		default:
			return "";
		}

		for(auto & record : m_map_socket_frag_variable) {
			code += direction + " vec4 " + record.second + ";\n";
		}
		return code;
	}

	std::string GeometryNode::getExecutedCode(ogl::shader_type type) {
		std::string code;

		switch(type){
		case ogl::shader_type::VERTEX:
			for(auto & record: m_map_socket_vert_variable) {
				code += m_map_socket_frag_variable[record.first] + " = " + record.second + ";\n";
			}
			return code;
		default:
			return "";
		}

	}

	std::string GeometryNode::getOutputSocketReference(ogl::shader_type type, const std::string & socket_name) {
		switch(type) {
		case ogl::shader_type::VERTEX:
			return m_map_socket_vert_variable.at(socket_name);
		case ogl::shader_type::FRAGMENT:
			return m_map_socket_frag_variable.at(socket_name);
		default:
			return "";
		}
	}
}
}
