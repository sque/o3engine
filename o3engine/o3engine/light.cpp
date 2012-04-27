#include "./light.hpp"

namespace o3engine {
	// Default Constructor
	Light::Light() {
		// Set default parameters
		m_spot_cutoff = 45.0;
		m_type = ETYPE::DIRECTIONAL;
		m_spot_cutoff = 45.0f;
		m_direction = Vector3::UNIT_Z;
		m_ambient = Color::BLACK;
		m_diffuse = Color::WHITE;
		m_specular = Color::WHITE;
		m_enabled = false;
	}
}
