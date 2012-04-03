#include "./context.hpp"

namespace ogl {


	context * _curr_ctx = nullptr;

	context::context() :
		m_depth_test(*this),
		m_stencil_test(*this),
		m_scissor_test(*this),
		m_blend_unit(*this),
		m_capabilities(*this),
		m_face_cull(*this){

		for(texture_unit_t::name_type tu = 0; tu < m_capabilities.total_texture_units();tu++) {
			m_texture_units.push_back(new texture_unit_t(*this, GL_TEXTURE0+tu));
		}
	}

	context::~context(){
		for(texture_unit_t * punit : m_texture_units) {
			delete punit;
		}
	}

	bool context::create() {
		if (_curr_ctx == nullptr)
			_curr_ctx = new context();
		return true;
	}

	bool context::get_param_bool(context_param_type pname) const {
		GLboolean v;
		::glGetBooleanv((GLenum)pname, &v);
		return v;
	}

	GLint context::get_param_int(context_param_type pname) const{
		GLint v;
		::glGetIntegerv((GLenum)pname, &v);
		return v;
	}

	GLint64 context::get_param_int64(context_param_type pname) const{
		GLint64 v;
		::glGetInteger64v((GLenum)pname, &v);
		return v;
	}

	GLfloat context::get_param_float(context_param_type pname) const{
		GLfloat v;
		::glGetFloatv((GLenum)pname, &v);
		return v;
	}

	GLdouble context::get_param_double(context_param_type pname) const{
		GLdouble v;
		::glGetDoublev((GLenum)pname, &v);
		return v;
	}

	const std::vector<int> context::get_param_intv(context_param_type pname, size_t size) {
		std::vector<int> res(size);
		::glGetIntegerv((GLenum)pname, &res[0]);
		return std::move(res);
	}


	const std::vector<GLint64> context::get_param_int64v(context_param_type pname, size_t size) {
		std::vector<GLint64> res(size);
		::glGetInteger64v((GLenum)pname, &res[0]);
		return std::move(res);
	}

	const std::vector<float> context::get_param_floatv(context_param_type pname, size_t size) {
		std::vector<float> res(size);
		::glGetFloatv((GLenum)pname, &res[0]);
		return std::move(res);
	}

	const std::vector<double> context::get_param_doublev(context_param_type pname, size_t size) {
		std::vector<double> res(size);
		::glGetDoublev((GLenum)pname, &res[0]);
		return std::move(res);
	}


	//! Get a specific texture_unit
	texture_unit_t & context::texture_unit(size_t index){
		return *m_texture_units.at(index);
	}

	//! Get the name of the active texture unit
	size_t context::active_texture_unit() const{
		return get_param_int(context_param_type::ACTIVE_TEXTURE) - GL_TEXTURE0;
	}

	context & current_ctx() throw(no_active_context){
		if (_curr_ctx == nullptr)
			throw no_active_context();
		return * _curr_ctx;
	}



}
