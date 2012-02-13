#include "./offscreen.hpp"
#include <stdexcept>

namespace o3engine {

	class OffScreen::impl {
	public:
		int width;
		int height;
		Color m_back_color;

		impl(int w, int h) :
			width(w), height(h),
			m_back_color(Color::BLACK){

		}
	};

	OffScreen::OffScreen(int width, int height) {
		pimpl = new impl(width, height);
	}

	OffScreen::~OffScreen(){
		delete pimpl;
	}

	int OffScreen::getHeight() const{
		return pimpl->height;
	}

	int OffScreen::getWidth() const{
		return pimpl->width;
	}

	void OffScreen::resize(int width, int height) {
		throw new std::logic_error("Offscreen does not support resizing.");
	}


	void OffScreen::setBackColor(const Color & col) {
		pimpl->m_back_color = col;
	}

	const Color & OffScreen::getBackColor() const {
		return pimpl->m_back_color;
	}

}


