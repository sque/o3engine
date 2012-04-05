#include "./drawableobject.hpp"
#include "./materialmanager.hpp"

namespace o3engine
{
	// Constructor
	DrawableObject::DrawableObject(const string & name) :
		ManagedObject<ObjectManager, string, DrawableObject>(name),
		m_name(name) {
	}

	DrawableObject::~DrawableObject()
	{
	}

}
