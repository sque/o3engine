#include "./fontmanager.hpp"

namespace o3engine
{
	//- SINGLETON Initialization
	template<> FontManager* Singleton<FontManager>::ms_singleton = 0;


	// Constructor
	FontManager::FontManager()
	{
	}

	// Destructor
	FontManager::~FontManager()
	{	FontIterator it;

		for(it = map_fonts.begin();it != map_fonts.end();it++)
			delete it->second;
	}

	string FontManager::_fontHash(const string & fon_name, int height)
	{	char hash[256];

		sprintf(hash, "%s_||_%d", fon_name.c_str(), height);
		return hash;
	}

	// Get a font from database
	Font * FontManager::getFontPtr(const string & fon_name, int height)
	{	FontIterator it;
		string fhash = _fontHash(fon_name, height);

		// Check if font exists
		if ((it = map_fonts.find(fhash)) != map_fonts.end())
			return it->second;
		else
		{	Font * pTmpFont = new Font(fon_name, height);
			map_fonts[fhash] = pTmpFont;
			return pTmpFont;
		}
	}
}
