#ifndef OGL_BUFFER_HPP_INCLUDED
#define OGL_BUFFER_HPP_INCLUDED

#include "./base.hpp"
#include <vector>

namespace ogl {

	class buffer :
		named_object<GLuint>{
	public:
		buffer(const buffer &) = delete;
		buffer & operator=(const buffer &) = delete;

		buffer(buffer_type type);

		~buffer();

		inline buffer_type type() const {
			return m_buf_type;
		}

		inline void bind() const {
			::glBindBuffer((GLenum) type(), name());
		}

		//! Bind a range to specific index of arrayed targets (valid for some types)
		void bind_range(GLuint point, size_t offset, size_t size) const {
			::glBindBufferRange((GLenum) type(), point, name(), offset, size);
		}

		// The size of this buffer
		inline size_t size() const {
			return m_size;
		}

		//! glBufferData
		void define_data(size_t size, void * pdata, buffer_usage_pattern usage);

		//! glBufferSubData
		void update_subdata(size_t offset, size_t size, void * pdata);

		//! glGetBufferSubData (prefer mapping)
		std::vector<uint8_t> get_data(size_t offset, size_t size);

		void * map_data(buffer_access_type access);

		bool unmap_data();

		void * map_data_range(size_t offset, size_t size, map_access_bit access);

		void flush_mapped_range(size_t offset, size_t size);
	protected:

		buffer_type m_buf_type;

		size_t m_size;
	};
}

#endif
