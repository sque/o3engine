#include "./uniform_block.hpp"
#include "./program.hpp"

namespace ogl {

uniform_block::uniform_block(const program & prog, const std::string & name):
	m_block_name(name),
	mp_program(&prog),
	m_info_fetched(false){

	m_gl_name = ::glGetUniformBlockIndex(mp_program->name(), m_block_name.c_str());
	if (m_gl_name == GL_INVALID_INDEX) {
		gl_error(glGetError(), std::string("Cannot get ") + m_block_name + " uniform block.");
	}
}

void uniform_block::bind_to(GLuint point) {
	glUniformBlockBinding(mp_program->name(), name(), point);
}

template<class Ret>
Ret _uniform_block_get_param(const uniform_block & block, uniform_block_param param) {
	GLint bpoint;
	glGetActiveUniformBlockiv(block.get_program().name(), block.name(), (GLenum)param, &bpoint);
	return static_cast<Ret>(bpoint);
}

GLuint uniform_block::get_binding_point() const {
	return _uniform_block_get_param<GLuint>(*this, uniform_block_param::BINDING);
}

size_t uniform_block::get_data_size() const {
	return _uniform_block_get_param<size_t>(*this, uniform_block_param::DATA_SIZE);
}

size_t uniform_block::get_total_active_uniforms() const {
	return _uniform_block_get_param<size_t>(*this, uniform_block_param::ACTIVE_UNIFORMS);
}

bool uniform_block::is_referenced_by_vertex_shader() const {
	return _uniform_block_get_param<bool>(*this, uniform_block_param::REFERENCED_BY_VERTEX_SHADER);
}

bool uniform_block::is_referenced_by_fragment_shader() const {
	return _uniform_block_get_param<bool>(*this, uniform_block_param::REFERENCED_BY_FRAGMENT_SHADER);
}

bool uniform_block::is_referenced_by_geometry_shader() const {
	return _uniform_block_get_param<bool>(*this, uniform_block_param::REFERENCED_BY_GEOMETRY_SHADER);
}

}
