#ifndef OGL_UNIFORM_BLOCK_HPP_INCLUDED
#define OGL_UNIFORM_BLOCK_HPP_INCLUDED

#include "./base.hpp"

namespace ogl {

class program;

	//! Active uniform block of a program
	class uniform_block :
		public named_object<GLuint>{
	public:
		friend class program;

		//! The name of this block
		const std::string & get_block_name() {
			return m_block_name;
		}

		//! Variable size
		size_t size();

		//! Variable type
		variable_type type();

		//! Bind this block to a binding point
		void bind_to(GLuint point);

		//! Get the point that it was bind to
		GLuint get_binding_point() const;

		//! Get data size
		size_t get_data_size() const;

		//! Get the number of active uniforms
		size_t get_total_active_uniforms() const;

		// TODO: get_active_uniform() it return indices. Can this be translated to uniform locations and thus objects?

		//! Check if block is referenced by vertex shader
		bool is_referenced_by_vertex_shader() const;

		//! Check if block is referenced by fragment shader
		bool is_referenced_by_fragment_shader() const;

		//! Check if block is referenced by geometry shader
		bool is_referenced_by_geometry_shader() const;

		//! Get owner program
		const program & get_program() const {
			return *mp_program;
		}

		//! TODO: gcc 4.7 Implement emplace() inside program instead of adding friend copy
		uniform_block() = default;
		uniform_block(const uniform_block &) = default;
		uniform_block & operator=(const uniform_block &) = default;

	protected:
		//! Constructed only be program
		uniform_block(const program & prog, const std::string & name);

		//! Block name
		std::string m_block_name;

		//! Program that uniform belongs at (TODO: with emplace make it reference not pointer)
		const program * mp_program;

		//! Flag if information has been fetched
		bool m_info_fetched;

		//! Variable size
		size_t m_size;

		//! Variable type;
		variable_type m_type;

		//! Actually request variable information
		void query_info();

		};
}

#endif
