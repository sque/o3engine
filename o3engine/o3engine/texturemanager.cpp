#include "./texturemanager.hpp"

namespace o3engine {
	//- SingletonManager Initialization
	template<> TextureManager* SingletonManager<TextureManager, string, Texture>::ms_singleton = 0;

}
