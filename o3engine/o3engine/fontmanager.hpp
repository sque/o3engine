#ifndef FONTMANAGER_H_INCLUDED
#define FONTMANAGER_H_INCLUDED

#include "./prereqs.hpp"
#include "./font.hpp"
#include <map>

namespace o3engine
{
	class FontManager: public Singleton<FontManager>
	{
	protected:
		map<string, Font *>		map_fonts;
		typedef map<string, Font *>::iterator FontIterator;

		string _fontHash(const string & fon_name, int height);
	public:

		// Constructor
		FontManager();

		// Destructor
		~FontManager();

		// Get a font from database
		Font * getFontPtr(const string & fon_name, int height);
	};
}
#endif // FONTMANAGER_H_INCLUDED
