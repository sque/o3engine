#include "./../window.hpp"
#include "./glut_state.hpp"
#include "./../inputprocessor.hpp"
#include <iostream>

namespace o3engine {

	// Internal implementation of window
	class Window::impl {
	public:

		static GLUTState * ms_gstate;

		//! GLUT window handle
		int m_handle;

		//! Pointer to owner object
		Window * p_wnd;

		//! Window title
		string m_title;

		//! Window height
		int m_height;

		//! Window width
		int m_width;

		//! Back color when clearing
		Color m_back_color;

		//! Window input processor
		InputProcessor * mp_inputprocessor;

		impl(Window * p_wnd, int w, int h, int x, int y, InputProcessor * p_ip) :
				p_wnd(p_wnd), m_height(h), m_width(w),
				m_back_color(Color::BLACK),
				mp_inputprocessor(p_ip) {

			Window::impl::ms_gstate = GLUTState::getSingletonPtr();
			::glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ACCUM);
			::glutInitWindowSize(m_width, m_height);
			::glutInitWindowPosition(x, y);
			m_handle = ::glutCreateWindow("");

			// Save in internal state
			ms_gstate->push_window(p_wnd, this, m_handle, p_ip);

			// Setup callback functions
			::glutReshapeFunc(impl::callbackReshape);
			::glutDisplayFunc(impl::callbackDisplay);
		}

		~impl() {
			::glutDestroyWindow(m_handle);
			ms_gstate->remove_window(p_wnd);
		}

		void setTitle(const string & title) {
			m_title = title;
			::glutSetWindow(m_handle);
			::glutSetWindowTitle(m_title.c_str());
		}

		void resize(int width, int height) {
			m_width = width;
			m_height = height;
			::glutSetWindow(m_handle);
			::glutReshapeWindow(m_width, m_height);
		}

		void getPosition(int & x, int & y) {
			glutSetWindow(m_handle);
			x = ::glutGet(GLUT_WINDOW_X);
			y = ::glutGet(GLUT_WINDOW_Y);
		}

		void implCallbackDisplay() {
			glClearColor(m_back_color);
			::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			::glFlush();

			Window::surface_listeners_type::iterator it;
			for(it = p_wnd->m_sfc_listeners.begin();it != p_wnd->m_sfc_listeners.end(); it++)
				(*it)->onSurfaceRepaint();

			// Swap Buffers
			::glutSwapBuffers();
		}

		void implCallbackReshape(int new_width, int new_height) {
				int old_width = m_width;
			int old_height = m_height;
			m_width = new_width;
			m_height = new_height;

			Window::surface_listeners_type::iterator it;
			for(it = p_wnd->m_sfc_listeners.begin();it != p_wnd->m_sfc_listeners.end(); it++)
				(*it)->onSurfaceResized(old_width, old_height,
					new_width, new_height);
			}

		static void callbackDisplay() {
			((Window::impl *)ms_gstate->m_glut_to_wndstate[glutGetWindow()].mp_wnd_pimpl)
					->implCallbackDisplay();
		}

		static void callbackReshape(int new_width, int new_height) {
			((Window::impl *)ms_gstate->m_glut_to_wndstate[glutGetWindow()].mp_wnd_pimpl)
					->implCallbackReshape(new_width, new_height);
		}

	};

	GLUTState * Window::impl::ms_gstate = 0;

	// Constructor
	Window::Window(int width, int height, int x, int y):
			pimpl(NULL) {
		pimpl = new impl(this, width, height, x, y, new InputProcessor(*this));
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

	void Window::resize(int width, int height) {
		pimpl->resize(width, height);
	}

	void Window::getPosition(int &x, int &y) const {
		pimpl->getPosition(x, y);
	}

	// Set background color
	void Window::setBackColor(const Color & col) {
		pimpl->m_back_color = col;
	}

	// Get background color
	const Color & Window::getBackColor() const {
		return pimpl->m_back_color;
	}

	// Get input processor for this window
	InputProcessor & Window::getInputProcessor() {
		return *pimpl->mp_inputprocessor;
	}
}
