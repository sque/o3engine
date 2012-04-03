#include "./uniform.hpp"
#include "./program.hpp"

namespace ogl {

	uniform::uniform(const program & prog, const std::string & name) :
		m_var_name(name),
		mp_program(&prog),
		m_info_fetched(false){

		m_gl_name = ::glGetUniformLocation(mp_program->name(), m_var_name.c_str());
		if (m_gl_name == -1) {
			gl_error(glGetError(), std::string("Cannot get ") + m_var_name + " uniform variable.");
		}
	}

	void uniform::set1f(GLfloat v1) {
		::glProgramUniform1f(mp_program->name(), name(),v1);
	}
	void uniform::set2f(GLfloat v1, GLfloat v2) {
		::glProgramUniform2f(mp_program->name(), name(), v1, v2);
	}
	void uniform::set2f(const GLfloat * pv, size_t count) {
		::glProgramUniform2fv(mp_program->name(), name(), count, pv);
	}
	void uniform::set3f(GLfloat v1, GLfloat v2, GLfloat v3) {
		::glProgramUniform3f(mp_program->name(), name(), v1, v2 ,v3);
	}
	void uniform::set3f(const GLfloat * pv, size_t count) {
		::glProgramUniform3fv(mp_program->name(), name(), count, pv);
	}
	void uniform::set4f(GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4) {
		::glProgramUniform4f(mp_program->name(), name(), v1, v2, v3 ,v4);
	}
	void uniform::set4f(const GLfloat * pv, size_t count) {
		::glProgramUniform4fv(mp_program->name(), name(), count, pv);
	}

	void uniform::set1d(GLdouble v1) {
		::glProgramUniform1d(mp_program->name(), name(), v1);
	}
	void uniform::set2d(GLdouble v1, GLdouble v2) {
		::glProgramUniform2d(mp_program->name(), name(), v1, v2);
	}
	void uniform::set2d(const GLdouble * pv, size_t count) {
		::glProgramUniform2dv(mp_program->name(), name(), count, pv);
	}
	void uniform::set3d(GLdouble v1, GLdouble v2, GLdouble v3) {
		::glProgramUniform3d(mp_program->name(), name(), v1, v2, v3);
	}
	void uniform::set3d(const GLdouble * pv, size_t count) {
		::glProgramUniform3dv(mp_program->name(), name(), count, pv);
	}
	void uniform::set4d(GLdouble v1, GLdouble v2, GLdouble v3, GLdouble v4) {
		::glProgramUniform4d(mp_program->name(), name(), v1, v2, v3, v4);
	}
	void uniform::set4d(const GLdouble * pv, size_t count) {
		::glProgramUniform4dv(mp_program->name(), name(), count, pv);
	}

	void uniform::set1i(GLint v1) {
		::glProgramUniform1i(mp_program->name(), name(), v1);
	}
	void uniform::set2i(GLint v1, GLint v2) {
		::glProgramUniform2i(mp_program->name(), name(), v1, v2);
	}
	void uniform::set2i(const GLint * pv, size_t count) {
		::glProgramUniform2iv(mp_program->name(), name(), count, pv);
	}
	void uniform::set3i(GLint v1, GLint v2, GLint v3) {
		::glProgramUniform3i(mp_program->name(), name(), v1, v2, v3);
	}
	void uniform::set3i(const GLint * pv, size_t count) {
		::glProgramUniform3iv(mp_program->name(), name(), count, pv);
	}
	void uniform::set4i(GLint v1, GLint v2, GLint v3, GLint v4) {
		::glProgramUniform4i(mp_program->name(), name(), v1, v2, v3, v4);
	}
	void uniform::set4i(const GLint * pv, size_t count) {
		::glProgramUniform4iv(mp_program->name(), name(), count, pv);
	}

	void uniform::set1ui(GLuint v1) {
		::glProgramUniform1ui(mp_program->name(), name(), v1);
	}
	void uniform::set2ui(GLuint v1, GLuint v2) {
		::glProgramUniform2ui(mp_program->name(), name(), v1, v2);
	}
	void uniform::set2ui(const GLuint * pv, size_t count) {
		::glProgramUniform2uiv(mp_program->name(), name(), count, pv);
	}
	void uniform::set3ui(GLuint v1, GLuint v2, GLuint v3) {
		::glProgramUniform3ui(mp_program->name(), name(), v1, v2, v3);
	}
	void uniform::set3ui(const GLuint * pv, size_t count) {
		::glProgramUniform3uiv(mp_program->name(), name(), count, pv);
	}
	void uniform::set4ui(GLuint v1, GLuint v2, GLuint v3, GLuint v4) {
		::glProgramUniform4ui(mp_program->name(), name(), v1, v2, v3, v4);
	}
	void uniform::set4ui(const GLuint * pv, size_t count) {
		::glProgramUniform4uiv(mp_program->name(), name(), count, pv);
	}

	void uniform::setmat2f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix2fv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}
	void uniform::setmat3f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix3fv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}
	void uniform::setmat4f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix4fv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}
	void uniform::setmat2x3f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix2x3fv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}
	void uniform::setmat2x4f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix2x4fv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}
	void uniform::setmat3x2f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix3x2fv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}
	void uniform::setmat3x4f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix3x4fv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}
	void uniform::setmat4x2f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix4x2fv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}
	void uniform::setmat4x3f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix4x3fv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}

	void uniform::setmat2d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix2dv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}
	void uniform::setmat3d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix3dv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}
	void uniform::setmat4d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix4dv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}
	void uniform::setmat2x3d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix2x3dv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}
	void uniform::setmat2x4d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix2x4dv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}
	void uniform::setmat3x2d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix3x2dv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}
	void uniform::setmat3x4d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix3x4dv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}
	void uniform::setmat4x2d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix4x2dv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}
	void uniform::setmat4x3d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix4x3dv(mp_program->name(), name(), count,
				(GLboolean) transpose, pm);
	}

	void uniform::query_info() {

		if (!m_info_fetched) {
			GLint size;
			GLenum type;

			::glGetActiveUniform(mp_program->name(), name(), 0, 0, &size, &type, NULL);

			m_size = size;
			m_type = (variable_type)type;
			m_info_fetched = true;
		}
	}

	//! Variable size
	size_t uniform::size() {
		query_info();
		return m_size;
	}

	//! Variable type
	variable_type uniform::type() {
		query_info();
		return m_type;
	}
}
