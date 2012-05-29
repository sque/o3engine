#ifndef O3ENGINE_BUILD_TOOLS_HPP_INCLUDED
#define O3ENGINE_BUILD_TOOLS_HPP_INCLUDED

#include "node.hpp"
namespace o3engine {
namespace nodmaterial{

	//! Error while building program
	struct nodmaterial_build_error : public std::runtime_error {
		nodmaterial_build_error(const std::string & what) :
			runtime_error(what){
		}
	};

namespace builder {

	//! Build a unique GLSL variable name
	std::string output_variable_name(Node * pnode, const std::string & socket_name);

	//! Build a float GLSL literal from Float
	std::string literal(const float & f);

	//! Build a int32 GLSL literal from Int32
	std::string literal(const std::int32_t & r);

	//! Build a uint32 GLSL literal from Int32
	std::string literal(const std::uint32_t & r);

	//! Build a vec2 GLSL literal from Vector2
	std::string literal(const Vector2 & r);

	//! Build a vec3 GLSL literal from Vector3
	std::string literal(const Vector3 & r);

	//! Build a vec4 GLSL literal from Vector4
	std::string literal(const Vector4 & r);

	//! Build a vec4 GLSL literal from Color
	std::string literal(const Color & r);

	//! Build a GLSL literal from variant type. Type is resolved at compile time.
	std::string literal(const InputSocket::default_variant_type & vt);

	//! Build a GLSL string of GLSL data type
	std::string variable_type(Socket::ValueType type);

	//! Build a GLSL string that upon execution will return the value from an input socket
	std::string input_value(ogl::shader_type type, Node * node, const std::string & socket_name);

	//! Build a GLSL string that will call a function named func_name with arguments.
	std::string func_call(const std::string & func_name, std::initializer_list<std::string> arguments = {});
}}}

#endif
