#ifndef O3ENGINE_OGL_EXCEPTION_HPP_INCLUDED
#define O3ENGINE_OGL_EXCEPTION_HPP_INCLUDED
#include "./../prereqs.hpp"
#include <stdexcept>

namespace o3engine {
namespace ogl {

class exception: public std::exception {
public:
	virtual ~exception() throw () {	}
};

class gl_error: public exception {
public:

	std::string m_error_str;

	gl_error(const std::string & user_action) {
		m_error_str = std::string("GL: ") + user_action + std::string(" ")
				+ get_glu_error_str();
	}

	gl_error() {
		m_error_str = std::string("GL: ") + get_glu_error_str();
	}

	virtual ~gl_error() throw () {	}

	virtual const char* what() const throw () {
		return m_error_str.c_str();
	}

	const std::string get_glu_error_str() {
		return (const char *) gluErrorString(glGetError());
	}
};

class compile_error: public exception {
public:

	std::string m_error_str;

	compile_error(const std::string & error) throw () :
			m_error_str(error) {
	}

	virtual ~compile_error() throw () {
	}

	virtual const char * what() const throw () {
		return m_error_str.c_str();
	}
};

class link_error: public exception {
public:

	std::string m_error_str;

	link_error(const std::string & error) throw () :
			m_error_str(error) {
	}

	virtual ~link_error() throw () {
	}

	virtual const char * what() const throw () {
		return m_error_str.c_str();
	}
};

}
}
#endif
