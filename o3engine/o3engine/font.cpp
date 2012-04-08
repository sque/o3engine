#include "./font.hpp"

//FreeType Headers
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

#include <stdexcept>

namespace o3engine
{
	void _extract_glyph(FT_Face ftFace,
		unsigned char ch,
		Image & img,
		int &startX,
		int &startY,
		Font::CharGlyph & descChar,
		int maxWidth,
		int & maxLineHeight)
	{
		// Variables
		FT_Glyph glyph;
		int glyp_width;
		int glyp_height;

		// Load glyph of character
		if(FT_Load_Glyph( ftFace, FT_Get_Char_Index( ftFace, ch ), FT_LOAD_DEFAULT ))
			throw std::runtime_error("FT_Load_Glyph failed");

		//Move the face's glyph into a Glyph object.
		if(FT_Get_Glyph( ftFace->glyph, &glyph ))
			throw std::runtime_error("FT_Get_Glyph failed");

		//Convert the glyph to a bitmap.
		FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

		//This reference will make accessing the bitmap easier
		FT_Bitmap& bitmap=bitmap_glyph->bitmap;

		// Read info of bitmap
		glyp_width = bitmap.width;
		glyp_height = bitmap.rows;

		// Calculate line wrapping
		if (startX + glyp_width > maxWidth)
		{
			startY += maxLineHeight;
			startX = 0;
			maxLineHeight = 0;
		}

		// max line height
		if (maxLineHeight < glyp_height)
			maxLineHeight = glyp_height;

		// Save info of Glyph
		descChar.realChar = ch;
		descChar.texX = (Real)startX/1024.0;
		descChar.texY = (Real)startY/1024.0;
		descChar.Height = glyp_height;
		descChar.Width = glyp_width;
		descChar.texH = (Real)glyp_height/1024.0;
		descChar.texW = (Real)glyp_width/1024.0;
		descChar.VBaseLine = glyp_height - bitmap_glyph->top;
		descChar.HBaseLine = bitmap_glyph->left;
		descChar.advance = ftFace->glyph->advance.x >> 6;

		// Create glyphs kerning map
		if (FT_HAS_KERNING(ftFace))
		{	FT_UInt cur_glyph_index = FT_Get_Char_Index( ftFace, ch);
			FT_Vector delta;
			FT_UInt left_glyph_index;


			for (unsigned char chl = 0; chl < 127; chl++)
			{	left_glyph_index = FT_Get_Char_Index( ftFace, chl);

				// Calculate kerning
				FT_Get_Kerning(
					ftFace,
					left_glyph_index,
					cur_glyph_index,
					FT_KERNING_DEFAULT,
					&delta
				);

				// Save kerning
				descChar.left_kerning[chl] = delta.x >> 6;;
			}
		}

		// Copy bitmap to glyph
		for(int j = 0; j < glyp_width; j++)
			for(int k = 0; k < glyp_height; k++)
			{
				// Create an image with alpha channel from grey one
				img.pixel(j+startX, k+startY) =
				    color_rgba_t(255, 255, 255, bitmap.buffer[j + bitmap.pitch*(glyp_height - k - 1)]);

				// Debug baselines
				/*if ((( bitmap_glyph->left == j) || ((glyp_height - bitmap_glyph->top ) == k)) && (ch != ' '))
					img.setTexel(
					j+startX,
					k+startY,Color::RED);*/
			}

		// Increment startX
		startX += glyp_width;

		// Free space
		FT_Done_Glyph(glyph);
	}

	void Font::_create_texture(const string & font_file)
	{

		// Fire-up FreeType library (gimme power)
		FT_Library library;
		if (FT_Init_FreeType( &library ))
			throw std::runtime_error("FT_Init_FreeType failed");

		// The font face of the font
		FT_Face fntFace;

		// Load the font by reading file
		if (FT_New_Face( library, font_file.c_str(), 0, &fntFace ))
			throw std::runtime_error("FT_New_Face failed (there is probably a problem with your font file)");

		//For some twisted reason, Freetype measures font size
		//in terms of 1/64ths of pixels.  Thus, to make a font
		//h pixels high, we need to request a size of h*64.
		//(h << 6 is just a prettier way of writting h*64)
		FT_Set_Char_Size( fntFace, FontHeight << 6, FontHeight << 6, 96, 96);

		// Get some info from font face
		bKerning = FT_HAS_KERNING(fntFace);
		LineSpace = fntFace->height >> 6;

		// Initialize characters
		glyphs.resize(128);

		// Let's create the image with font glyphs
		Image imgFontMap(1024, 1024, Color(0,0,0,0));
		int startX = 0;
		int startY = 0;
		int maxLineHeight = 0;
		for(unsigned char ch = 0; ch < 128; ch++)
		{
			_extract_glyph(fntFace, ch, imgFontMap, startX, startY, glyphs[ch], 1024, maxLineHeight);
			glyphs[ch].prepareQuad();
		}

		// And here we create the texture with font map
		char tex_name[256];
		sprintf(tex_name, "FontMap_%s_%d_", font_file.c_str(), FontHeight);
		// TODO: pTexture_FontMap = new Texture(tex_name, imgFontMap);

		//We don't need the face information now that the display
		//lists have been created, so we free the assosiated resources.
		FT_Done_Face(fntFace);

		//Ditto for the library.
		FT_Done_FreeType(library);
	}

