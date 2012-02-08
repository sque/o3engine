#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED

// Internal
#include "./prereqs.hpp"
#include "./material.hpp"
#include "./singletonmanager.hpp"

namespace o3engine
{
	/**
		@brief Antikeimeno pou mporei na topothetithei se komvo
	 */
	class DrawableObject : ManagedObject<ObjectManager, string, DrawableObject>
	{
	protected:
		//! Name of this object
		string Name;

	public:
		//! Constructor
		DrawableObject(const string & name);

		//! Destrcutor
		virtual ~DrawableObject();

		//! Render the solid part of object
		virtual void drawSolidPart() = 0;

		//! Render the transperant part of object
		virtual void drawTransperantPart() = 0;

		//! Check if it is transperant object
		virtual bool hasTransperant() = 0;

		//! Get name of object
		inline const string & getName() const	{	return Name;	}
	};
}
// Include object manager
#include "./objectmanager.hpp"

#endif // DRAWABLE_H_INCLUDED
