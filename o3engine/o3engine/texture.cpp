#include "./texture.hpp"

namespace o3engine
{
	// Constructor
	Texture::Texture(const string & name, ogl::texture_type type)
		:ManagedObject<TextureManager, string, Texture>(name),
		 mp_gl_texture(new ogl::texture(type)) {
	}

	//! Work on existing opengl texture
	Texture::Texture(const string & name, ogl::texture * ptexture)
		:ManagedObject<TextureManager, string, Texture>(name),
		mp_gl_texture(ptexture) {
	}

	Texture::~Texture(){
		delete mp_gl_texture;
	}

	// Load a picture from file
	bool Texture::uploadImage(const Image & img, bool build_mipmap)	{

		// This is only for 2d loading
		assert(mp_gl_texture->type() == ogl::texture_type::TEX_2D);
		mp_gl_texture->define_data_2d(
				ogl::tex2d_update_target::TEX_2D,
				0,
				ogl::image_format::RGBA,
				img.getWidth(),
				img.getHeight(),
				0,
				ogl::pixel_format::RGBA,
				ogl::tex_pixel_type::UNSIGNED_BYTE,
				img.getDataPtr());

		mp_gl_texture->set_mag_filter(ogl::mag_filter_type::LINEAR);

		if (build_mipmap) {
			mp_gl_texture->generate_mipmaps();
			mp_gl_texture->set_min_filter(ogl::min_filter_type::LINEAR_MIPMAP_NEAREST);
		} else {
			mp_gl_texture->set_min_filter(ogl::min_filter_type::LINEAR);
		}
		return true;
	}

	Image Texture::downloadImage() {
		/*GLint width = 0, height = 0;

		mp_gl_texture->
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

		return img;*/
		//TODO
	}
}