	Font::Font(const string & font_file, int _height)
	{	FontHeight = _height;

		// Create map fonts from glyph
		_create_texture(font_file);
	}

	void Font::debug(int w, int h)
	{
		glEnable(GL_TEXTURE_2D);
		//pTexture_FontMap->glBind2d();
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);	glVertex2d(0,0);
			glTexCoord2f(0,1);	glVertex2d(0,h);
			glTexCoord2f(1,1);	glVertex2d(w,h);
			glTexCoord2f(1,0);	glVertex2d(w,0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	// Read a hex chunk and translate to byte
	unsigned char Font::readHexChunk(const char * hex)
	{	unsigned char tmp = 0;

		for(int i = 0;i < 2;i++)
		{
			if((*hex >= '0') && (*hex <= '9'))
				tmp |= *hex - '0' ;

			else if((*hex >= 'A') && (*hex <= 'F'))
				tmp |= (*hex - 'A' + 10);

			else if((*hex >= 'a') && (*hex <= 'f'))
				tmp |= (*hex - 'a' + 10);

			// shift left
			if (i == 0)
				tmp <<= 4;

			// pame next gramma
			++hex;
		}
		return tmp;
	}

	// Internal function to parse a color from string
	int Font::applyColor(const char *col_str)
	{	Color selColor;
		unsigned char rgb[3];

		// Check that it can fit
		for(int i = 0;i < 8;i++)
			if (col_str[i] == '\0')
				return 0;

		// Check ending
		if (col_str[7] != ';')
			return 0;

		// parse 2 first chunks of hex
		rgb[0] = readHexChunk(col_str + 1);
		rgb[1] = readHexChunk(col_str + 3);
		rgb[2] = readHexChunk(col_str + 5);

		// Set colors
		selColor.assignAsRGBA(color_rgba_t(rgb[0], rgb[1], rgb[2], 255));

		// Apply color
		glColor4(selColor);
		return 7;
	}

	void Font::print(Vector3 pos, const Color & text_color, const char * str)
	{	CharGlyph * pPrevGlyph = NULL;
		int jump_lets;

		glEnable(GL_TEXTURE_2D);
		//pTexture_FontMap->glBind2d();
		glColor4(text_color);

			// Initialize position
			glPushMatrix();
            glTranslate(pos);

			// Loop arround all characters
			str--;
			while(*(++str))
			{
				// Skip extended
				if ((unsigned char)(*str) > 0x80)
					continue;

				// Calculate new line
				if ((*str) == '\n')
				{
					pPrevGlyph = NULL;
					glPopMatrix();
					glPushMatrix();
					pos.y = pos.y - LineSpace;
                    glTranslate(pos);
					continue;
				}

				// Process inline color
				if ((*str) == '&')
				{	str += (jump_lets = applyColor(str));
					if (jump_lets)
						continue;

					// Process restore original color
					if (str[1] == ';')
					{	glColor4(text_color);
						str += 1;
						continue;
					}
				}

				// Get character glyph
				CharGlyph &curGlyph = glyphs[*str];

				// Move pen's position
				curGlyph.advancePen(pPrevGlyph, bKerning);

				// Print glyph
				curGlyph.renderQuad();

				// Save previous glyph
				pPrevGlyph = &curGlyph;
			}
			glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}

	// Used to display a quad with part of current texture
	void Font::CharGlyph::renderQuad()
	{
		glBegin(GL_QUADS);
			glTexCoord2f(tex_Hor_low, tex_Ver_low);		glVertex2d(vertx_Hor_low, vertx_Ver_low);
			glTexCoord2f(tex_Hor_low, tex_Ver_high);	glVertex2d(vertx_Hor_low, vertx_Ver_high);
			glTexCoord2f(tex_Hor_high, tex_Ver_high);	glVertex2d(vertx_Hor_high, vertx_Ver_high);
			glTexCoord2f(tex_Hor_high, tex_Ver_low);	glVertex2d(vertx_Hor_high, vertx_Ver_low);
		glEnd();
	}

	void Font::CharGlyph::prepareQuad()
	{	// Calculate position of texture and vertex
		tex_Hor_low = texX;
		tex_Hor_high = texX + texW;
		tex_Ver_low = texY;
		tex_Ver_high = texY + texH;

		vertx_Hor_low = HBaseLine;
		vertx_Hor_high = Width + HBaseLine;
		vertx_Ver_low = - VBaseLine;
		vertx_Ver_high = Height - VBaseLine;

	}
	// Advance pen
	void Font::CharGlyph::advancePen(CharGlyph * pleft, bool kern)
	{	map<char, int>::iterator it;
		int totalAdvance;
		// Skip if no left
		if (pleft == NULL) return;

		// Advance the nominal
		totalAdvance = pleft->advance;

		// Kerning
		if (kern)
			if ((it = left_kerning.find(pleft->realChar)) != left_kerning.end())
				totalAdvance += it->second;

		// Actual advance
		glTranslated(totalAdvance, 0, 0);
	}

	void Font::printf(Vector3 pos, const Color & text_color, const char *fmt, ...)
	{
		char		text[1024];	// Temporary buffer
		va_list		ap;

		if (fmt == NULL)
			*text=0;
		else
		{
			va_start(ap, fmt);
			vsprintf(text, fmt, ap);
			va_end(ap);
		}

		print(pos, text_color, text);
	}
}
