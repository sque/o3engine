#include "./skinnedobject.hpp"
#include "./materialmanager.hpp"

namespace o3engine
{
	// Constructor
	SkinnedObject::SkinnedObject(const string & name)
		:DrawableObject(name)
	{
		// Add default material
		pMaterial = MaterialManager::getSingletonPtr()->getDefaultMaterialPtr();
		bTransperant = false;
	}

	SkinnedObject::~SkinnedObject()
	{
	}

	void SkinnedObject::setMaterial(const string & mat_name)
	{
		// Get material
		setMaterial(MaterialManager::getObjectPtr(mat_name));
	}
}
