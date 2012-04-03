#ifndef OGL_CONTEXT_HPP_INCLUDED
#define OGL_CONTEXT_HPP_INCLUDED

#include "./base.hpp"
#include "./exception.hpp"
#include "./depth_test_unit.hpp"
#include "./stencil_test_unit.hpp"
#include "./scissor_test_unit.hpp"
#include "./face_cull_unit.hpp"
#include "./blend_unit.hpp"
#include "./capabilities_unit.hpp"
#include "./texture_unit.hpp"

namespace ogl {

	//! Opengl Context
	class context {
	public:

		//! Create a new OGL context for current thread
		static bool create();

		GLint get_param_int(context_param_type pname) const;

		GLuint get_param_uint(context_param_type pname) const {
			return (GLuint)get_param_int64(pname);
		}

		GLint64 get_param_int64(context_param_type pname) const;

		bool get_param_bool(context_param_type pname) const;

		GLfloat get_param_float(context_param_type pname) const;

		GLdouble get_param_double(context_param_type pname) const;

		template<class E>
		E get_param_enum(context_param_type pname) const {
			return (E)get_param_int(pname);
		}

		const std::vector<int> get_param_intv(context_param_type pname, size_t size);

		const std::vector<GLint64> get_param_int64v(context_param_type pname, size_t size);

		const std::vector<float> get_param_floatv(context_param_type pname, size_t size);

		const std::vector<double> get_param_doublev(context_param_type pname, size_t size);


		//! Get depth test unit of this context
		inline depth_test_unit & depth_test() {
			return m_depth_test;
		}

		//! Get stencil test unit of this context
		inline stencil_test_unit & stencil_test() {
			return m_stencil_test;
		}

		//! Get scissor test unit of this context
		inline scissor_test_unit & scissor_test() {
			return m_scissor_test;
		}

		//! Get blend unit of this context
		inline blend_unit & blend() {
			return m_blend_unit;
		}

		//! Get cull face unit of this context
		inline face_cull_unit & face_cull() {
			return m_face_cull;
		}

		//! Get a specific texture_unit
		texture_unit_t & texture_unit(size_t index);

		//! Get the index of the active texture unit
		size_t active_texture_unit() const;

		//! Get the capabilities query interface
		capabilities_unit & capabilities() {
			return m_capabilities;
		}

		//! Destructor
		~context();
	protected:

		//! Depth test unit
		depth_test_unit m_depth_test;

		//! Stencil test unit
		stencil_test_unit m_stencil_test;

		//! Scissor test unit
		scissor_test_unit m_scissor_test;

		//! Blend unit
		blend_unit m_blend_unit;

		//! Query capabilities interface
		capabilities_unit m_capabilities;

		//! Face cull unit
		face_cull_unit m_face_cull;

		//! Texture unit collection
		typedef std::vector<texture_unit_t *> texture_unit_collection;

		//! Texture units collection
		texture_unit_collection m_texture_units;

		//! Hidden constructor
		context();
	};

	context & current_ctx() throw(no_active_context);
}

#endif
