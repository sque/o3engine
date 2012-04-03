#ifndef OGL_DEPTH_TEST_UNIT_HPP_INCLUDED
#define OGL_DEPTH_TEST_UNIT_HPP_INCLUDED

#include "./base.hpp"

namespace ogl {
	//! Forward declaration of context
	class context;

	//! Control OpenGL depth test unit
	class depth_test_unit {
	public:
		friend class context;

		depth_test_unit(const depth_test_unit &) = delete;
		depth_test_unit operator=(const depth_test_unit &) = delete;

		void get_range(GLclampd & znear, GLclampd & zfar);

		void set_range(GLclampd znear, GLclampd zfar);

		void set_clear_value(GLclampd depth);

		GLclampd get_clear_value();

		void enable();

		void disable();

		bool is_enabled();

		void enable_write();

		void disable_write();

		bool is_write_enabled();

		compare_func get_compare_func();

		void set_compare_func(compare_func func);

		void get_polygon_offset(GLfloat & factor, GLfloat & units);

		void set_polygon_offset(GLfloat factor, GLfloat units);

		void enable_fill_polygon_offset();

		void disable_fill_polygon_offset();

		bool is_fill_polygon_offset_enabled();

		void enable_point_polygon_offset();

		void disable_point_polygon_offset();

		bool is_point_polygon_offset_enabled();

		void enable_line_polygon_offset();

		void disable_line_polygon_offset();

		bool is_line_polygon_offset_enabled();

	protected:
		depth_test_unit(context & ctx);
		context & m_ctx;
	};
}

#endif
