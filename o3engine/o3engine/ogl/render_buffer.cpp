#include "./render_buffer.hpp"

namespace ogl{

	render_buffer::render_buffer() {
		::glGenRenderbuffers(1, &m_gl_name);
		gl_error_checkpoint("glGenRenderbuffers failed. ");
	}

	render_buffer::~render_buffer() {
		if (::glIsRenderbuffer(name())) {
			::glDeleteRenderbuffers(1, &m_gl_name);
		}
	}

	void render_buffer::bind() {
		::glBindRenderbuffer(GL_RENDERBUFFER, name());
	}

	void render_buffer::define_storage(image_rendable_format internal_format, size_t width, size_t height, size_t samples) throw(gl_error) {
		bind();
		::glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, (GLenum)internal_format, width, height);
		GLenum gerr;
		if ((gerr = ::glGetError()) != GL_NO_ERROR) {
			throw gl_error(gerr, "glRenderbufferStorageMultisample failed. ");
		}
	}
}
