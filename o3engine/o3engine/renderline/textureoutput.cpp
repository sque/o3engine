#include "./textureoutput.hpp"
#include <stdexcept>

namespace o3engine {
namespace RenderLine {

	TextureOutput::TextureOutput(OffScreen & offscreen) :
			Texture("TO BE CHANGED", ogl::texture_type::TEX_2D),
			RenderLine::Output(offscreen.getWidth(), offscreen.getHeight()),
			m_offscreen(offscreen) {

		offscreen.attachSurfaceListener(*this);
/*
		m_use_fbo = GLEW_EXT_framebuffer_object && m_use_fbo;

		if (m_use_fbo) {
			printf("RTT: using fbo...\n");

			// Create fbo
			glGenFramebuffersEXT(1, &m_gli_fbo);

			// Bind to fbo
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_gli_fbo);

			glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT,
					getWidth(), getHeight());

			// Bind texture
			glBindTexture(GL_TEXTURE_2D, m_gli_texture);

			// when texture area is large, bilinear filter the first mipmap
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// when texture area is small, bilinear filter the texture
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			// Initialize texture
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, getWidth(), getHeight(), 0,
					GL_RGBA, GL_UNSIGNED_BYTE, NULL);

			// bind this texture to the current framebuffer obj. as
			// color_attachement_0
			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
					GL_TEXTURE_2D, m_gli_texture, 0);

			//'unbind' the frambuffer object, so subsequent drawing ops are not
			// drawn into the FBO.
			// '0' means "windowing system provided framebuffer
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		} else {
			// Allocate space and disable mipmaps
			setImage(Image(getWidth(), getHeight(), Color::MAGENTA), false);
		}*/
	}

	TextureOutput::~TextureOutput() {
		if (m_use_fbo)
			glDeleteFramebuffersEXT(1, &m_gli_fbo);
	}

	void TextureOutput::render() {
		/*//std::cout << "Texture rendering\n";
		if (m_use_fbo) {
			// Bind to back fbo
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_gli_fbo);

			// create viewport
			glViewport(0, 0, getWidth(), getHeight());

			// Set clear color to offscreen's one
			glClearColor(m_offscreen.getBackColor());

			// Clear frame buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			renderNext();

			// 'unbind' the FBO. things will now be drawn to screen as usual
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		} else {
			glViewport(0, 0, getWidth(), getHeight());

			renderNext();

			// Bind to output texture
			glBindTexture(GL_TEXTURE_2D, m_gli_texture);

			// Copy rendered frame to texture
			glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 128, 128, 0);

			// Set clear color to offscreen's one
			glClearColor(m_offscreen.getBackColor());

			// Clear everything
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Disable texturing
			glBindTexture(GL_TEXTURE_2D, 0);
		}*/
	}

	void TextureOutput::onSurfaceResized(int old_width, int old_height,
			int new_width, int new_height) {
		throw new logic_error("Cannot change size a texture surface!");
	}

}
}
