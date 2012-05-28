#include "./builder_tools.hpp"
#include <boost/format.hpp>

namespace o3engine {
namespace materilizer{
namespace builder {

	bool has_input_connector(Node * node, const std::string & connector_name) {
		auto & ic = node->getInputConnectors();
		return ic.find(connector_name) != ic.end();
	}

	bool has_output_connector(Node * node, const std::string & connector_name) {
		auto & oc = node->getOutputConnectors();
		return oc.find(connector_name) != oc.end();
	}

	std::string output_variable(Node * node, const std::string & connector_name) {
		if (!has_output_connector(node, connector_name))
			throw materilizer_build_error("There is no output connector with this name. \n" + connector_name + "\"");
		return node->getName() + connector_name;
	}

	std::string literal(const Vector2 & r) {
		return (boost::format("vec3(%1%, %2%)") % r.x % r.y).str();
	}

	std::string literal(const Vector3 & r) {
		return (boost::format("vec3(%1%, %2%, %3%)") % r.x % r.y % r.z).str();
	}

	std::string literal(const Vector4 & r) {
		return (boost::format("vec4(%1%, %2%, %3%, %4%)") % r.x % r.y % r.z % r.w).str();
	}

	std::string literal(const Color & r) {
		return (boost::format("vec4(%1%, %2%, %3%, %4%)") % r.red % r.green % r.blue % r.alpha).str();
	}

	std::string variable_type(Connector::ValueType type) {
		switch(type) {
		case Connector::ValueType::Float:
			return "float";
		case Connector::ValueType::Int:
			return "int";
		case Connector::ValueType::Uint:
			return "uint";
		case Connector::ValueType::Vec3:
			return "vec3";
		case Connector::ValueType::Vec4:
			return "vec4";
		case Connector::ValueType::Vec2:
			return "vec2";
		case Connector::ValueType::Mat3:
			return "mat3";
		case Connector::ValueType::Mat4:
			return "mat4";
		default:
			return "";
		}
	}


	std::string input_data_value(ogl::shader_type type, Node * node, const std::string & connector_name) {
		if (!has_input_connector(node, connector_name))
			throw materilizer_build_error("There is no output connector with this name. \n" + connector_name + "\"");
		return node->getInputConnector(connector_name)->getConnectedNode()->getGeneratedOutputValue(
				type,
				node->getInputConnector(connector_name)->getConnectedSocket()->getName());
	}

	std::string func_call(const std::string & func_name, std::initializer_list<std::string> arguments) {

		// Create arguments string
		std::string str_args;
		str_args.reserve(512);
		for(auto & arg: arguments) {
			str_args += "," + arg;
		}
		str_args = str_args.substr(1);

		return func_name + "(" + str_args + ")";
	}
}}}
