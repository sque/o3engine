#include "./orthocamera.hpp"

namespace o3engine {

	void OrthoCamera::calcProjMatrix() {
		m_proj_matrix = ortho(m_left, m_right, m_bottom, m_top, m_znear, m_zfar);
	}
}
