#ifndef O3ENGINE_DRAWABLE_H_INCLUDED
#define O3ENGINE_DRAWABLE_H_INCLUDED

// Internal
#include "./prereqs.hpp"
#include "./material.hpp"
#include "./singletonmanager.hpp"

namespace o3engine {

	//! Object that will hold scenerender parameters
	struct SceneRendererVisitor {

		//! Helper to populate a gpu program with scene parameters
		virtual void populateSceneParameters(ogl::program * target) = 0;

		//! Inheritable
		virtual ~SceneRendererVisitor(){}
	};

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
		virtual void draw(SceneRendererVisitor * pvisitor) = 0;

		//! Get name of object
		inline const string & getName() const {
			return m_name;
		}
	};
}

// Include object manager
#include "./objectmanager.hpp"

#endif
