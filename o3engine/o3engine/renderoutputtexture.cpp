#include "./renderoutputtexture.hpp"

namespace o3engine
{
	RenderOutputTexture::RenderOutputTexture(const string & name, int width, int height, bool use_fbo)
        :Texture(name),
        RenderOutput(width, height),
        m_use_fbo(use_fbo)
	{
	    m_use_fbo = GLEW_EXT_framebuffer_object && m_use_fbo;

		if (m_use_fbo)
		{
		    printf("RTT: using fbo to implement...");

			// Create fbo
			glGenFramebuffersEXT(1, &m_gli_fbo);

			// Bind to fbo
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_gli_fbo);

			// Bind texture
			glBindTexture(GL_TEXTURE_2D, m_gli_texture);

			// when texture area is large, bilinear filter the first mipmap
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

			// when texture area is small, bilinear filter the texture
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

			// Initialize texture
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0,
						GL_RGBA, GL_UNSIGNED_BYTE,NULL);

			// bind this texture to the current framebuffer obj. as
			// color_attachement_0
			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
				GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_gli_texture, 0);

			//'unbind' the frambuffer object, so subsequent drawing ops are not
		   // drawn into the FBO.
		   // '0' means "windowing system provided framebuffer
		   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		}
		else
		{
			// Allocate space and disable mipmaps
			setImage(Image(m_width, m_height, Color::MAGENTA), false);
		}
	}

	RenderOutputTexture::~RenderOutputTexture()
	{
		if (m_use_fbo)
			glDeleteFramebuffersEXT(1, &m_gli_fbo);
	}

	void RenderOutputTexture::onPreRender()
	{

		if (m_use_fbo)
		{
			// Bind to back fbo
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_gli_fbo);

			// create viewport
			glViewport(0, 0, m_width, m_height);

			// Set clear color to empty
			::glClearColor(0, 0, 0, 0);

			// Clear frame buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		else
		{
			glViewport(0, 0, m_width, m_height);
		}
	}

	void RenderOutputTexture::onPostRender()
	{
		if (m_use_fbo)
		{
			// 'unbind' the FBO. things will now be drawn to screen as usual
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		}
		else
		{
			// Bind to output texture
			glBindTexture(GL_TEXTURE_2D, m_gli_texture);

			// Copy rendered frame to texture
			glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 128, 128, 0);

			// Clear everything
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Disable texturing
			glBindTexture(GL_TEXTURE_2D,0);
		}
	}
}
