#include "./shaderprogram.hpp"

namespace o3engine {
namespace ogl{

	ShaderProgram::ShaderProgram(){
		m_gl_name = ::glCreateProgram();
		if (m_gl_name == 0)
			throw new gl_error("Cannot create shader program.");
	}

	void ShaderProgram::attach_shader(const Shader & sh) {
		::glAttachShader(m_gl_name, sh.name());
	}

	int ShaderProgram::get_param(param_type type) const {
		GLint param_val;
		::glGetProgramiv(m_gl_name, (GLenum)type, &param_val);
		return param_val;
	}

	bool ShaderProgram::is_linked() const{
		return (bool)get_param(param_type::LINK_STATUS);
	}

	bool ShaderProgram::is_valid() const {
		return (bool)get_param(param_type::VALIDATE_STATUS);
	}

	std::string ShaderProgram::info_log() const{
		int info_lenght = get_param(param_type::INFO_LOG_LENGTH);

		// Read error
		std::string info_log(info_lenght, '\0');
		glGetProgramInfoLog(m_gl_name, info_lenght, &info_lenght, &info_log[0]);
		return info_log;
	}

	void ShaderProgram::link() throw(link_error){
		::glLinkProgram(m_gl_name);
		if (!is_linked()) {
			throw new link_error(info_log());
		}
	}

	void ShaderProgram::validate(){
		::glValidateProgram(m_gl_name);
		if (!is_valid()) {
			throw new link_error(info_log()); // TODO: another exception class
		}
	}
}
}
