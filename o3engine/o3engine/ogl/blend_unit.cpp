#include "./blend_unit.hpp"

#include "./context.hpp"
namespace ogl {

blend_unit::blend_unit(context & ctx)
	:m_ctx(ctx){
}

void blend_unit::enable_logicop() {
	::glEnable(GL_COLOR_LOGIC_OP);
}

void blend_unit::disable_logicop() {
	::glDisable(GL_COLOR_LOGIC_OP);
}

bool blend_unit::is_logicop_enabled() {
	return ::glIsEnabled(GL_COLOR_LOGIC_OP);
}

void blend_unit::set_logicop(logic_op op) {
	::glLogicOp((GLenum)op);
}

logic_op blend_unit::get_logicop() {
	return (logic_op)m_ctx.get_param_int(context_param_type::LOGIC_OP_MODE);
}

void blend_unit::enable() {
	::glEnable(GL_BLEND);
}

void blend_unit::disable() {
	::glDisable(GL_BLEND);
}

bool blend_unit::is_enabled() {
	return m_ctx.get_param_bool(context_param_type::BLEND);
}

void blend_unit::set_write_mask(bool red, bool green, bool blue, bool alpha) {
	::glColorMask(red, green, blue, alpha);
}

void blend_unit::set_buffer_write_mask(GLuint buffer_index, bool red, bool green, bool blue, bool alpha) {
	::glColorMaski(buffer_index, red, green, blue, alpha);
}

void blend_unit::get_write_mask(bool & red, bool & green, bool & blue, bool & alpha) {
	GLboolean rgba[4];
	::glGetBooleanv(GL_COLOR_WRITEMASK, rgba);
	red = rgba[0];
	green = rgba[1];
	blue = rgba[2];
	alpha = rgba[3];
}

void blend_unit::set_func(blend_factor sfactor, blend_factor dfactor) {
	::glBlendFunc((GLenum)sfactor, (GLenum)dfactor);
}

void blend_unit::set_buffer_func(GLuint buffer_index, blend_factor sfactor, blend_factor dfactor) {
	::glBlendFunci(buffer_index, (GLenum)sfactor, (GLenum)dfactor);
}

void blend_unit::set_func_components(blend_factor srgb, blend_factor drgb, blend_factor salpha, blend_factor dalpha) {
	::glBlendFuncSeparate((GLenum)srgb, (GLenum)drgb, (GLenum)salpha, (GLenum)dalpha);
}

void blend_unit::set_buffer_func_components(GLuint buffer_index, blend_factor srgb, blend_factor drgb, blend_factor salpha, blend_factor dalpha) {
	::glBlendFuncSeparatei(buffer_index, (GLenum)srgb, (GLenum)drgb, (GLenum)salpha, (GLenum)dalpha);
}


void blend_unit::get_func_rgb(blend_factor & sfactor, blend_factor & dfactor) {
	sfactor = (blend_factor)m_ctx.get_param_int(context_param_type::BLEND_SRC_RGB);
	dfactor = (blend_factor)m_ctx.get_param_int(context_param_type::BLEND_DST_RGB);
}

void blend_unit::get_func_alpha(blend_factor & sfactor, blend_factor & dfactor) {
	sfactor = (blend_factor)m_ctx.get_param_int(context_param_type::BLEND_SRC_ALPHA);
	dfactor = (blend_factor)m_ctx.get_param_int(context_param_type::BLEND_DST_ALPHA);
}


void blend_unit::set_func_color(GLclampf r, GLclampf g, GLclampf b, GLclampf a) {
	::glBlendColor(r, g, b, a);
}

void blend_unit::get_func_color(GLclampf & r, GLclampf & g, GLclampf & b, GLclampf & a) {
	auto rgba = m_ctx.get_param_floatv(context_param_type::BLEND_COLOR, 4);
	r = rgba[0];
	g = rgba[1];
	b = rgba[2];
	a = rgba[3];
}

void blend_unit::set_func_equation(blend_equation mode) {
	::glBlendEquation((GLenum)mode);
}

void blend_unit::set_buffer_func_equation(GLuint buffer_index, blend_equation mode) {
	::glBlendEquationi(buffer_index, (GLenum)mode);
}

blend_equation blend_unit::get_func_equation_rgb() {

	return (blend_equation)m_ctx.get_param_int(context_param_type::BLEND_EQUATION_RGB);
}

blend_equation blend_unit::get_func_equation_alpha() {
	return (blend_equation)m_ctx.get_param_int(context_param_type::BLEND_EQUATION_ALPHA);
}

}
