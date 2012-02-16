#ifndef SHADEROBJECT_HPP_
#define SHADEROBJECT_HPP_

#include "../prereqs.hpp"
namespace o3engine{
namespace ogl {

	class CompiledShader {
	public:

		CompiledShader(GLint gl_name):
			m_gl_name(gl_name){
		}

		inline GLint name() const {
			return m_gl_name;
		}
	protected:
		GLint m_gl_name;
	};
}
}
#endif
