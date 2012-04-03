#include "./buffer.hpp"
#include "./exception.hpp"

namespace ogl{


	buffer::buffer(buffer_type type)
		:m_buf_type(type),
		 m_size(0)	 {
		::glGenBuffers(1, &m_gl_name);
		gl_error_checkpoint("glGenBuffers failed.");
	}

	buffer::~buffer() {
		if (::glIsBuffer(m_gl_name)) {
			::glDeleteBuffers(1, &m_gl_name);
		}
	}

	void buffer::define_data(size_t size, void * pdata, buffer_usage_pattern usage) {
		bind();
		m_size = size;
		::glBufferData((GLenum)type(), size, pdata, (GLenum)usage);
	}

	void buffer::update_subdata(size_t offset, size_t size, void * pdata) {
		bind();
		::glBufferSubData((GLenum)type(), offset, size, pdata);
	}

	std::vector<uint8_t> buffer::get_data(size_t offset, size_t size) {
		bind();
		std::vector<uint8_t> buf(size);
		::glGetBufferSubData((GLenum)type(), offset, size, &buf[0]);
		return std::move(buf);
	}

	void * buffer::map_data(buffer_access_type access) {
		bind();
		return ::glMapBuffer((GLenum)type(), (GLenum)access);
	}

	bool buffer::unmap_data() {
		bind();
		return (bool)::glUnmapBuffer((GLenum)type());
	}

	void * buffer::map_data_range(size_t offset, size_t size, map_access_bit access) {
		bind();
		return ::glMapBufferRange((GLenum) type(), offset, size,(GLbitfield)access);
	}

	void buffer::flush_mapped_range(size_t offset, size_t size) {
		bind();
		::glFlushMappedBufferRange((GLenum)type(), offset, size);
	}
}
