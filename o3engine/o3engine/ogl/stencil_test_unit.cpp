#include "./stencil_test_unit.hpp"
#include "./context.hpp"

namespace ogl {

stencil_test_unit::stencil_test_unit(context & ctx):
	m_ctx(ctx) {
}

void stencil_test_unit::enable() {
	::glEnable(GL_STENCIL_TEST);
}

void stencil_test_unit::disable() {
	::glDisable(GL_STENCIL_TEST);
}

bool stencil_test_unit::is_enabled() {
	return m_ctx.get_param_bool(context_param_type::STENCIL_TEST);
}

void stencil_test_unit::set_write_mask(mask_type mask) {
	::glStencilMask(mask);
}

void stencil_test_unit::set_face_write_mask(face_type face, mask_type mask) {
	::glStencilMaskSeparate((GLenum)face, mask);
}

stencil_test_unit::mask_type stencil_test_unit::get_write_mask() {
	return m_ctx.get_param_uint(context_param_type::STENCIL_WRITEMASK);
}

stencil_test_unit::mask_type stencil_test_unit::get_back_write_mask() {
	return m_ctx.get_param_uint(context_param_type::STENCIL_BACK_WRITEMASK);
}

void stencil_test_unit::set_compare_func(compare_func func, stencil_test_unit::compare_reference_type ref, stencil_test_unit::mask_type mask) {
	::glStencilFunc((GLenum)func, ref, mask);
}

void stencil_test_unit::set_face_compare_func(face_type face, compare_func func, stencil_test_unit::compare_reference_type ref, stencil_test_unit::mask_type mask) {
	::glStencilFuncSeparate((GLenum)face, (GLenum)func, ref, mask);
}

compare_func stencil_test_unit::get_compare_func() {
	return m_ctx.get_param_enum<compare_func>(context_param_type::STENCIL_FUNC);
}

compare_func stencil_test_unit::get_back_compare_func() {
	return m_ctx.get_param_enum<compare_func>(context_param_type::STENCIL_BACK_FUNC);
}

stencil_test_unit::mask_type stencil_test_unit::get_compare_mask() {
	return m_ctx.get_param_uint(context_param_type::STENCIL_VALUE_MASK);
}

stencil_test_unit::mask_type stencil_test_unit::get_back_compare_mask() {
	return m_ctx.get_param_uint(context_param_type::STENCIL_BACK_VALUE_MASK);
}

stencil_test_unit::compare_reference_type stencil_test_unit::get_compare_reference() {
	return m_ctx.get_param_int(context_param_type::STENCIL_REF);
}

stencil_test_unit::compare_reference_type stencil_test_unit::get_back_compare_reference() {
	return m_ctx.get_param_int(context_param_type::STENCIL_BACK_REF);
}

void stencil_test_unit::set_op(stencil_op stencil_fail, stencil_op stencil_pass_depth_fail, stencil_op stencil_pass_depth_pass) {
	::glStencilOp((GLenum)stencil_fail, (GLenum) stencil_pass_depth_fail, (GLenum) stencil_pass_depth_pass);
}

void stencil_test_unit::set_face_op(face_type face, stencil_op stencil_fail, stencil_op stencil_pass_depth_fail, stencil_op stencil_pass_depth_pass) {
	::glStencilOpSeparate((GLenum) face, (GLenum)stencil_fail, (GLenum) stencil_pass_depth_fail, (GLenum) stencil_pass_depth_pass);
}

stencil_op stencil_test_unit::get_stencil_fail_op() {
	return m_ctx.get_param_enum<stencil_op>(context_param_type::STENCIL_FAIL);
}

stencil_op stencil_test_unit::get_back_stencil_fail_op() {
	return m_ctx.get_param_enum<stencil_op>(context_param_type::STENCIL_BACK_FAIL);
}

stencil_op stencil_test_unit::get_stencil_pass_depth_fail_op() {
	return m_ctx.get_param_enum<stencil_op>(context_param_type::STENCIL_PASS_DEPTH_FAIL);
}

stencil_op stencil_test_unit::get_back_stencil_pass_depth_fail_op() {
	return m_ctx.get_param_enum<stencil_op>(context_param_type::STENCIL_BACK_PASS_DEPTH_FAIL);
}

stencil_op stencil_test_unit::get_stencil_pass_depth_pass_op(){
	return m_ctx.get_param_enum<stencil_op>(context_param_type::STENCIL_PASS_DEPTH_PASS);
}

stencil_op stencil_test_unit::get_back_stencil_pass_depth_pass_op() {
	return m_ctx.get_param_enum<stencil_op>(context_param_type::STENCIL_BACK_PASS_DEPTH_PASS);
}

stencil_op stencil_test_unit::get_op(face_type face, bool stencil_pass, bool depth_pass) throw(std::invalid_argument){

	if (face != face_type::BACK) {
		if (!stencil_pass) {
			return get_stencil_fail_op();
		} else if (!depth_pass) {
			return get_stencil_pass_depth_fail_op();
		} else if (depth_pass){
			return get_stencil_pass_depth_pass_op();
		}
	} else {
		if (!stencil_pass) {
			return get_back_stencil_fail_op();
		} else if (!depth_pass) {
			return get_back_stencil_pass_depth_fail_op();
		} else if (depth_pass){
			return get_back_stencil_pass_depth_pass_op();
		}
	}

	throw std::invalid_argument("There is no operation when stencil test is PASS.");
}

}

