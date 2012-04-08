#include "perspectivecamera.hpp"

namespace o3engine {

	void PerspectiveCamera::calcProjMatrix() {
		m_proj_matrix = perspective(m_fovy, m_aspect_ratio, m_znear, m_zfar);
	}

	void PerspectiveCamera::onStateAltered(){
		//setAspectRatio((double)mp_state->width / (double)mp_state->height);
	}

}
