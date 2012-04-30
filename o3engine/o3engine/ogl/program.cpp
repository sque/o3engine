#include "./program.hpp"

namespace ogl{

	program::program(){
		m_gl_name = ::glCreateProgram();
		if (m_gl_name == 0)
			throw gl_error(glGetError(), "Cannot create shader program.");
	}

	void program::attach_shader(shader & sh) {
		::glAttachShader(m_gl_name, sh.name());
		gl_error_checkpoint("glAttachShader failed.");
		m_shaders.push_back(&sh);
	}

	void program::detach_shader(shader & sh) {
		shaders_type::iterator it = std::find(m_shaders.begin(), m_shaders.end(), &sh);

		if (it == m_shaders.end());
			return;	// Not found

		::glDetachShader(name(), sh.name());
		m_shaders.erase(it);
	}

	int program::get_param(param_type type) const {
		GLint param_val;
		::glGetProgramiv(m_gl_name, (GLenum)type, &param_val);
		return param_val;
	}

	uniform & program::get_uniform(const std::string & uname) throw (uniform_not_found){
		GLint uid = ::glGetUniformLocation(name(), uname.c_str());
		if (uid == -1)
			throw uniform_not_found(uname);

		uniforms_type::iterator it;
		if ((it = m_uniforms.find(uid)) == m_uniforms.end()) {
			// Create uniform state object
			m_uniforms[uid] = uniform(*this, uname); // TODO: use C++11 emplace()
		}

		return m_uniforms[uid];
	}

	uniform & program::get_uniform(uniform::name_type name_id) throw (uniform_not_found) {
		uniforms_type::iterator it;
		if ((it = m_uniforms.find(name_id)) == m_uniforms.end()) {
			throw uniform_not_found("Cannot find uniform by id.");
		}

		return m_uniforms[name_id];
	}

	uniform_block & program::get_uniform_block(const std::string & bname) throw (uniform_not_found){
		uniform_block::name_type bid = ::glGetUniformBlockIndex(name(), bname.c_str());
		if (bid == GL_INVALID_INDEX)
			throw uniform_not_found(bname);

		uniform_blocks_type::iterator it;
		if ((it = m_uniform_blocks.find(bid)) == m_uniform_blocks.end()) {
			// Create uniform state object
			m_uniform_blocks[bid] = uniform_block(*this, bname); // TODO: use C++11 emplace()
		}

		return m_uniform_blocks[bid];
	}

	bool program::is_linked() const{
		return (bool)get_param(param_type::LINK_STATUS);
	}

	bool program::is_valid() const {
		return (bool)get_param(param_type::VALIDATE_STATUS);
	}

	GLint program::total_attached_shaders() const {
		return get_param(param_type::ATTACHED_SHADERS);
	}

	GLint program::total_active_atomic_counter_buffers() const {
		//TODO: GLEW 1.7 return get_param(param_type::ACTIVE_ATOMIC_COUNTER_BUFFERS);
		return 0;
	}

	GLint program::total_active_attributes() const{
		return get_param(param_type::ACTIVE_ATTRIBUTES);
	}

	GLint program::max_name_of_active_attributes() const{
		return get_param(param_type::ACTIVE_ATTRIBUTE_MAX_LENGTH);
	}

	GLint program::total_active_uniforms() const{
		return get_param(param_type::ACTIVE_UNIFORMS);
	}

	GLint program::max_name_of_active_uniforms() const{
		return get_param(param_type::ACTIVE_UNIFORM_MAX_LENGTH);
	}

	GLint program::binary_length() const{
		return get_param(param_type::PROGRAM_BINARY_LENGTH);
	}

	buffer_mode_type program::transform_feedback_buffer_mode() const{
		return (buffer_mode_type)get_param(param_type::TRANSFORM_FEEDBACK_BUFFER_MODE);
	}

	GLint program::total_transform_feedback_varyings() const{
		return get_param(param_type::TRANSFORM_FEEDBACK_VARYINGS);
	}

	GLint program::max_name_of_transform_feedback_varying() const{
		return get_param(param_type::TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH);
	}

	GLint program::max_geometry_vertices_out() const{
		return get_param(param_type::GEOMETRY_VERTICES_OUT);
	}

	primitive_type program::geometry_input_type() const{
		return (primitive_type)get_param(param_type::GEOMETRY_INPUT_TYPE);
	}

	primitive_type program::geometry_output_type() const{
		return (primitive_type)get_param(param_type::GEOMETRY_OUTPUT_TYPE);
	}

	const std::string program::info_log() const{
		int info_lenght = get_param(param_type::INFO_LOG_LENGTH);

		// Read error
		std::string info_log(info_lenght, '\0');
		glGetProgramInfoLog(m_gl_name, info_lenght, &info_lenght, &info_log[0]);
		return std::move(info_log);
	}

	void program::link() throw(link_error){
		::glLinkProgram(m_gl_name);
		if (!is_linked()) {
			throw link_error(info_log());
		}
	}

	void program::build() throw(compile_error, link_error) {
		shaders_type::iterator it;

		for(shader * psh : m_shaders) {
			if (!psh->is_compiled()) {
				psh->compile();
			}
		}
		link();
	}

	void program::validate(){
		::glValidateProgram(m_gl_name);
		if (!is_valid()) {
			throw link_error(info_log()); // TODO: another exception class
		}
	}
}
