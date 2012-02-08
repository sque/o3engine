#ifndef MATERIALMANAGER_H_INCLUDED
#define MATERIALMANAGER_H_INCLUDED

#include "./prereqs.hpp"
#include "./material.hpp"
#include "./singletonmanager.hpp"

// STL
#include <map>

namespace o3engine
{
	class MaterialManager : public SingletonManager<MaterialManager, string, Material>
	{
	protected:

		// Map of materials
		int next_hashname;                                          // An increment number used to autohash materials

		//! Default material of engine
		Material * pDefaultMaterial;

		// Routines for parsing values from .material file
		Real _parse_value(const string & var);
		Color _parse_color3(const string & r, const string & g, const string & b);
		Color _parse_color4(const string & r, const string & g, const string & b, const string & a);
	public:
		// Constructor
		MaterialManager();

		// Destructor
		~MaterialManager();

		// Get default material
		inline const Material * getDefaultMaterialPtr() const { return pDefaultMaterial; }

		// Get default material
		inline const Material & getDefaultMaterial() const { return *pDefaultMaterial; }

		// Load materials file
		bool loadMaterials(const string & fname);
	};
}

#endif // MATERIALMANAGER_H_INCLUDED
