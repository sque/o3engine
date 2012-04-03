#include "./texture_unit.hpp"
#include "./context.hpp"

namespace ogl {

	texture_unit_t::texture_unit_t(context & ctx, GLenum name) :
		m_ctx(ctx){
		m_gl_name = name;
	}

	//! Activate this texture unit (deactivate previous one)
	void texture_unit_t::activate() {
		glActiveTexture(name());
	}

	//! Check if this texture unit is active
	bool texture_unit_t::is_active() const {
		return m_ctx.get_param_int(context_param_type::ACTIVE_TEXTURE) == (int)name();
	}

	//! Bind a texture on this unit
	void texture_unit_t::bind_texture(texture & tex) {
		activate();
		tex.bind();
	}

	//! Unbind any texture from a specific target
	void texture_unit_t::unbind_texture(texture_type tex_type) {
		activate();
		glBindTexture((GLenum)tex_type, 0);
	}
}
