#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include "./prereqs.hpp"
#include "./texture.hpp"
#include "./singletonmanager.hpp"
#include <map>
namespace o3engine
{
	//! TextureManager
	class TextureManager : public SingletonManager<TextureManager, string, Texture>
	{
	public:

		//! Constructor
		TextureManager(){}

		//! Destructor
		virtual ~TextureManager(){}
	};
}
#endif // TEXTUREMANAGER_H_INCLUDED
