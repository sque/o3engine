#include "./objectmanager.hpp"

namespace o3engine
{
//- SingletonManager Initialization
template<> ObjectManager* SingletonManager<ObjectManager, string, DrawableObject>::ms_singleton = 0;
}
