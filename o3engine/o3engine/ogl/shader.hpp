#ifndef SHADER_HPP_
#define SHADER_HPP_
#include "./../prereqs.hpp"
#include "./exception.hpp"
#include "./compiledshader.hpp"

namespace o3engine {
namespace ogl {

	/**
	 * @remarks non-copiable, non-inheritable
	 */
	class Shader {
	public:

		Shader(const Shader &) = delete;
		Shader& operator=(const Shader &) = delete;

		//! Construct from source
		Shader(shader_type type, const string & source);

		~Shader();

		inline GLint name() const {
			return m_gl_name;
		}

		const string & source() const {
			return m_source;
		}

		string & source() {
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

		//! Shader source
		string m_source;

		//! OpenGL name
		GLint m_gl_name;
	};
}
}

#endif
