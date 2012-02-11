#include "./window.hpp"
#include <algorithm>

namespace o3engine {

	float Window::getAspectRatio() const{
		return getHeight()/getWidth();
	}

	void Window::attachWindowEventsListener(WindowEventsListener & listener) {
		m_wnd_listeners.push_back(&listener);
	}

	bool Window::detachWindowEventsListener(WindowEventsListener & listener) {
		window_listeners_type::iterator it = std::find(m_wnd_listeners.begin(), m_wnd_listeners.end(), &listener);
		if (it != m_wnd_listeners.end()) {
			m_wnd_listeners.erase(it);
			return true;
		}
		return false;
	}
}

