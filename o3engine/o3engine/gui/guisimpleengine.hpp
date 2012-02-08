#ifndef GUISIMPLEENGINE_H_INCLUDED
#define GUISIMPLEENGINE_H_INCLUDED

#include "../prereqs.hpp"
#include "./guiengine.hpp"

namespace o3engine
{
    /**
    @ingroup gui_group
    */
	class GuiSimpleEngine : public GuiEngine
	{
	protected:

		enum E_BACKGROUNDS
		{
			BG_FRAME_NORMAL = 0,
			BG_MAX
		};

		// Background definition and renderer
		class BackgroundRenderer
		{
		public:
			// Enumeration of regions for each element
			enum E_REGIONS
			{
				REGION_TOP_LEFT = 0,
				REGION_TOP,
				REGION_TOP_RIGHT,
				REGION_LEFT,
				REGION_MIDDLE,
				REGION_RIGHT,
				REGION_BOTTOM_LEFT,
				REGION_BOTTOM,
				REGION_BOTTOM_RIGHT,
				REGION_MAX
			};

			// Descriptor for a region
			class Region
			{
			public:
				enum E_TYPE
				{
					TYPE_COLOR,
					TYPE_TEXTURE
				} type;

				Color mColor;
				Texture * pTexture;

				// Default constructor
				Region()
				{	type = TYPE_COLOR; mColor = Color::WHITE; pTexture = NULL;	}

				void modeTexture(Texture * _ptexture)
				{	pTexture = _ptexture; type = TYPE_TEXTURE;	}

				void modeColor(const Color & _col)
				{	mColor = _col; type = TYPE_COLOR;	}

				void render(Real left, Real bottom, Real right, Real top);
			} v_regions[REGION_MAX];

			Real split_left;
			Real split_right;
			Real split_top;
			Real split_bottom;

			void render(const Vector2 & size);

		} v_bgrenderer[BG_MAX];


		void _drawFrame(GuiFrame * p_frame, const Vector2 & size);
		void _drawButton(GuiButton * p_button, const Vector2 & size);

	public:
		GuiSimpleEngine(const char * theme_file);

		virtual void drawWnd(GuiWindow * p_wnd);
	};
}
#endif // GUISIMPLEENGINE_H_INCLUDED
