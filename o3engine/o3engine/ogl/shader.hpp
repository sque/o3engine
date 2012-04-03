#ifndef OGL_SHADER_HPP_INCLUDED
#define OGL_SHADER_HPP_INCLUDED
#include "./base.hpp"
#include "./exception.hpp"

namespace ogl {

	//! GPU Shader
	/**
	 * @remarks non-copiable, non-inheritable
	 */
	class shader:
		public named_object<GLint> {
	public:

		shader(const shader &) = delete;
		shader& operator=(const shader &) = delete;

		//! Construct from source
		shader(shader_type type, const std::string & source);

		~shader();

		const std::string & source() const {
			return m_source;
		}

		std::string & source() {
			return m_source;
		}

		void compile() throw(compile_error);

		bool is_compiled() const;

		std::string info_log() const;

		const shader_type & type() const{
			return m_type;
		}

	protected:
		//! Generic initialize function
		void initialize();

		shader_type m_type;

		//! shader source
		std::string m_source;
	};

	shader * open_shader_file(shader_type type, std::initializer_list<const std::string> fnames);
}

#endif
