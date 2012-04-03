#ifndef OGL_VERTEX_ARRAY_HPP_INCLUDED
#define OGL_VERTEX_ARRAY_HPP_INCLUDED

#include "./base.hpp"
#include "./buffer.hpp"
#include <map>

namespace ogl {

	class vertex_array;

	class vertex_attrib_array {
	public:
		friend class vertex_array;

		enum class param_type {
			BUFFER_BINDING = GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING,
			ENABLED = GL_VERTEX_ATTRIB_ARRAY_ENABLED,
			SIZE = GL_VERTEX_ATTRIB_ARRAY_SIZE,
			STRIDE = GL_VERTEX_ATTRIB_ARRAY_STRIDE,
			TYPE = GL_VERTEX_ATTRIB_ARRAY_TYPE,
			NORMALIZED = GL_VERTEX_ATTRIB_ARRAY_NORMALIZED,
			INTEGER = GL_VERTEX_ATTRIB_ARRAY_INTEGER,
			DIVISOR = GL_VERTEX_ATTRIB_ARRAY_DIVISOR,
			CURRENT = GL_CURRENT_VERTEX_ATTRIB,
		};

		void enable();

		void disable();

		bool is_enabled() const;

		void set_pointerf(const buffer & bo, GLint vector_size, attribf_data_type bo_type, size_t stride = 0, size_t offset = 0);

		void set_pointeri(const buffer & bo, GLint vector_size, attribf_data_type bo_type, size_t stride = 0, size_t offset = 0);

		void set_pointerl(const buffer & bo, GLint vector_size, attribf_data_type bo_type, size_t stride = 0, size_t offset = 0);

		inline GLuint index() const{
			return m_attr_index;
		}

		// TODO: remove when emplace
		vertex_attrib_array(const vertex_attrib_array &) = default;
		vertex_attrib_array & operator = (const vertex_attrib_array &) = default;
		vertex_attrib_array() = default;

		vertex_attrib_array(const vertex_array * pvao, GLuint index);
	protected:
		const vertex_array * mp_vao;
		GLuint m_attr_index;
	};

	class vertex_array :
		public named_object<GLuint> {
	public:
		vertex_array(const vertex_array &) = delete;
		vertex_array & operator=(const vertex_array &) = delete;

		vertex_array();

		~vertex_array();

		inline void bind() const {
			::glBindVertexArray(name());
		}

		vertex_attrib_array & get_attrib(GLuint index);

		void draw(primitive_type mode, GLint first, GLint count);

		void draw_elements(primitive_type mode, GLint count, const GLubyte * pindices);

		void draw_elements(primitive_type mode, GLint count, const GLushort * pindices);

		void draw_elements(primitive_type mode, GLint count, const GLuint * pindices);

		void draw_elements(primitive_type mode, GLint count, const buffer & elem_array, elements_type type);

		void draw_multiple(primitive_type mode, GLint first, GLint count, GLint instances);

		void draw_elements_multiple(primitive_type mode, GLint count, const GLubyte * pindices, GLint instances);

		void draw_elements_multiple(primitive_type mode, GLint count, const GLushort * pindices, GLint instances);

		void draw_elements_multiple(primitive_type mode, GLint count, const GLuint * pindices, GLint instances);

		//TODO: many more draw functions exist
	protected:
		//! Attribute types
		typedef std::map<GLint, vertex_attrib_array> attribs_type;

		//! Attributes
		attribs_type m_attribs;
	};
}

#endif
