#include "./texture.hpp"
#include "./exception.hpp"

namespace ogl{

	// Generate one texture
	texture::texture(const texture_type & type):
		m_tex_type(type){
		::glGenTextures(1, &m_gl_name);

		gl_error_checkpoint("glGenTextures failed. ");
	}

	texture::~texture() {
		if (glIsTexture(name()))
			glDeleteTextures(1, &m_gl_name);
	}


	void texture::set_base_level(GLint lvl) {
		set_parami(param_type::MIN_FILTER, lvl);
	}

	void texture::set_border_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
		GLfloat colors[4] = {b, g, r, a};
		set_paramfv(param_type::BORDER_COLOR, colors);
	}

	void texture::set_compare_func(compare_func cf) {
		set_parami(param_type::COMPARE_FUNC, (GLint)cf);
	}

	void texture::set_compare_mode(compare_mode cm) {
		set_parami(param_type::COMPARE_MODE, (GLint)cm);
	}

	void texture::set_lod_bias(GLfloat bias) {
		set_paramf(param_type::LOD_BIAS, bias);
	}

	void texture::set_min_filter(min_filter_type mf) {
		set_parami(param_type::MIN_FILTER, (GLint)mf);
	}

	void texture::set_mag_filter(mag_filter_type mf) {
		set_parami(param_type::MAG_FILTER, (GLint)mf);
	}

	void texture::set_min_lod(GLfloat lvl) {
		set_paramf(param_type::MIN_LOD, lvl);
	}

	void texture::set_max_lod(GLfloat lvl) {
		set_paramf(param_type::MIN_LOD, lvl);
	}

	void texture::set_max_level(GLint lvl) {
		set_parami(param_type::MAX_LEVEL, lvl);
	}

	void texture::set_swizzle(swizzle_type r, swizzle_type g, swizzle_type b, swizzle_type a) {
		GLint rgba[4] = { (GLint)r, (GLint)g, (GLint)b, (GLint)a};
		set_paramiv(param_type::SWIZZLE_RGBA, rgba);
	}

	void texture::set_wrap_s(wrap_type ws) {
		set_parami(param_type::WRAP_S, (GLint)ws);
	}

	void texture::set_wrap_t(wrap_type wt) {
		set_parami(param_type::WRAP_T, (GLint)wt);
	}

	void texture::set_wrap_r(wrap_type wr) {
		set_parami(param_type::WRAP_R, (GLint)wr);
	}


	GLint texture::get_base_level() {
		return get_parami(param_type::BASE_LEVEL);
	}

	void texture::get_border_color(GLfloat * rgba) {
		get_paramfv(param_type::BORDER_COLOR, rgba);
	}

	void texture::get_border_color(GLfloat & r, GLfloat & g, GLfloat & b, GLfloat & a) {
		GLfloat rgba[4];
		get_border_color(rgba);
		r = rgba[0];
		g = rgba[0];
		b = rgba[0];
		a = rgba[0];
	}

	void texture::define_data_2d(tex2d_update_target target,
			GLuint lvl,
			image_format internal_format,
			size_t width,
			size_t height,
			int border,
			pixel_format pix_form,
			tex_pixel_type pix_type,
			const void * pdata) {

		::glBindTexture((GLenum)type(), name());
		::glTexImage2D((GLenum)target, lvl, (GLint)internal_format, width, height, border, (GLenum)pix_form, (GLenum)pix_type, pdata);
	}

	void texture::generate_mipmaps() {
		::glGenerateMipmap((GLenum)type());
	}
}
