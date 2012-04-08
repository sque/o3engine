#ifndef O3ENGINE_TEXTURE_HPP_INCLUDED
#define O3ENGINE_TEXTURE_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./singletonmanager.hpp"

// System Libraries
#include <memory.h>
#include <string>

namespace o3engine
{
	//! A handler for opengl textures
	/**
	 * Textures are object saved in memory containing
	 * an image that can be used on 3d objects through materials
	 * @par Class Characteristics
	 * Texture is @ref noncopyable_page, @ref inherit_page and follows the @ref sfn_page
	 */
	class Texture :
		public ManagedObject<TextureManager, std::string, Texture>
	{
	protected:

		//! OpenGL texture object
		ogl::texture * mp_gl_texture;

	public:
		//! Create a new texture
		Texture(const string & name, ogl::texture_type type);

		//! Work on existing opengl texture
		Texture(const string & name, ogl::texture * ptexture);

		// Noncopyable
		Texture(const Texture &) = delete;
		Texture & operator=(const Texture &) = delete;

		//! Virtual destructor to allow inheritance
		virtual ~Texture();

		//! Upload a 2D image to texture (valid only for 2D texture types)
		bool uploadImage(const Image & img, bool build_mipmap = true);

		//! Download image from gpu memory
		Image downloadImage();

		//! Get opengl texture
		ogl::texture & glObject() {
			return *mp_gl_texture;
		}
	};
}

#include "./texturemanager.hpp"
#endif
