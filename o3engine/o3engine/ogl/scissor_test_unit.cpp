#include "./scissor_test_unit.hpp"
#include "./context.hpp"

namespace ogl {

scissor_test_unit::scissor_test_unit(context & ctx) :
	m_ctx(ctx){
}

void scissor_test_unit::enable() {
	::glEnable(GL_SCISSOR_TEST);
}

void scissor_test_unit::disable() {
	::glDisable(GL_SCISSOR_TEST);
}

bool scissor_test_unit::is_enabled() {
	return ::glIsEnabled(GL_SCISSOR_TEST);
}

void scissor_test_unit::set_box(int x, int y, size_t width, size_t height) {
	::glScissor(x, y, width, height);
}

void scissor_test_unit::get_box(int & x, int & y, size_t & width, size_t & height) {
	auto box = m_ctx.get_param_intv(context_param_type::SCISSOR_BOX, 4);
	x = box[0];
	y = box[1];
	width = box[2];
	height = box[3];
}

}
