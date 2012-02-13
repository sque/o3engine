#include "./surface.hpp"
#include <algorithm>
namespace o3engine {

	Surface::Surface(){
	}

	Surface::~Surface(){
	}

	float Surface::getAspectRatio() const {
		return getHeight() / getWidth();
	}

	void Surface::attachSurfaceListener(SurfaceListener & listener) {
		m_sfc_listeners.push_back(&listener);
	}

	bool Surface::detachSurfaceListener(SurfaceListener & listener) {
		surface_listeners_type::iterator it = std::find(m_sfc_listeners.begin(),
				m_sfc_listeners.end(), &listener);
		if (it != m_sfc_listeners.end()) {
			m_sfc_listeners.erase(it);
			return true;
		}
		return false;
	}

	// Call repaint event
	void Surface::requestRepaint() {
		for(surface_listeners_type::iterator it = m_sfc_listeners.begin();
				it != m_sfc_listeners.end();it++) {
			(*it)->onSurfaceRepaint();
		}
	}
}
