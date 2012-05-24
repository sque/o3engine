#ifndef OGL_EXCEPTION_HPP_INCLUDED
#define OGL_EXCEPTION_HPP_INCLUDED

#include "./base.hpp"
#include <stdexcept>

namespace ogl {

//! Base exception for all OGL related exceptions
class exception: public std::exception {
public:

	//! Error string holder
	std::string m_error_str;


	virtual ~exception() throw () {	}

	//! Constructor with error string
	exception(const std::string & error) throw () :
			m_error_str(error) {}

	//! Default constructor
	exception() throw(){
	};

	//! Return what string
	virtual const char * what() const throw () {
		return m_error_str.c_str();
	}
};

//! When an opengl error occurs, this exception carries opengl status
class gl_error: public exception {
public:
	//! OpenGL error code
	GLenum m_gl_error;

	//! Construct with the error code
	gl_error(GLenum error) :
		m_gl_error(error){
		m_error_str = std::string("GL: ") + get_glu_error_str();
	}

	//! Construct with a custom message
	gl_error(GLenum error, const std::string & user_action) :
		m_gl_error(error){
		m_error_str = std::string("GL: ") + user_action + std::string(" ")
				+ get_glu_error_str();
	}

	virtual ~gl_error() throw () {	}

	const std::string get_glu_error_str() {
		return (const char *) gluErrorString(m_gl_error);
	}
};

//! Exception thrown when object cannot be located
class object_not_found: public exception {
public:
	object_not_found(const std::string & name) throw (){
		m_error_str = std::string("Cannot find object with name ") + name;
	}
	virtual ~object_not_found() throw() {
	}
};

//! Exception thrown when uniform cannot be located
class uniform_not_found: public exception {
public:
	uniform_not_found(const std::string & name) throw (){
		m_error_str = std::string("Cannot find uniform with name ") + name;
	}
	virtual ~uniform_not_found() throw() {
	}
};

//! Exception thrown when compilation has failed.
class compile_error: public exception {
public:
	compile_error(const std::string & error) throw () :
			exception(error) {}

	virtual ~compile_error() throw () {	}
};

//! Exception thrown when shader linkage has failed
class link_error: public exception {
public:
	link_error(const std::string & error) throw () :
			exception(error) {}

	virtual ~link_error() throw () {}
};

//! Exception thrown when there is no active context
class no_active_context: public exception {
public:

	no_active_context() throw() :
		exception("No active context."){
	}

	no_active_context(const std::string & error) throw() {
		m_error_str = std::string("No active context. " + error);
	}

	virtual ~no_active_context() throw() {}
};

//! Checkpoint that no
inline void gl_error_checkpoint(const std::string & name) throw(gl_error){
	GLenum gerr;
	if ((gerr = glGetError()) != GL_NO_ERROR) {
		throw gl_error(gerr, name);
	}
}

}
#endif
