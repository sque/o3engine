#ifndef OBJECTMANAGER_HPP_INCLUDED
#define OBJECTMANAGER_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./drawableobject.hpp"
#include "./singletonmanager.hpp"

// STL libraries
#include <map>

namespace o3engine
{
	/**
	 * Diaxeirizetai ola ta antikeimena pou exoume fortwsei (mesh, primative shapes..)
	 */
	class ObjectManager :public SingletonManager<ObjectManager, string, DrawableObject>
	{
	public:

		inline ObjectManager()
		{ }

		// Destructor
		virtual ~ObjectManager(){}
	};
}
#endif // OBJECTMANAGER_H_INCLUDED
