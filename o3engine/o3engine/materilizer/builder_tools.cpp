#include "./builder_tools.hpp"
#include <boost/format.hpp>

namespace o3engine {
namespace materilizer{
namespace builder {

	std::string output_variable_name(Node * pnode, const std::string & socket_name) {
		if (!pnode->hasOutputSocket(socket_name))
			throw materilizer_build_error("There is no output socket with this name. \n" + socket_name + "\"");
		return pnode->getName() + "_" + socket_name;
	}

	std::string literal(const float & f) {
		return (boost::format("%1%") % f).str();
	}

	std::string literal(const std::int32_t & r) {
		return (boost::format("%1%") % r).str();
	}

	std::string literal(const std::uint32_t & r) {
		return (boost::format("%1%") % r).str();
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

	struct literal_variant_visitor : public boost::static_visitor<std::string> {
		template<class Type>
		std::string operator()(const Type & v) const {
			return literal(v);
		}
	};

	std::string literal(const InputSocket::default_variant_type & vt) {
		return boost::apply_visitor(literal_variant_visitor(), vt);
	}

	std::string variable_type(Socket::ValueType type) {
		switch(type) {
		case Socket::ValueType::Float:
			return "float";
		case Socket::ValueType::Int:
			return "int";
		case Socket::ValueType::Uint:
			return "uint";
		case Socket::ValueType::Vec3:
			return "vec3";
		case Socket::ValueType::Vec4:
			return "vec4";
		case Socket::ValueType::Vec2:
			return "vec2";
		case Socket::ValueType::Mat3:
			return "mat3";
		case Socket::ValueType::Mat4:
			return "mat4";
		default:
			return "";
		}
	}


	std::string input_value(ogl::shader_type type, Node * pnode, const std::string & socket_name) {

		// Check if there is actually a socket with this name
		if (!pnode->hasInputSocket(socket_name)) {
			throw materilizer_build_error("There is no output socket with this name. \n" + socket_name + "\"");
		}

		// Check if it is not connected, then return default value
		auto * psocket = pnode->getInputSocket(socket_name);
		if (!psocket->isConnected()) {
			return literal(psocket->getDefaultValue());
		}

		// Else return the value of the foreign node
		return psocket->getConnectedNode()->getOutputSocketReference(
			type,
			psocket->getConnectedSocket()->getName());
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
