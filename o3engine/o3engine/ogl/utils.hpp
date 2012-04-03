#ifndef OGL_UTILS_HPP_INCLUDED
#define OGL_UTILS_HPP_INCLUDED

#include "./types.hpp"
#include <algorithm>


namespace ogl {



/*
	struct glGetVertexAttribiv_tag
	{
		template < class T >
		static void call(...,  T *ptr) {glGetVertexAttribiv}
	};

	x.gl_get_wrapper(glGetVertexAttribiv_tag(), x);

	template < class tag, class T >
	void foo(..)
	{
		tag::execute()
	}

	typedef void (*gl_get_wrapper_func)(GLenum, GLint *);
*/

/*
	template <class N, class T>
	struct gl_wrapper_desc{
		typedef void (*func_type)(N, GLenum, T *);
	};


	template <class T>
	using gl_wrapper_desc<GLbool, T> gl_test_type;
*/
	/*template<class R, class T, class E>
	R gl_get_wrapper(void (*f)(GLuint, GLenum, T *), GLuint i, GLenum pname) {
		T v;
		f(i, (GLenum)pname, &v);
		return (R)v;
	}*/


/*

	template<gl_get_wrapper_func F, class T, class I>
	T gl_get_wrapper_1(I pre1, GLenum pname) {
		T v;
		F(pre1, (GLenum)pname, &v);
		return std::move(v);
	}*/
/*
	template<class RET, class F, class T>
	struct {
		typedef void (*func_type)(GLenum, )
	};
*/


	/*typedef void (*gl_get_wrapper_func)(GLenum, GLint *);
	template<F f>
	T gl_get_wrapper(GLenum pname) {
		T v;
		F((GLenum)pname, &v);
		return std::move(v);
	}*/

/*
	template<typename T>
	T gl_get(GLenum pname) {
		T v;
		::glGetFloatv((GLenum)pname, &v);
		return std::move(v);
	}

	class testi{
		static void calld(int x, int y) { }
	};
	//testi::call();
	testi::calld(0,0);
*/

/*
	gl_get_wrapper< glGetPointer, vec2f >

	vec2f range = context::curr().get<vec2f>(context_param_type::DEPTH_RANGE);

	vec2f range = context::get<vec2f>(context_param_type::DEPTH_RANGE);

	vec2f range = gl_get<vec2f>(DEPTH_RANGE);

	vec2f clamp = ptexture->get<vec2f>(texture_param_type::CLAMP_RANGE);

	vec2f clamp = ptexture->get<vec2f>(CLAMP_RANGE);

	vec2f clamp = ptexture->get(CLAMP_RANGE);

	vec2f clamp = ptexture->param(CLAMP_RANGE);

	ptexture->param(CLAMP_RANGE, vec2f(1,2));

	vec2f clamp = ptexture->get(CLAMP_RANGE);  // Only GLclampd IMPOSSIBLE (in respect of time)

	float clamp = ptexture->get<float>(CLAMP_RANGE);	// SEGFAULT!

	float clamp = ptexture->get_float(CLAMP_RANGE);		// SEGFAULT!

	flaot clamp = ptexture->get_clamp_range();			// Compile safe

	*/
}

#endif
