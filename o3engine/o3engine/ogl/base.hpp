#ifndef OGL_BASE_HPP_INCLUDED
#define OGL_BASE_HPP_INCLUDED

#include "./types.hpp"
#include "./utils.hpp"
#include <stdexcept>
#include <string>
#include <initializer_list>

namespace ogl {

	//! Base type for Opengl named objects
	template <class T>
	class named_object {
	public:

		//! Type of the name
		typedef T name_type;

		// Return the name of object
		inline name_type name() const {
			return  m_gl_name;
		}

	protected:
		//! object name
		T m_gl_name;
	};

	template<class R, class T, class N, class E>
	R gl_get_wrapper(void (*f)(N, GLenum, T *), N i, E pname) {
		T v;
		f(i, (GLenum)pname, &v);
		return R(v);
	}

	template<class T, class N, class E>
	T gl_get_wrapper(void (*f)(N, GLenum, T *), N i, E pname) {
		T v;
		f(i, (GLenum)pname, &v);
		return v;
	}
}

#endif
