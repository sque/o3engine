#include "./light.hpp"

namespace o3engine {
	// Default Constructor
	Light::Light() {
		// Set default parameters
		m_spot_cutoff = 45.0;
		m_type = LIGHT_DIRECTIONAL;
		m_spot_cutoff = 45.0f;
		m_direction = Vector3::UNIT_Z;
		m_ambient = Color::BLACK;
		m_diffuse = Color::WHITE;
		m_specular = Color::WHITE;
		m_enabled = false;
	}

	void glLight(const Light & light, GLint gl_light_enum) {
		// enable light
		if (light.m_enabled)
			glEnable(gl_light_enum);
		else {
			glDisable(gl_light_enum);
			return;
		}

		// Set colors
		glLight(gl_light_enum, GL_SPECULAR, light.m_specular);
		glLight(gl_light_enum, GL_DIFFUSE, light.m_diffuse);
		glLight(gl_light_enum, GL_AMBIENT, light.m_ambient);

		// Set positions and shit
		switch (light.m_type) {
		case Light::LIGHT_DIRECTIONAL:
			// Direction of light
			glLight(gl_light_enum, GL_POSITION, light.m_direction, 0);
			glLightf(gl_light_enum, GL_SPOT_CUTOFF, 180.0);
			break;
		case Light::LIGHT_POSITIONAL:
			// Set cut off to nothing
			glLightf(gl_light_enum, GL_SPOT_CUTOFF, 180.0);
			glLight(gl_light_enum, GL_POSITION, light.m_direction, 1);
			break;
		case Light::LIGHT_SPOT:
			// Set cut off
			glLight(gl_light_enum, GL_POSITION, light.m_direction, 1);
			glLightf(gl_light_enum, GL_SPOT_CUTOFF, (GLfloat) light.m_spot_cutoff);
			break;
		}
	}
}
