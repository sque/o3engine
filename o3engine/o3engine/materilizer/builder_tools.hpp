#ifndef O3ENGINE_BUILD_TOOLS_HPP_INCLUDED
#define O3ENGINE_BUILD_TOOLS_HPP_INCLUDED

#include "node.hpp"
namespace o3engine {
namespace materilizer{

	//! Error while building program
	struct materilizer_build_error : public std::runtime_error {
		materilizer_build_error(const std::string & what) :
			runtime_error(what){
		}
	};

namespace builder {

	bool has_input_connector(Node * node, const std::string & connector_name);

	bool has_output_connector(Node * node, const std::string & connector_name);

	std::string output_variable(Node * node, const std::string & connector_name);

	std::string literal(const Vector2 & r);

	std::string literal(const Vector3 & r);

	std::string literal(const Vector4 & r);

	std::string literal(const Color & r);

	std::string variable_type(Connector::ValueType type);

	std::string input_data_value(ogl::shader_type type, Node * node, const std::string & connector_name);

	std::string func_call(const std::string & func_name, std::initializer_list<std::string> arguments = {});
}}}

#endif
