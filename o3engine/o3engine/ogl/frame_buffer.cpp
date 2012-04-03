#include "./frame_buffer.hpp"

namespace ogl{

	frame_buffer::frame_buffer(frame_buffer_target target) :
	m_target(target){
		::glGenFramebuffers(1, &m_gl_name);
		gl_error_checkpoint("glGenFramebuffers failed. ");
	}

	frame_buffer::frame_buffer(name_type name, frame_buffer_target target) :
		m_target(target){
		m_gl_name = name;
	}

	frame_buffer::~frame_buffer() {
		if (::glIsFramebuffer(name()))
			::glDeleteFramebuffers(1, &m_gl_name);
	}

	void frame_buffer::bind() const{
		::glBindFramebuffer((GLenum)target(), name());
	}

	frame_buffer_status frame_buffer::status(frame_buffer_target target){
		return (frame_buffer_status)::glCheckFramebufferStatus((GLenum)target);
	}

	void frame_buffer::attach_render_buffer(frame_buffer_attachment attachment_point, render_buffer & rb) {
		bind();
		::glFramebufferRenderbuffer((GLenum)target(), (GLenum)attachment_point, GL_RENDERBUFFER,  rb.name());
	}

	void frame_buffer::detach_render_buffer(frame_buffer_attachment attachment_point, render_buffer & rb) {
		bind();
	}

	frame_buffer_status frame_buffer::status() const {
		return (frame_buffer_status)::glCheckFramebufferStatus((GLenum)target());
	}

	void frame_buffer::read_pixels(int x, int y, size_t width, size_t height, pixel_data_format format, fbo_pixel_type pix_type, void * dst) const{
		bind();
		::glReadPixels(x, y, width, height, (GLenum)format, (GLenum)pix_type, dst);
	}

	void frame_buffer::attach_texture(frame_buffer_attachment attachment_point, texture & tex, int level) {
		bind();
		::glFramebufferTexture((GLenum)target(), (GLenum)attachment_point, tex.name(), level);
	}

	void frame_buffer::attach_texture(frame_buffer_attachment attachment_point, texture & tex, int level, tex2d_update_target tex_target, int layer) {
		bind();
		if (tex.type() == texture_type::TEX_1D) {
			::glFramebufferTexture1D((GLenum)target(), (GLenum)attachment_point, (GLenum)tex_target, tex.name(), level);
		} else if (tex.type() == texture_type::TEX_2D) {
			::glFramebufferTexture2D((GLenum)target(), (GLenum)attachment_point, (GLenum)tex_target, tex.name(), level);
		} else if (tex.type() == texture_type::TEX_2D) {
			::glFramebufferTexture3D((GLenum)target(), (GLenum)attachment_point, (GLenum)tex_target, tex.name(), level, layer);
		}
	}

	const frame_buffer & frame_buffer::window_default() {
		if (ms_window_fbo == nullptr)
			ms_window_fbo = new frame_buffer(0, frame_buffer_target::DRAW);
		return *ms_window_fbo;
	}

	frame_buffer * frame_buffer::ms_window_fbo = nullptr;
}
