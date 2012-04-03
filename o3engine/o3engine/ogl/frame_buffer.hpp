#ifndef OGL_FRAME_BUFFER_HPP_INCLUDED
#define OGL_FRAME_BUFFER_HPP_INCLUDED

#include "./base.hpp"
#include "./render_buffer.hpp"
#include "./texture.hpp"

namespace ogl {

	/**
	 * Frame buffer object
	 */
	class frame_buffer :
		public named_object<GLuint>{
	public:

		//! Create and allocate one framebuffer
		frame_buffer(frame_buffer_target target = frame_buffer_target::DRAW);

		//! Delete this framebuffer
		~frame_buffer();

		frame_buffer(const frame_buffer &) = delete;
		frame_buffer & operator=(const frame_buffer &) = delete;

		//! Bind as framebuffer on its defined target
		void bind() const;

		//! Get target if this frame buffer
		inline frame_buffer_target target() const {
			return m_target;
		}

		//! Get current window default framebuffer
		static const frame_buffer & window_default();

		//! Query status of active framebuffer
		static frame_buffer_status status(frame_buffer_target target);

		//! Get status of this framebuffer
		frame_buffer_status status() const;

		//! Check if this framebuffer is complete
		bool is_complete() const {
			bind();
			return (status(target()) == frame_buffer_status::COMPLETE);
		}

		void attach_render_buffer(frame_buffer_attachment attachment_point, render_buffer & rb);

		void detach_render_buffer(frame_buffer_attachment attachment_point, render_buffer & rb);

		void attach_texture(frame_buffer_attachment attachment_point, texture & tex, int level);

		void attach_texture(frame_buffer_attachment attachment_point, texture & tex, int level, tex2d_update_target tex_target, int layer = 0);

		void read_pixels(int x, int y, size_t width, size_t height, pixel_data_format format, fbo_pixel_type pix_type, void * dst) const;

	protected:
		static frame_buffer * ms_window_fbo;

		frame_buffer(name_type name, frame_buffer_target target);

		frame_buffer_target m_target;
	};
}


#endif
