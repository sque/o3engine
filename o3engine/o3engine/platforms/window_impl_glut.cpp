#include "./window.hpp"
#include "./input_processor.hpp"

namespace o3engine {
// Internal implementation of platform
class Window::impl {
public:
	static vector<impl *> m_handles_to_impls;
	string m_name;
	string m_title;
	int m_height;
	int m_width;
	int m_handle;
	int m_pos_x;
	int m_pos_y;
	Color m_back_color;
	WindowEventsListener * mp_listener;


	impl(const string & name, int w, int h, int x = 0, int righy = 0) :
			m_name(name), m_height(h), m_width(w), m_back_color(
					Color::BLACK), mp_listener(NULL) {
		::glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ACCUM);
		::glutInitWindowSize(m_width, m_height);
		::glutInitWindowPosition(m_pos_x, m_pos_y);
		m_handle = ::glutCreateWindow("");

		// Save pointer of current window
		m_handles_to_impls[m_handle] = this;

		// Setup Callback functions
		/*glutReshapeFunc(impl::glutFuncReshape);
		glutDisplayFunc(impl::glutFuncDisplay);
		glutIdleFunc(impl::glutFuncIdle);*/
	}

	~impl() {
		::glutDestroyWindow(m_handle);
		m_handles_to_impls[m_handle] = NULL;
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

	static void callbackDisplay() {
		m_handles_to_impls[glutGetWindow()]->mp_listener->onWindowRepaint();
	}

	static void callbackReshape(int new_width, int new_height) {
		impl * pimpl = m_handles_to_impls[glutGetWindow()];
		int old_width = pimpl->m_width;
		int old_height = pimpl->m_height;
		pimpl->m_width = new_width;
		pimpl->m_height = new_height;
		pimpl->mp_listener->onWindowResized(old_width, old_height,
				new_width, new_height);
	}

};

// Constructor
Window::Window(const string & name, int width, int height, int x, int y):
		pimpl(NULL) {
	pimpl = new impl(name, width, height, x, y);
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

// Set/Unset windows events listener
void Window::setWindowEventsListener(WindowEventsListener * p_listener) {
	//pimpl->mp_window_listener = p_listener;
}

// Get the current windows events listener
WindowEventsListener * Window::getWindowEventsListener() {
	//return pimpl->mp_window_listener;
}
}
