#ifndef OGL_STENCIL_TEST_UNIT_HPP_INCLUDED
#define OGL_STENCIL_TEST_UNIT_HPP_INCLUDED

#include "./base.hpp"

namespace ogl {

class context;

class stencil_test_unit {
public:
	friend class context;

	typedef GLuint mask_type;

	typedef GLint compare_reference_type;

	stencil_test_unit(stencil_test_unit &) = delete;
	stencil_test_unit & operator=(stencil_test_unit &) = delete;

	void enable();

	void disable();

	bool is_enabled();

	void set_write_mask(mask_type mask);

	void set_face_write_mask(face_type face, mask_type mask);

	mask_type get_write_mask();

	mask_type get_back_write_mask();

	void set_compare_func(compare_func func, compare_reference_type ref, mask_type mask);

	void set_face_compare_func(face_type face, compare_func func, compare_reference_type ref, mask_type mask);

	compare_func get_compare_func();

	compare_func get_back_compare_func();

	mask_type get_compare_mask();

	mask_type get_back_compare_mask();

	compare_reference_type get_compare_reference();

	compare_reference_type get_back_compare_reference();

	void set_op(stencil_op stencil_fail, stencil_op stencil_pass_depth_fail, stencil_op stencil_pass_depth_pass);

	void set_face_op(face_type face, stencil_op stencil_fail, stencil_op stencil_pass_depth_fail, stencil_op stencil_pass_depth_pass);

	stencil_op get_stencil_fail_op();

	stencil_op get_back_stencil_fail_op();

	stencil_op get_stencil_pass_depth_fail_op();

	stencil_op get_back_stencil_pass_depth_fail_op();

	stencil_op get_stencil_pass_depth_pass_op();

	stencil_op get_back_stencil_pass_depth_pass_op();

	stencil_op get_op(face_type face, bool stencil_pass, bool depth_pass) throw(std::invalid_argument);

protected:
	stencil_test_unit(context & ctx);

	context & m_ctx;
};
}


#endif
