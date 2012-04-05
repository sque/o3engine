/**
 * @cond INTERNAL
 * Do not ever include this header. It is internal implementation
 */
#ifndef O3ENGINE_GLUT_STATE_HPP_INCLUDED
#define O3ENGINE_GLUT_STATE_HPP_INCLUDED

#include "./../../prereqs.hpp"
#include "./../offscreen.hpp"
#include <map>
#include <set>
#include <algorithm>

namespace o3engine {

	//! Internal GLUT implementation state holder
	class GLUTState : public Singleton<GLUTState>{
	public:

		//! Class with all attributes of a window
		struct WindowState {
			Window * mp_wnd;
			void * mp_wnd_pimpl;
			int	m_glut_id;
			InputProcessor * mp_input_proc;
		};

		typedef std::map<Window *, WindowState> wnd_to_wndstate_type;
		typedef std::map<int, WindowState> glut_to_wndstate_type;
		typedef std::set<OffScreen *> offscreens_type;

		//! Map windows based on windows pointer
		wnd_to_wndstate_type m_wnd_to_wndstate;

		//! Map windows based on windows pointer
		glut_to_wndstate_type m_glut_to_wndstate;

		//! A list of all off-screen surfaces
		offscreens_type m_offscreens;

		//! Check if glew is initialized
		bool m_glew_initialized;

		//! Pointer to function for controlling swap interval (Vsync)
		void (*mf_swap_interval)(int);

		GLUTState():
			m_glew_initialized(false){
		}

		//! Ask to initialize glew (if not yet)
		bool initializeGlew();

		//! Set swap interval
		bool swapInterval(int v);

		//! Check if it has off-screens
		inline bool hasOffscreens() {
			return (m_offscreens.size() != 0);
		}

		//! Check if there are windows
		inline bool hasWindows() {
			return (m_wnd_to_wndstate.size() != 0);
		}

		//! Push and index a window
		inline void pushWindow(Window * pwnd, void * pimpl, int glut_wnd_id, InputProcessor * pinproc) {
			WindowState wstate = {pwnd, pimpl, glut_wnd_id, pinproc};
			m_wnd_to_wndstate[pwnd] = wstate;
			m_glut_to_wndstate[glut_wnd_id] = wstate;
		}

		//! Remove a window from indexess
		inline void removeWindow(Window * pwnd) {

			m_glut_to_wndstate.erase(m_wnd_to_wndstate[pwnd].m_glut_id);
			m_wnd_to_wndstate.erase(pwnd);
		}

		//! Ask to repaint offscreen surfaces
		void redisplayOffscreens() {
			for(offscreens_type::iterator it = m_offscreens.begin();
					it != m_offscreens.end(); it++) {
				(*it)->requestRepaint();
			}
		}

		//! Push and index an offscreen surface
		void pushOffscreen(OffScreen * poff) {
			m_offscreens.insert(poff);
		}

		//! Remove an offscreen surface
		void removeOffscreen(OffScreen * poff) {
			m_offscreens.erase(poff);
		}
	};

}

#endif
//! @endcond
