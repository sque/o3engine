#include "./light.hpp"

namespace o3engine {
	// Default Constructor
	Light::Light() :
		m_ambient(Color(0.1, 0.1, 0.1, 1)),
		m_diffuse(Color::WHITE),
		m_specular(Color::WHITE),
		m_direction(Vector3::NEGATIVE_UNIT_Z),
		m_spot_cutoff(45.0f),
		m_type(ETYPE::DIRECTIONAL),
		m_enabled(true){
	}
}
