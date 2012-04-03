#ifndef OGL_FACE_CULL_UNIT_HPP_INCLUDED
#define OGL_FACE_CULL_UNIT_HPP_INCLUDED

#include "./base.hpp"

namespace ogl {

class context;

//! Context unit that controls culling
class face_cull_unit {
public:
	face_cull_unit(context & ctx);

	void enable();

	void disable();

	bool is_enabled();

	void set_culled_face(face_type face);

	face_type get_culled_face();

	void set_frontface_orientation(face_orientation orientation);

	face_orientation get_frontface_orientation(face_orientation);

protected:
	context & m_ctx;
};

}


#endif
