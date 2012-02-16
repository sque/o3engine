#ifndef O3ENGINE_SHADERPROGRAM_HPP_INCLUDED
#define O3ENGINE_SHADERPROGRAM_HPP_INCLUDED

#include "./../prereqs.hpp"
#include "./shader.hpp"

namespace o3engine {
namespace ogl {
	class ShaderProgram {
	public:
		ShaderProgram(const ShaderProgram &) = delete;
		ShaderProgram & operator=(const ShaderProgram &) = delete;

		ShaderProgram();

		enum class param_type {
			DELETE_STATUS = GL_DELETE_STATUS,
			LINK_STATUS = GL_LINK_STATUS,
			VALIDATE_STATUS = GL_VALIDATE_STATUS,
			INFO_LOG_LENGTH = GL_INFO_LOG_LENGTH,
			ATTACHED_SHADERS = GL_ATTACHED_SHADERS,
			ACTIVE_ATTRIBUTES = GL_ACTIVE_ATTRIBUTES,
			ACTIVE_ATTRIBUTE_MAX_LENGTH = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
			ACTIVE_UNIFORMS = GL_ACTIVE_UNIFORMS,
			ACTIVE_UNIFORM_MAX_LENGTH = GL_ACTIVE_UNIFORM_MAX_LENGTH
		};

		void attach_shader(const Shader & sh);

		void link() throw(link_error);

		int get_param(param_type type) const;

		bool is_linked() const;

		void validate();

		bool is_valid() const;

		std::string info_log() const;

		inline GLint name() const {
			return m_gl_name;
		}


	protected:
		GLint m_gl_name;
	};
}
}


#endif
