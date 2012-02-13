/**
 * @cond INTERNAL
 * Do not ever include this header. It is internal implementation
 */
#ifndef O3ENGINE_GLUT_STATE_HPP_INCLUDED
#define O3ENGINE_GLUT_STATE_HPP_INCLUDED

#include "./../prereqs.hpp"
#include <set>
#include <algorithm>

namespace o3engine {

	//! Internal GLUT implementation state holder
	class GLUTState : public Singleton<GLUTState>{
	public:

		//! Class with all attributes of a window
		struct GLUTWindowState {
			Window * mp_wnd;
			int	m_glut_id;
			InputProcessor * mp_input_proc;
		};

		typedef std::set<Window *> windows_type;
		typedef std::vector<Window *> glut_to_windows_type;
		typedef std::set<OffScreen *> offscreens_type;

		//! A list with all windows
		windows_type m_windows;

		//! A map from glut ids to Window objects
		glut_to_windows_type m_glut_to_windows;

		//! A list with all off-screens
		offscreens_type m_offscreens;

		//! Check if it has off-screens
		inline bool has_offscreens() {
			return (m_offscreens.size() != 0);
		}

		//! Check if there are windows
		inline bool has_windows() {
			return (m_windows.size() != 0);
		}

		inline void push_window(Window * pwnd, int glut_wnd_id, InputProcessor * pinproc) {
			m_windows.insert(pwnd);
			m_glut_to_windows.resize(glut_wnd_id + 1);
			m_glut_to_windows[glut_wnd_id] = pwnd;
		}

		inline void remove_window(Window * pwnd) {

			windows_type::iterator it = std::find(m_windows.begin(), m_windows.end(), pwnd);
			if (it != m_windows.end())
				m_windows.erase(it);

			glut_to_windows_type::iterator g2w_it = std::find(
					m_glut_to_windows.begin(), m_glut_to_windows.end(), pwnd);
			if (g2w_it != m_glut_to_windows.end())
				*g2w_it = NULL;
		}
	};

}

#endif
//! @endcond
