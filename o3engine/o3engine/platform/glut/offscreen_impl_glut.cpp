#include "./../offscreen.hpp"
#include "./glut_state.hpp"
#include <stdexcept>

namespace o3engine {

	class OffScreen::impl {
	public:

		//! Width of surface
		int width;

		//! Height of surface
		int height;

		//! Clear color
		Color m_back_color;

		//! Replicated static pointer
		static GLUTState * ms_gstate;

		//! Owner of this private implementation.
		OffScreen * mp_offscreen;

		impl(OffScreen * poffscreen, int w, int h) :
			width(w), height(h),
			m_back_color(Color::BLACK),
			mp_offscreen(poffscreen){

			ms_gstate = GLUTState::getSingletonPtr();
			ms_gstate->pushOffscreen(poffscreen);
		}

		~impl(){
			ms_gstate->removeOffscreen(mp_offscreen);
		}
	};

	GLUTState * OffScreen::impl::ms_gstate = 0;

	OffScreen::OffScreen(int width, int height) {
		pimpl = new impl(this, width, height);
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


