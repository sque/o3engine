#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "./prereqs.hpp"
#include "./texture.hpp"

#include <vector>
#include <map>

namespace o3engine
{
	//! Class for displaying text based on a font file.
	class Font
	{
	public:

		// Description of each character glyph
		class CharGlyph
		{
		protected:
			Real tex_Ver_low, tex_Ver_high;
			Real tex_Hor_low, tex_Hor_high;
			int vertx_Ver_low, vertx_Ver_high;
			int vertx_Hor_low, vertx_Hor_high;

		public:
			char realChar;					// The real character
			int Width;						// Width of font
			int Height;						// Height of font
			int VBaseLine;					// Vertical base line
			int HBaseLine;					// Horizontal base line
			Real texX;						// Starting Texture X position of font
			Real texY;						// Ending Texture  Y position of font
			Real texH;						// Height of glyph in texture
			Real texW;						// Width of glyph in texture
			int advance;					// Spacing of character
			map<char, int> left_kerning;	// Left kerning map

			// Default constructor
			CharGlyph(){}

			// Copy constructor
			CharGlyph(const CharGlyph & r)
			{	operator=(r);	}

			// Copy operator
			CharGlyph & operator=(const CharGlyph & r)
			{
				Width = r.Width;
				Height = r.Height;
				texX = r.texX;
				texY = r.texY;
				texH = r.texH;
				texW = r.texW;
				VBaseLine = r.VBaseLine;
				realChar = r.realChar;
				return *this;
			}

			// Create glyph kerning map
			void createKerningMap();

			// Prepare gl display quad
			void prepareQuad();

			// Used to display a quad with part of current texture
			void renderQuad();

			// Advance pen
			void advancePen(CharGlyph * pleft, bool kern);
		};

	protected:

		// Pointer to texture font
		Texture * pTexture_FontMap;

		// Height of font
		int FontHeight;

		// Line space
		int LineSpace;

		// Function to create font map texture
		void _create_texture(const string & font_file);

		// Array with character glyphs
		std::vector<CharGlyph> glyphs;

		// Kerning supported
		bool bKerning;

		// Internal function to parse a color from string and apply it
		int applyColor(const char *col_str);

		// Read a hex chunk and translate to byte
		unsigned char readHexChunk(const char * hex);
	public:
		// Create a texture from font map
		Font(const string & font_file, int _height);

		// shows the map of fonts in a quad
		void debug(int w, int h);

		// Print a static string
		void print(Vector3 pos, const Color & text_color, const char * str);

		// Print a custom formated string
		void printf(Vector3 pos, const Color & text_color, const char *fmt, ...);

		// Get line space;
		inline int getLineSpace() const
		{	return LineSpace;	}

		// Set line space
		inline void setLineSpace(int _sp)
		{	LineSpace = _sp;	}
	};
}
#endif // FONT_H_INCLUDED
