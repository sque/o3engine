#include "./vertex_array.hpp"
#include <assert.h>

namespace ogl {

	vertex_attrib_array::vertex_attrib_array(const vertex_array * pvao, GLuint index) :
		mp_vao(pvao),
		m_attr_index(index){
	}

	void vertex_attrib_array::enable(){
		mp_vao->bind();
		::glEnableVertexAttribArray(index());
	}

	void vertex_attrib_array::disable(){
		mp_vao->bind();
		::glDisableVertexAttribArray(index());
	}

	bool vertex_attrib_array::is_enabled() const{
		mp_vao->bind();
		return gl_get_wrapper<bool>(glGetVertexAttribiv, index(), param_type::ENABLED);
	}

	void vertex_attrib_array::set_pointerf(const buffer & bo, GLint vector_size, attribf_data_type bo_type, size_t stride, size_t offset) {
		assert(bo.type() == buffer_type::ARRAY);
		bo.bind();
		mp_vao->bind();
		::glVertexAttribPointer(index(), vector_size, (GLenum)bo_type, GL_FALSE, stride, (void*)offset);
	}

	void vertex_attrib_array::set_pointeri(const buffer & bo, GLint vector_size, attribf_data_type bo_type, size_t stride, size_t offset) {
		assert(bo.type() == buffer_type::ARRAY);
		bo.bind();
		mp_vao->bind();
		::glVertexAttribIPointer(index(), vector_size, (GLenum)bo_type, stride, (void*)offset);
	}

	void vertex_attrib_array::set_pointerl(const buffer & bo, GLint vector_size, attribf_data_type bo_type, size_t stride, size_t offset) {
		assert(bo.type() == buffer_type::ARRAY);
		bo.bind();
		mp_vao->bind();
		::glVertexAttribIPointer(index(), vector_size, (GLenum)bo_type, stride, (void*)offset);
	}

	vertex_array::vertex_array() {
		::glGenVertexArrays(1, &m_gl_name);
	}

	vertex_array::~vertex_array() {
		if (::glIsVertexArray(m_gl_name)) {
			::glDeleteVertexArrays(1, &m_gl_name);
		}
	}

	vertex_attrib_array & vertex_array::get_attrib(GLuint index) {
		attribs_type::iterator it = m_attribs.find(index);

		if (it == m_attribs.end()) {
			// Create new object
			m_attribs[index] = vertex_attrib_array(this, index);
		}
		return m_attribs[index];
	}

	void vertex_array::draw(primitive_type mode, GLint first, GLint count) {
		bind();
		::glDrawArrays((GLenum)mode, first, count);
	}

	void vertex_array::draw_elements(primitive_type mode, GLint count, const GLubyte * pindices) {
		bind();
		::glDrawElements((GLenum)mode, count, GL_UNSIGNED_BYTE, pindices);
	}

	void vertex_array::draw_elements(primitive_type mode, GLint count, const GLushort * pindices) {
		bind();
		::glDrawElements((GLenum)mode, count, GL_UNSIGNED_SHORT, pindices);
	}

	void vertex_array::draw_elements(primitive_type mode, GLint count, const GLuint * pindices) {
		bind();
		::glDrawElements((GLenum)mode, count, GL_UNSIGNED_INT, pindices);
	}

	void vertex_array::draw_elements(primitive_type mode, GLint count, const buffer & elem_array, elements_type type) {
		bind();
		elem_array.bind();
		::glDrawElements((GLenum)mode, count, (GLenum)type, nullptr);
	}

	void vertex_array::draw_multiple(primitive_type mode, GLint first, GLint count, GLint instances) {
		bind();
		::glDrawArraysInstanced((GLenum)mode, first, count, instances);
	}

	void vertex_array::draw_elements_multiple(primitive_type mode, GLint count, const GLubyte * pindices, GLint instances) {
		bind();
		::glDrawElementsInstanced((GLenum)mode, count, GL_UNSIGNED_BYTE, pindices, instances);
	}

	void vertex_array::draw_elements_multiple(primitive_type mode, GLint count, const GLushort * pindices, GLint instances) {
		bind();
		::glDrawElementsInstanced((GLenum)mode, count, GL_UNSIGNED_SHORT, pindices, instances);
	}

	void vertex_array::draw_elements_multiple(primitive_type mode, GLint count, const GLuint * pindices, GLint instances) {
		bind();
		::glDrawElementsInstanced((GLenum)mode, count, GL_UNSIGNED_INT, pindices, instances);
	}

}
