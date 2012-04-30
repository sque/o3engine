#ifndef O3ENGINE_DRAWABLE_HPP_INCLUDED
#define O3ENGINE_DRAWABLE_HPP_INCLUDED

// Internal
#include "./prereqs.hpp"
#include "./material.hpp"
#include "./singletonmanager.hpp"

namespace o3engine {

	//! Interface of SceneRender visitor object
	struct SceneRendererVisitor {

		//! Helper to populate a GPU program with all state uniforms
		virtual void preDraw(ogl::program * target) = 0;

		//! Inheritable
		virtual ~SceneRendererVisitor(){}
	};

	/**
	 @brief Object that can be attached to a Node and provide draw API.
	 */
	class DrawableObject: ManagedObject<ObjectManager, string, DrawableObject> {
	protected:

		//! Name of this object
		string m_name;

	public:
		//! Constructor
		DrawableObject(const string & name);

		//! Destructor
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
