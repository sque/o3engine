#ifndef OGL_PROGRAM_HPP_INCLUDED
#define OGL_PROGRAM_HPP_INCLUDED

#include "./shader.hpp"
#include "./uniform.hpp"
#include <map>

namespace ogl {

	//! Program to be executed in the GPU pipeline
	/**
	 * @remarks non-copiable, non-inheritable
	 */
	class program :
		public named_object<GLint>{
	public:

		program(const program &) = delete;
		program & operator=(const program &) = delete;

		program();

		//! Type of shaders container
		typedef std::vector<shader *> shaders_type;

		enum class param_type {
			DELETE_STATUS = GL_DELETE_STATUS,
			LINK_STATUS = GL_LINK_STATUS,
			VALIDATE_STATUS = GL_VALIDATE_STATUS,
			INFO_LOG_LENGTH = GL_INFO_LOG_LENGTH,
			ATTACHED_SHADERS = GL_ATTACHED_SHADERS,
			// TODO: GLEW 1.7 ACTIVE_ATOMIC_COUNTER_BUFFERS = GL_ACTIVE_ATOMIC_COUNTER_BUFFERS,
			ACTIVE_ATTRIBUTES = GL_ACTIVE_ATTRIBUTES,
			ACTIVE_ATTRIBUTE_MAX_LENGTH = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
			ACTIVE_UNIFORMS = GL_ACTIVE_UNIFORMS,
			ACTIVE_UNIFORM_MAX_LENGTH = GL_ACTIVE_UNIFORM_MAX_LENGTH,
			PROGRAM_BINARY_LENGTH = GL_PROGRAM_BINARY_LENGTH,
			TRANSFORM_FEEDBACK_BUFFER_MODE = GL_TRANSFORM_FEEDBACK_BUFFER_MODE,
			TRANSFORM_FEEDBACK_VARYINGS = GL_TRANSFORM_FEEDBACK_VARYINGS,
			TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH = GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH,
			GEOMETRY_VERTICES_OUT = GL_GEOMETRY_VERTICES_OUT,
			GEOMETRY_INPUT_TYPE = GL_GEOMETRY_INPUT_TYPE,
			GEOMETRY_OUTPUT_TYPE = GL_GEOMETRY_OUTPUT_TYPE
		};

		//! Attach a shader at program pipeline
		void attach_shader(shader & sh);

		//! Detach a shader object
		void detach_shader(shader & sh);

		//! Get all attached shaders
		inline shaders_type get_attached_shaders() const{
			return m_shaders;
		}

		//! Get a program parameter
		GLint get_param(param_type type) const;

		//! Check if this program is linked
		bool is_linked() const;

		//! Link all attached shaders
		void link() throw(link_error);

		//! Compile shaders and link them
		void build() throw(compile_error, link_error);

		//! Validate program
		void validate();

		//! Check if it is valid
		bool is_valid() const;

		//! Query info log
		const std::string info_log() const;

		//! Use this program
		inline void use() const {
			::glUseProgram(name());
		}

		//! Handle a uniform
		/**
		 * Returned variable will be deleted when program is deleted
		 */
		uniform & get_uniform(const std::string & name) throw (uniform_not_found);

		//! Handle a uniform by uid name
		/**
		 * Returned variable will be deleted when program is deleted
		 */
		uniform & get_uniform(GLuint name_id) throw (uniform_not_found);

		//! Define the related fbo color attachement of frag color varying out
		void define_frag_color_color_attachment(GLuint color_attachment, const std::string & name);

		//! Get total attached shaders
		GLint total_attached_shaders() const;

		//! Get total active atomic counter buffers
		GLint total_active_atomic_counter_buffers() const;

		//! Get total active attributes
		GLint total_active_attributes() const;

		//! Get the maximum name length of all active attributes (including null character)
		GLint max_name_of_active_attributes() const;

		//! Get total number of active uniforms
		GLint total_active_uniforms() const;

		//! Get the maximum name length of all active uniforms (including null character)
		GLint max_name_of_active_uniforms() const;

		//! Get length of programs binary format
		GLint binary_length() const;

		//! Get program's feedback buffer mode
		buffer_mode_type transform_feedback_buffer_mode() const;

		//! Get total transform feedback varyings
		GLint total_transform_feedback_varyings() const;

		//! Get the maximum name length of all transform feedback varyings (including null character)
		GLint max_name_of_transform_feedback_varying() const;

		//! Get the maximum geometry vertices that can be produced
		GLint max_geometry_vertices_out() const;

		//! Get the primitive type of geometry input
		primitive_type geometry_input_type() const;

		//! Get the primitive type of geometry output
		primitive_type geometry_output_type() const;

	protected:
		//! Type of uniforms container
		typedef std::map<GLint, uniform> uniforms_type;

		//! Uniforms container
		uniforms_type m_uniforms;

		//! Shaders container
		shaders_type m_shaders;
	};
}

#endif
