#ifndef PARTICLESYSTEM_H_INCLUDED
#define PARTICLESYSTEM_H_INCLUDED

#include "./prereqs.hpp"
#include "./drawableobject.hpp"

// STL libraries
#include <vector>

namespace o3engine
{
	// Class for particle inheritance
	class Particle
	{
	protected:

	public:
		inline Particle(){}
		inline virtual ~Particle(){}

		inline virtual void onRender() = 0;
		inline virtual void onInit() = 0;
		inline virtual void onTimePass(Real secs) = 0;
		inline virtual void onSetParameter(int par_name, const void * par_value){};

	};

	template<class TP>
	class ParticleSystem : public DrawableObject
	{
	protected:
		vector<TP *> v_particles;

		// Event functions to be triggered before and after render of particles
		// usefull for changing state of the machine
		virtual void OnPreRender(){};
		virtual void OnPostRender(){};

	public:
		ParticleSystem(const string & name, int pSize)
			: DrawableObject(name)
		{   TP * pT;
			for(int i = 0;i < pSize; i ++)
			{
				pT = new TP;
				v_particles.push_back(pT);
				pT->onInit();

			}
		}

		virtual ~ParticleSystem()
		{   TP * pT;
			typename vector<TP *>::iterator it;

			// Delete all objects
			for(it = v_particles.begin();it != v_particles.end();it++)
			{
				pT = *it;
				delete pT;
			}
			v_particles.clear();

		}

		virtual void drawSolidPart(){}

		// draw all particles
		virtual void drawTransperantPart()
		{   typename vector<TP *>::iterator it;

			// Call pre render
			OnPreRender();

			// Render particles
			for(it = v_particles.begin();it != v_particles.end();it++)
			{
				(*it)->onRender();
			}

			// Call post render
			OnPostRender();
		}

		// Feed with time
		inline void timePulse(Real secs)
		{   typename vector<TP *>::iterator it;

			// Render particles
			for(it = v_particles.begin();it != v_particles.end();it++)
			{   (*it)->onTimePass(secs);   }
		}

		// Reset particle system (reinitalize all particles)
		inline void reset()
		{   typename vector<TP *>::iterator it;

			for(it = v_particles.begin();it != v_particles.end();it++)
			{
				(*it)->onInit();
			}
		}

		// Set particle parameters
		inline void setParameter(int par_name, const void * par_value)
		{   typename vector<TP *>::iterator it;

			for(it = v_particles.begin();it != v_particles.end();it++)
			{
				(*it)->onSetParameter(par_name, par_value);
			}
		}

		inline bool hasTransperant()
		{	return true;	}
	};
}
#endif // PARTICLESYSTEM_H_INCLUDED
