#ifndef OGL_BLEND_UNIT_HPP_INCLUDED
#define OGL_BLEND_UNIT_HPP_INCLUDED

#include "./base.hpp"

namespace ogl {

class context;

class blend_unit {
public:
	friend class context;

	blend_unit(blend_unit & )= delete;
	blend_unit & operator=(blend_unit & )= delete;

	void enable_logicop();

	void disable_logicop();

	bool is_logicop_enabled();

	void set_logicop(logic_op op);

	logic_op get_logicop();

	void enable();

	void disable();

	bool is_enabled();

	void set_write_mask(bool red, bool green, bool blue, bool alpha);

	void set_buffer_write_mask(GLuint buffer_index, bool red, bool green, bool blue, bool alpha);

	void get_write_mask(bool & red, bool & green, bool & blue, bool & alpha);

	void set_func(blend_factor sfactor, blend_factor dfactor);

	void set_buffer_func(GLuint buffer_index, blend_factor sfactor, blend_factor dfactor);

	void set_func_components(blend_factor srgb, blend_factor drgb, blend_factor salpha, blend_factor dalpha);

	void set_buffer_func_components(GLuint buffer_index, blend_factor srgb, blend_factor drgb, blend_factor salpha, blend_factor dalpha);

	void get_func_rgb(blend_factor & sfactor, blend_factor & dfactor);

	void get_func_alpha(blend_factor & sfactor, blend_factor & dfactor);

	void set_func_color(GLclampf r, GLclampf g, GLclampf b, GLclampf a);

	void get_func_color(GLclampf & r, GLclampf & g, GLclampf & b, GLclampf & a);

	void set_func_equation(blend_equation mode);

	void set_buffer_func_equation(GLuint buffer_index, blend_equation mode);

	blend_equation get_func_equation_rgb();

	blend_equation get_func_equation_alpha();

private:
	blend_unit(context & ctx);

	context & m_ctx;
};

}

#endif
