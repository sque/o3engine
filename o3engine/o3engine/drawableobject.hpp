#ifndef O3ENGINE_DRAWABLE_H_INCLUDED
#define O3ENGINE_DRAWABLE_H_INCLUDED

// Internal
#include "./prereqs.hpp"
#include "./material.hpp"
#include "./singletonmanager.hpp"

namespace o3engine {
	/**
	 @brief Antikeimeno pou mporei na topothetithei se komvo
	 */
	class DrawableObject: ManagedObject<ObjectManager, string, DrawableObject> {
	protected:
		//! Name of this object
		string m_name;

	public:
		//! Constructor
		DrawableObject(const string & name);

		//! Destrcutor
		virtual ~DrawableObject();

		//! Render the solid part of object
		virtual void draw() = 0;

		//! Get name of object
		inline const string & getName() const {
			return m_name;
		}
	};
}

// Include object manager
#include "./objectmanager.hpp"

#endif
