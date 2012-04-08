#ifndef PARTICLESYSTEM_H_INCLUDED
#define PARTICLESYSTEM_H_INCLUDED

#include "./prereqs.hpp"
#include "./drawableobject.hpp"

// STL libraries
#include <vector>

namespace o3engine {
	// Class for particle inheritance
	class Particle {
	public:
		inline Particle() {
		}
		inline virtual ~Particle() {
		}

		inline virtual void onRender() = 0;
		inline virtual void onInit() = 0;
		inline virtual void onTimePass(Real secs) = 0;
		inline virtual void onSetParameter(int par_name, const void * par_value) {
		}
	};

	template<class ParticleType>
	class ParticleSystem: public DrawableObject {
	public:

		//! Type of this particle
		typedef ParticleType particle_type;

		//! Type of particles container
		typedef std::vector<particle_type *> particles_container_type;

		//! Constructor
		ParticleSystem(const string & name, size_t total) :
				DrawableObject(name) {
			particle_type * ppart;
			for (size_t i = 0; i < total; i++) {
				ppart = new particle_type();
				m_particles.push_back(pT);
				ppart->onInit();

			}
		}

		virtual ~ParticleSystem() {
			// Delete all objects
			for (auto & ppart : m_particles) {
				delete ppart;
			}
		}

		virtual void drawSolidPart() {
		}

		// draw all particles
		virtual void drawTransperantPart() {
			// Call pre render
			onPreRender();

			// Render particles
			for (auto & ppart : m_particles) {
				ppart->onRender();
			}

			// Call post render
			onPostRender();
		}

		// Feed with time
		inline void timePulse(Real secs) {
			// Render particles
			for (auto & ppart : m_particles) {
				ppart->onTimePass(secs);
		}

		// Reset particle system (reinitalize all particles)
		inline void reset() {
			for (auto & ppart : m_particles) {
				ppart->onInit();
			}
		}

		// Set particle parameters
		inline void setParameter(int par_name, const void * par_value) {
			// TODO: This can be improved by using a common storage for parameters
			for (auto & ppart : m_particles) {
				ppart->onSetParameter(par_name, par_value);
			}
		}

	protected:
		//! Particles list
		particles_container_type m_particles;

		// Event functions to be triggered before and after render of particles
		// usefull for changing state of the machine
		virtual void onPreRender() {
		}

		virtual void onPostRender() {
		}
	};
}
#endif // PARTICLESYSTEM_H_INCLUDED
