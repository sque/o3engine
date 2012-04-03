#include "./face_cull_unit.hpp"
#include "./context.hpp"

namespace ogl {

face_cull_unit::face_cull_unit(context & ctx) :
	m_ctx(ctx) {
}

void face_cull_unit::enable() {
	::glEnable(GL_CULL_FACE);
}

void face_cull_unit::disable() {
	::glDisable(GL_CULL_FACE);
}

bool face_cull_unit::is_enabled() {
	return ::glIsEnabled(GL_CULL_FACE);
}

void face_cull_unit::set_culled_face(face_type face) {
	::glCullFace((GLenum)face);
}

face_type face_cull_unit::get_culled_face() {
	return m_ctx.get_param_enum<face_type>(context_param_type::CULL_FACE_MODE);
}

void face_cull_unit::set_frontface_orientation(face_orientation orientation) {
	::glFrontFace((GLenum)orientation);
}

face_orientation face_cull_unit::get_frontface_orientation(face_orientation){
	return m_ctx.get_param_enum<face_orientation>(context_param_type::FRONT_FACE);
}

}
