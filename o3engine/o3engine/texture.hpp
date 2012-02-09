#ifndef O3ENGINE_TEXTURE_HPP_INCLUDED
#define O3ENGINE_TEXTURE_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./singletonmanager.hpp"

// System Libraries
#include <memory.h>
#include <string>

namespace o3engine
{
	//! A handler of 2D texture
	/**
	    Textures are object saved in memory containing
	    an image that can be used on 3d objects through materials
    @par Class Characteristics
         Texture is @ref noncopyable_page, @ref inherit_page and follows the @ref sfn_page
    */
	class Texture :
		public ManagedObject<TextureManager, std::string, Texture>
	{
    private:
        // Noncopyable
        Texture(const Texture &);
        Texture & operator=(const Texture &);

	protected:
		GLuint m_gli_texture;           //!< Index of in opengl implementation
		bool m_wrap_onS;                //!< Flag if we are wrapping on S
		bool m_wrap_onT;                //!< Flag if we are wrapping on T
		bool m_use_mipmaps; 			//!< Flag if we are using mipmaps

		//!< Call opengl to update parameters
		void _update_texture_parameters();

	public:
		//! Default constructor
		Texture(const string & name);

		//! Virtual destructor to allow inheritance
		inline virtual ~Texture() {   glDeleteTextures(1, &m_gli_texture);  }

		//! Construct and load an image from file
		Texture(const string & name, const string & fname, bool use_mipmaps = true);

		//! Construct and load an image from memory
		Texture(const string & name, const Image & tex_img, bool use_mipmaps = true);

		//! Load a texture from an existing image
		bool setImage(const Image & img, bool _use_mipmaps = true);

		//! Download image from gpu memory
		Image downloadImage();

		//! Set wrap on S axis (Horizontal)
		inline void setWrapOnS(bool wrap_onS)
		    { m_wrap_onS = wrap_onS; _update_texture_parameters(); }

		//! Set wrap on T axis (Vertical)
		inline void setWrapOnT(bool wrap_onT)
		    { m_wrap_onT = wrap_onT; _update_texture_parameters(); }

		//! Get wrap on S axis (Horizontal)
		inline bool getWrapOnS() const { return m_wrap_onS; }

		//! Get wrap on T axis (Vertical)
		inline bool getWrapOnT() const { return m_wrap_onT; }

		//! Check if we are using mipmaps
		inline bool isMipmapsEnabled() const {	return m_use_mipmaps;	}

		//! OpenGL: Use me to glBindTexture2d
		inline void glBind2d()
		    const {    ::glBindTexture(GL_TEXTURE_2D, m_gli_texture);  }
	};
}

#include "./texturemanager.hpp"
#endif
