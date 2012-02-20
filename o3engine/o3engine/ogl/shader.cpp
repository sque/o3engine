#include "./shader.hpp"
#include "./exception.hpp"
#include <boost/format.hpp>
namespace o3engine {
namespace ogl{

	void Shader::initialize() {
		m_gl_name = ::glCreateShader((GLenum) m_type);
		if (m_gl_name == 0)
			throw new gl_error("Cannot create shader.");
	}

	Shader::Shader(shader_type type, const string & source):
		m_type(type),m_source(source) {
		initialize();
	}

	Shader::~Shader() {
		if (::glIsShader(m_gl_name))
			::glDeleteShader(m_gl_name);
	}

	std::string Shader::info_log() const{
		int info_lenght = 0;
		::glGetShaderiv(m_gl_name, GL_INFO_LOG_LENGTH, &info_lenght);

		// Read error
		std::string info_log(info_lenght, '\0');
		glGetShaderInfoLog(m_gl_name, info_lenght, &info_lenght, &info_log[0]);
		return info_log;
	}

	bool Shader::is_compiled() const {
		GLint is_compiled_flag = 0;
		::glGetShaderiv(m_gl_name, GL_COMPILE_STATUS, &is_compiled_flag);
		return (bool)is_compiled_flag;
	}

	void Shader::compile() throw(compile_error){
		const GLchar * chunks[1] = { m_source.c_str() };
		GLint chunk_sizes[1];
		chunk_sizes[0]= m_source.length();

		// Load source
		::glShaderSource(m_gl_name, 1, chunks, chunk_sizes);

		// Compile shader
		::glCompileShader(m_gl_name);

		// Check status
		if (!is_compiled()) {
			throw compile_error(info_log());
		}
	}
}
}
