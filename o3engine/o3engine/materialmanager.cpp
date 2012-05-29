#include "./materialmanager.hpp"
#include "./string_functions.hpp"
#include "./texturemanager.hpp"
#include "./programmanager.hpp"

using namespace std;

namespace o3engine {

	//- SingletonManager Initialization
	template<> MaterialManager* SingletonManager<MaterialManager, string, Material>::ms_singleton = nullptr;

	// Constructor
	MaterialManager::MaterialManager() :
		mp_default_material(nullptr){
	}

	// Destructor
	MaterialManager::~MaterialManager() {
	}

	void MaterialManager::initialize() {
		ProgramManager::getSingleton().loadProgram("default", FileName("default.vert"), FileName("default.frag"));
		mp_default_material = new Material("default");
	}

}
