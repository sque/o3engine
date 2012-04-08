#ifndef OGL_TEXTURE_HPP_INCLUDED
#define OGL_TEXTURE_HPP_INCLUDED
#include "./base.hpp"

namespace ogl {

	/**
	 * @remarks non-copiable, non-inheritable
	 */
	class texture :
		public named_object<GLuint>{
	public:

		enum class param_type {
			BASE_LEVEL = GL_TEXTURE_BASE_LEVEL,
			BORDER_COLOR = GL_TEXTURE_BORDER_COLOR,
			COMPARE_FUNC = GL_TEXTURE_COMPARE_FUNC,
			COMPARE_MODE = GL_TEXTURE_COMPARE_MODE,
			LOD_BIAS = GL_TEXTURE_LOD_BIAS,
			MIN_FILTER = GL_TEXTURE_MIN_FILTER,
			MAG_FILTER = GL_TEXTURE_MAG_FILTER,
			MIN_LOD = GL_TEXTURE_MIN_LOD,
			MAX_LOD = GL_TEXTURE_MAX_LOD,
			MAX_LEVEL = GL_TEXTURE_MAX_LEVEL,
			SWIZZLE_R = GL_TEXTURE_SWIZZLE_R,
			SWIZZLE_G = GL_TEXTURE_SWIZZLE_G,
			SWIZZLE_B = GL_TEXTURE_SWIZZLE_B,
			SWIZZLE_A = GL_TEXTURE_SWIZZLE_A,
			SWIZZLE_RGBA = GL_TEXTURE_SWIZZLE_RGBA,
			WRAP_S = GL_TEXTURE_WRAP_S,
			WRAP_T = GL_TEXTURE_WRAP_T,
			WRAP_R = GL_TEXTURE_WRAP_R
		};

		texture(const texture &) = delete;
		texture& operator=(const texture &) = delete;

		// Generate one texture
		texture(const texture_type & type);

		~texture();

		inline const texture_type & type() const {
			return m_tex_type;
		}

		inline void bind() const {
			::glBindTexture((GLenum)type(), name());
		}

		//! @name Set texture parameters
		//! @{


		void set_border_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

		void set_compare_func(compare_func cf);
		void set_compare_mode(compare_mode cm);

		void set_lod_bias(GLfloat bias);
		void set_min_filter(min_filter_type mf);
		void set_mag_filter(mag_filter_type mf);

		void set_min_lod(GLfloat lod);
		void set_max_lod(GLfloat lod);

		void set_base_level(GLint lvl);
		void set_max_level(GLint lvl);

		void set_swizzle(swizzle_type r, swizzle_type g, swizzle_type b, swizzle_type a);

		void set_wrap_s(wrap_type ws);
		void set_wrap_t(wrap_type wt);
		void set_wrap_r(wrap_type wr);

		//! @}

		//! @name Get texture parameters
		//! @{ TODO: the rest of the functions
		GLint get_base_level();
		void get_border_color(GLfloat * rgba);
		void get_border_color(GLfloat & r, GLfloat & g, GLfloat & b, GLfloat & a);


		//! @}

		//! glBufferData
		void define_data_2d(tex2d_update_target target,
				GLuint lvl,
				image_format internal_format, size_t width, size_t height, int border,
				pixel_format pix_form, tex_pixel_type pix_type, const void * pdata);

		//! glBufferSubData
		void update_subdata(size_t offset, size_t size, void * pdata);

		//! Generate mipmaps
		void generate_mipmaps();

	protected:
		//! Generic initialize function
		void initialize();

		//! OpenGL texture type
		texture_type m_tex_type;

		inline void set_parami(param_type param, GLint val) {
			bind();
			::glTexParameteri((GLenum)type(), (GLenum)param, (GLint)val);

		}

		inline void set_paramf(param_type param, GLfloat val) {
			bind();
			::glTexParameteri((GLenum)type(), (GLenum)param, (GLfloat)val);
		}

		inline void set_paramiv(param_type param, GLint * val) {
			bind();
			::glTexParameteriv((GLenum)type(), (GLenum)param, val);
		}

		inline void set_paramfv(param_type param, GLfloat * val) {
			bind();
			::glTexParameterfv((GLenum)type(), (GLenum)param, val);
		}

		inline GLint get_parami(param_type param) {
			bind();
			GLint val;
			::glGetTexParameteriv((GLenum)type(), (GLenum)param, &val);
			return val;
		}

		inline void get_paramiv(param_type param, GLint * pval) {
			bind();
			::glGetTexParameteriv((GLenum)type(), (GLenum)param, pval);
		}

		inline GLfloat get_paramf(param_type param) {
			bind();
			GLfloat val;
			::glGetTexParameterfv((GLenum)type(), (GLenum)param, &val);
			return val;
		}

		inline void get_paramfv(param_type param, GLfloat * pval) {
			bind();
			::glGetTexParameterfv((GLenum)type(), (GLenum)param, pval);
		}
	};
}

#endif
