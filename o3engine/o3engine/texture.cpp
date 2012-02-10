#include "./texture.hpp"

namespace o3engine
{
	// Constructor
	Texture::Texture(const string & name)
		:ManagedObject<TextureManager, string, Texture>(name)
	{
		// Create opengl texture
		glGenTextures(1, &m_gli_texture);
		// Set default parameters
		m_wrap_onS = false;
		m_wrap_onT = false;
		m_use_mipmaps = false;
	}

	// Construct and load an image
	Texture::Texture(const string & name, const string & fname, bool use_mipmaps)
		:ManagedObject<TextureManager, string, Texture>(name)
	{
		// Create opengl texture
		glGenTextures(1, &m_gli_texture);

		// Set default parameters
		m_wrap_onS = false;
		m_wrap_onT = false;
		m_use_mipmaps = false;

		// Load Image
		setImage(Image(fname), m_use_mipmaps);
	}

	// Construct and load an image from memmory
	Texture::Texture(const string & name, const Image & tex_img, bool use_mipmaps)
		:ManagedObject<TextureManager, string, Texture>(name)
	{
		// Create opengl texture
		glGenTextures(1, &m_gli_texture);

		// Set default parameters
		m_wrap_onS = false;
		m_wrap_onT = false;
		m_use_mipmaps = false;

		// Load Image
		setImage(tex_img, m_use_mipmaps);
	}

	// Call opengl to update parameters
	void Texture::_update_texture_parameters()
	{   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
			m_wrap_onS? (GLfloat)GL_REPEAT : (GLfloat)GL_CLAMP );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
			m_wrap_onT? (GLfloat)GL_REPEAT : (GLfloat)GL_CLAMP );
	}

	// Load a picture from file
	bool Texture::setImage(const Image & img, bool use_mipmaps)
	{
		// Save parameter
		m_use_mipmaps = use_mipmaps;

		// select our current texture
		glBindTexture( GL_TEXTURE_2D, m_gli_texture);

		// Clamp / repeat parameters
		_update_texture_parameters();

		// select modulate to mix texture with color for shading
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

		// when texture area is large, bilinear filter the first mipmap
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		if (m_use_mipmaps)
		{
			// when texture area is small, bilinear filter the closest mipmap
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			if (0 != gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.getWidth(), img.getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, img.getDataPtr()))
			{
				printf(">> ERROR texture: unknown failure on building mipmaps!\n");
				return false;
			}
		}
		else
		{
			// when texture area is small, bilinear filter the texture
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

			// Copy only 1st level and no border
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getWidth(), img.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getDataPtr());
		}
		return true;
	}

	Image Texture::downloadImage() {
		GLint width = 0, height = 0;

		glBindTexture(GL_TEXTURE_2D, m_gli_texture);
		glGetTexLevelParameteriv(GL_TEXTURE_2D,	0, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D,	0, GL_TEXTURE_HEIGHT, &height);
		printf("Texture level parameter %d %d \n", width, height);
		Image img(width, height);
		glGetTexImage(
			GL_TEXTURE_2D,
			0,
			GL_BGRA,
			GL_UNSIGNED_BYTE,
			&img.pixel(0,0));

		glBindTexture(GL_TEXTURE_2D, 0);

		return img;
	}
}
