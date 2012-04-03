#ifndef OGL_TEXTURE_UNIT_HPP_INCLUDED
#define OGL_TEXTURE_UNIT_HPP_INCLUDED

#include "./base.hpp"
#include "./texture.hpp"

namespace ogl {

	class context;

	class texture_unit_t:
		public named_object<GLenum>{
	public:
		friend class context;

		//! Activate this texture unit (deactivate previous one)
		void activate();

		//! Check if this texture unit is active
		bool is_active() const;

		//! Bind a texture on this unit
		void bind_texture(texture & tex);

		//! Unbind any texture from a specific target
		void unbind_texture(texture_type tex_type);

		/*void bind_sampler(sampler & sampl);

		void unbind_sampler(texture_type);*/

		texture_unit_t(texture_unit_t &) = delete;
		texture_unit_t & operator=(texture_unit_t &) = delete;

	protected:

		texture_unit_t(context & ctx, GLenum name);
		context & m_ctx;
	};
}

#endif
