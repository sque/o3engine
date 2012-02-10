#include "./window.hpp"

namespace o3engine {

	float Window::getAspectRatio() const{
		return getHeight()/getWidth();
	}

}

