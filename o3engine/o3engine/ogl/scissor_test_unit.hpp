#ifndef OGL_SCISSOR_TEST_UNIT_HPP_INCLUDED
#define OGL_SCISSOR_TEST_UNIT_HPP_INCLUDED

#include "./base.hpp"

namespace ogl {

class context;

//! Context unit that controls culling
class scissor_test_unit {
public:
	friend class context;

	scissor_test_unit(scissor_test_unit &) = delete;
	scissor_test_unit & operator=(scissor_test_unit &) = delete;

	void enable();

	void disable();

	bool is_enabled();

	void set_box(int x, int y, size_t width, size_t height);

	void get_box(int & x, int & y, size_t & width, size_t & height);

protected:
	scissor_test_unit(context & ctx);

	context & m_ctx;
};

}


#endif
