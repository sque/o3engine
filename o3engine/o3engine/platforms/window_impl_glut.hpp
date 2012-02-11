#ifndef WINDOW_IMPL_GLUT_HPP_
#define WINDOW_IMPL_GLUT_HPP_

#include "./window.hpp"

namespace o3engine {

// Internal implementation of platform
	class Window::impl {
	public:
		friend class InputProcessor;
		static std::vector<impl *> m_handles_to_impls;
		string m_name;
		string m_title;
		int m_height;
		int m_width;
		int m_handle;
		Color m_back_color;
		int m_pos_x;
		int m_pos_y;
		WindowEventsListener * mp_listener;
		InputProcessor * mp_inputprocessor;


		impl(const string & name, int w, int h, int x, int y, InputProcessor * p_ip) :
				m_name(name), m_height(h), m_width(w),
				m_back_color(Color::BLACK),
				m_pos_x(x), m_pos_y(y), mp_listener(NULL),
				mp_inputprocessor(p_ip) {

			::glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ACCUM);
			::glutInitWindowSize(m_width, m_height);
			::glutInitWindowPosition(m_pos_x, m_pos_y);
			m_handle = ::glutCreateWindow("");

			// Save pointer of current window
			m_handles_to_impls.resize(m_handle + 1);
			m_handles_to_impls[m_handle] = this;

			// Setup Callback functions
			::glutReshapeFunc(impl::callbackReshape);
			::glutDisplayFunc(impl::callbackDisplay);
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

		void implCallbackDisplay() {
			glClearColor(m_back_color);
			::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			::glFlush();

			// Swap Buffers
			::glutSwapBuffers();
		}

		void implCallbackReshape(int new_width, int new_height) {
/*
 * impl * pimpl = m_handles_to_impls[glutGetWindow()];
			int old_width = pimpl->m_width;
			int old_height = pimpl->m_height;
			pimpl->m_width = new_width;
			pimpl->m_height = new_height;
			pimpl->mp_listener->onWindowResized(old_width, old_height,
					new_width, new_height);
 */
		}

		static void callbackDisplay() {
			m_handles_to_impls[glutGetWindow()]->implCallbackDisplay();
		}

		static void callbackReshape(int new_width, int new_height) {
			m_handles_to_impls[glutGetWindow()]->implCallbackReshape(new_width, new_height);

		}

	};

}

#endif /* WINDOW_IMPL_GLUT_HPP_ */
