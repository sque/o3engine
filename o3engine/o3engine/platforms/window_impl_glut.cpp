#include "./window.hpp"
#include "./window_impl_glut.hpp"
#include "./inputprocessor.hpp"
#include <iostream>

namespace o3engine {


	std::vector<Window::impl *> Window::impl::m_handles_to_impls;


	// Constructor
	Window::Window(const string & name, int width, int height, int x, int y):
			pimpl(NULL) {
		pimpl = new impl(name, width, height, x, y, new InputProcessor(*this));
	}

	// Destructor
	Window::~Window() {
		if (pimpl)
			delete pimpl;
	}

	//! Get current window title
	const string Window::getTitle() const {
		return pimpl->m_title;
	}

	//! Set window title
	void Window::setTitle(const string & title) {
		pimpl->setTitle(title);
	}

	int Window::getHeight() const {
		return pimpl->m_height;
	}

	int Window::getWidth() const {
		return pimpl->m_width;
	}

	void Window::setSize(int width, int height) {
		pimpl->resize(width, height);
	}

	//! Set background color
	void Window::setBackColor(const Color & col) {
		pimpl->m_back_color = col;
	}

	//! Get background color
	const Color & Window::getBackColor() const {
		return pimpl->m_back_color;
	}

	//! Get input processor for this window
	InputProcessor & Window::getInputProcessor() {
		return *pimpl->mp_inputprocessor;
	}

}
