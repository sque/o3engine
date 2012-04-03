#ifndef OGL_UNIFORM_HPP_INCLUDED
#define OGL_UNIFORM_HPP_INCLUDED

#include "./base.hpp"

namespace ogl {

class program;

	//! Active uniform variable of a program
	class uniform :
		public named_object<GLint>{
	public:
		friend class program;

		const std::string & var_name() {
			return m_var_name;
		}

		//! @{
		//! @name GL like functions

		void set1f(GLfloat v1);
		void set2f(GLfloat v1, GLfloat v2);
		void set2f(const GLfloat * pv, size_t count = 1);
		void set3f(GLfloat v1, GLfloat v2, GLfloat v3);
		void set3f(const GLfloat * pv, size_t count = 1);
		void set4f(GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4);
		void set4f(const GLfloat * pv, size_t count = 1);

		void set1d(GLdouble v1);
		void set2d(GLdouble v1, GLdouble v2);
		void set2d(const GLdouble * pv, size_t count = 1);
		void set3d(GLdouble v1, GLdouble v2, GLdouble v3);
		void set3d(const GLdouble * pv, size_t count = 1);
		void set4d(GLdouble v1, GLdouble v2, GLdouble v3, GLdouble v4);
		void set4d(const GLdouble * pv, size_t count = 1);

		void set1i(GLint v1);
		void set2i(GLint v1, GLint v2);
		void set2i(const GLint * pv, size_t count = 1);
		void set3i(GLint v1, GLint v2, GLint v3);
		void set3i(const GLint * pv, size_t count = 1);
		void set4i(GLint v1, GLint v2, GLint v3, GLint v4);
		void set4i(const GLint * pv, size_t count = 1);

		void set1ui(GLuint v1);
		void set2ui(GLuint v1, GLuint v2);
		void set2ui(const GLuint * pv, size_t count = 1);
		void set3ui(GLuint v1, GLuint v2, GLuint v3);
		void set3ui(const GLuint * pv, size_t count = 1);
		void set4ui(GLuint v1, GLuint v2, GLuint v3, GLuint v4);
		void set4ui(const GLuint * pv, size_t count = 1);

		void setmat2f(const GLfloat *pm, bool transpose = false, size_t count = 1);
		void setmat3f(const GLfloat *pm, bool transpose = false, size_t count = 1);
		void setmat4f(const GLfloat *pm, bool transpose = false, size_t count = 1);
		void setmat2x3f(const GLfloat *pm, bool transpose = false, size_t count = 1);
		void setmat2x4f(const GLfloat *pm, bool transpose = false, size_t count = 1);
		void setmat3x2f(const GLfloat *pm, bool transpose = false, size_t count = 1);
		void setmat3x4f(const GLfloat *pm, bool transpose = false, size_t count = 1);
		void setmat4x2f(const GLfloat *pm, bool transpose = false, size_t count = 1);
		void setmat4x3f(const GLfloat *pm, bool transpose = false, size_t count = 1);

		void setmat2d(const GLdouble *pm, bool transpose = false, size_t count = 1);
		void setmat3d(const GLdouble *pm, bool transpose = false, size_t count = 1);
		void setmat4d(const GLdouble *pm, bool transpose = false, size_t count = 1);
		void setmat2x3d(const GLdouble *pm, bool transpose = false, size_t count = 1);
		void setmat2x4d(const GLdouble *pm, bool transpose = false, size_t count = 1);
		void setmat3x2d(const GLdouble *pm, bool transpose = false, size_t count = 1);
		void setmat3x4d(const GLdouble *pm, bool transpose = false, size_t count = 1);
		void setmat4x2d(const GLdouble *pm, bool transpose = false, size_t count = 1);
		void setmat4x3d(const GLdouble *pm, bool transpose = false, size_t count = 1);

		//! Variable size
		size_t size();

		//! Variable type
		variable_type type();

		//! @}

		//! TODO: gcc 4.7 Implement emplace() inside program instead of adding friend copy
		uniform() = default;
		uniform(const uniform &) = default;
		uniform & operator=(const uniform &) = default;

	protected:
		//! Constructed only be program
		uniform(const program & prog, const std::string & name);

		//! Variable name
		std::string m_var_name;

		//! Program that uniform belongs at (TODO: with emplace make it reference not pointer)
		const program * mp_program;

		//! Flag if information has been fetched
		bool m_info_fetched;

		//! Variable size
		size_t m_size;

		//! Variable type;
		variable_type m_type;

		//! Actually request variable information
		void query_info();

	};
}

#endif
