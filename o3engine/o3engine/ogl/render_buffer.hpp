#ifndef OGL_RENDER_BUFFER_HPP_INCLUDED
#define OGL_RENDER_BUFFER_HPP_INCLUDED

#include "./base.hpp"
#include "./exception.hpp"
namespace ogl {

	class render_buffer :
		public named_object<GLuint>{
	public:
		render_buffer();
		~render_buffer();

		render_buffer(const render_buffer &) = delete;
		render_buffer & operator=(const render_buffer &) = delete;

		void bind();

		void define_storage(image_rendable_format internal_format, size_t width, size_t height, size_t samples = 0) throw(gl_error);
	};
}

#endif
