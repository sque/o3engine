#ifndef O3ENGINE_LIGHT_HPP_INCLUDED
#define O3ENGINE_LIGHT_HPP_INCLUDED

#include "./prereqs.hpp"

namespace o3engine {

	//! A light object that can be attached in any node
	/**
	 * To create a light, just create a new object from this class
	 * with some unique name. <b>NOTICE</b>: Light is off by default,
	 * you must turn it on. Lights inherit direction by the node
	 * they are attached, this is also valid for directional light.
	 * @todo Remake it
	 */
	class Light {
	public:
		//! The types of lights
		enum E_LIGHT_TYPES {
			LIGHT_POSITIONAL, 	//!< Positional light
			LIGHT_DIRECTIONAL, 	//!< Directional light
			LIGHT_SPOT
		//!< Spot light
		};

	private:
		E_LIGHT_TYPES m_type; 	//!< The current type of light
		Degree m_spot_cutoff; 	//!< Spotlight cutoff
		Vector3 m_direction; 	//!< Direction of light (directional, and spot)
		Color m_ambient; 		//!< Ambient color
		Color m_diffuse; 		//!< Diffuse color
		Color m_specular; 		//!< Specular color
		bool m_enabled; 		//!< If light is enabled

	public:
		//! Constructor a new light with default values
		Light();

		//! Switch light on or off
		inline void switchLight() {
			m_enabled = !m_enabled;
		}

		//! Set enabled light
		inline void setEnabled(bool enabled) {
			m_enabled = enabled;
		}

		//! Set diffuse color
		inline void setDiffuse(const Color & diffuse) {
			m_diffuse = diffuse;
		}

		//! Set ambient color
		inline void setAmbient(const Color & ambient) {
			m_ambient = ambient;
		}

		//! Set specular color
		inline void setSpecular(const Color & specular) {
			m_specular = specular;
		}

		//! Check if light is enabled
		inline bool isEnabled() const {
			return m_enabled;
		}

		//! Set direction of light
		/**
		 @remarks You must give a normalized vector!
		 */
		inline void setDirection(const Vector3 & direction) {
			m_direction = direction;
		}

		//! Set type of light
		inline void setType(E_LIGHT_TYPES type) {
			m_type = type;
		}

		//! Set the spotlight cut off angle
		inline void setSpotCutOffAngle(const Angle & cutoff) {
			m_spot_cutoff = cutoff;
		}

		//! Get ambient color
		inline const Color & getAmbient() const {
			return m_ambient;
		}

		//! Get diffuse color
		inline const Color & getDiffuse() const {
			return m_diffuse;
		}

		//! Get specular color
		inline const Color & getSpecular() const {
			return m_specular;
		}

		//! Get direction of light
		inline const Vector3 & getDirection() const {
			return m_direction;
		}

		//! Get type of light
		inline const E_LIGHT_TYPES & getTypeOfLight() const {
			return m_type;
		}

		//! Get the spotlight cutoff angle
		inline const Degree & getSpotCutOffAngle() const {
			return m_spot_cutoff;
		}

		friend void glLight(const Light & light, GLint gl_light_enum);
	};

	//! Draw light in opengl contex
	/**
	 * @ingroup gl_supprt
	 */
	void glLight(const Light & light, GLint gl_light_enum);

}

#endif
