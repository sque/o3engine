#ifndef MATERIALMANAGER_H_INCLUDED
#define MATERIALMANAGER_H_INCLUDED

#include "./prereqs.hpp"
#include "./material.hpp"
#include "./singletonmanager.hpp"

// STL
#include <map>

namespace o3engine {
	//! Material manager
	class MaterialManager: public SingletonManager<MaterialManager, string, Material> {
	protected:
		//! Default material of engine
		Material * mp_default_material;

	public:
		// Constructor
		MaterialManager();

		// Destructor
		~MaterialManager();

		// Get default material
		inline const Material * getDefaultMaterialPtr() const {
			return mp_default_material;
		}

		// Get default material
		inline const Material & getDefaultMaterial() const {
			return *mp_default_material;
		}

		//! Initialize manager
		void initialize();

		// Load materials file
		bool loadMaterials(const string & fname);
	};
}

#endif // MATERIALMANAGER_H_INCLUDED
