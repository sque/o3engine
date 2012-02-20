#ifndef OGL_TEXTURE_HPP_INCLUDED
#define OGL_TEXTURE_HPP_INCLUDED
#include "./../prereqs.hpp"
#include "./exception.hpp"

namespace o3engine {
namespace ogl {

	/**
	 * @remarks non-copiable, non-inheritable
	 */
	class Texture {
	public:

		enum class tex_type {
			TEX_1D = GL_TEXTURE_1D,
			TEX_2D = GL_TEXTURE_2D,
			TEX_3D = GL_TEXTURE_3D,
			TEX_CUBEMAP = GL_TEXTURE_CUBE_MAP
		};

		enum class filter_type {
			NEAREST = GL_NEAREST,
			LINEAR = GL_LINEAR,
			NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
			LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
			NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
			LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
		};

		enum class param_type {

		};

		Texture(const Texture &) = delete;
		Texture& operator=(const Texture &) = delete;

		// Generate one texture
		Texture(const tex_type & type);

		~Texture();

		inline GLint name() const {
			return m_gl_name;
		}

		inline const tex_type & type() const {
			return m_tex_type;
		}

		inline const get_param(param_type type) {

		}

		inline void bind() const {
			::glBindTexture((GLenum)type(), name());
		}

	protected:
		//! Generic initialize function
		void initialize();

		//! OpenGL texture type
		tex_type m_tex_type;

		//! OpenGL name
		GLint m_gl_name;
	};
}
}

#endif
