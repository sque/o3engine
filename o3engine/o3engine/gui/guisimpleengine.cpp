#include "../texture.hpp"
#include "./guisimpleengine.hpp"
#include "./guiwindow.hpp"
#include "./guiframe.hpp"

namespace o3engine
{
	GuiSimpleEngine::GuiSimpleEngine(const char * theme_file)
	{
		// Frame renderer
		v_bgrenderer[BG_FRAME_NORMAL].split_left = 20;
		v_bgrenderer[BG_FRAME_NORMAL].split_right = 20;
		v_bgrenderer[BG_FRAME_NORMAL].split_top = 23;
		v_bgrenderer[BG_FRAME_NORMAL].split_bottom = 13;
		v_bgrenderer[BG_FRAME_NORMAL].v_regions[BackgroundRenderer::REGION_TOP_LEFT].modeTexture(new Texture("simple_theme_1", "themes/darkmac/wnd_top_left.png"));
		v_bgrenderer[BG_FRAME_NORMAL].v_regions[BackgroundRenderer::REGION_TOP].modeTexture(new Texture("simple_theme_2", "themes/darkmac/wnd_top.png"));
		v_bgrenderer[BG_FRAME_NORMAL].v_regions[BackgroundRenderer::REGION_TOP_RIGHT].modeTexture(new Texture("simple_theme_3", "themes/darkmac/wnd_top_right.png"));
		v_bgrenderer[BG_FRAME_NORMAL].v_regions[BackgroundRenderer::REGION_BOTTOM_LEFT].modeTexture(new Texture("simple_theme_4", "themes/darkmac/wnd_bottom_left.png"));
		v_bgrenderer[BG_FRAME_NORMAL].v_regions[BackgroundRenderer::REGION_BOTTOM].modeColor(Color(0.21, 0.21, 0.21, 1));
		v_bgrenderer[BG_FRAME_NORMAL].v_regions[BackgroundRenderer::REGION_BOTTOM_RIGHT].modeTexture(new Texture("simple_theme_6", "themes/darkmac/wnd_bottom_right.png"));

	}

	void GuiSimpleEngine::drawWnd(GuiWindow * p_wnd)
	{	const Vector2 & size = p_wnd->getSize();

		if (p_wnd->getClassName() == "builtin_root")
			return;
		else if (p_wnd->getClassName() == "builtin_frame")
			_drawFrame((GuiFrame *)p_wnd, size);
		else if (p_wnd->getClassName() == "builtin_button")
			_drawButton((GuiButton *)p_wnd, size);
		else
		{
			glColor4f(1, 1, 1, 0.5);
			glBegin(GL_QUADS);
				glVertex2f(0, 0);
				glVertex2f(0, size.y);
				glVertex2f(size.x, size.y);
				glVertex2f(size.x, 0);
			glEnd();
			printf("GuiSimpleEngine: [UNKNOWN CLASS] %s\n", p_wnd->getClassName().c_str());
		}
	}

	void GuiSimpleEngine::_drawFrame(GuiFrame * p_frame, const Vector2 & size)
	{
		// Draw background
		v_bgrenderer[BG_FRAME_NORMAL].render(size);

	}

	void GuiSimpleEngine::_drawButton(GuiButton * p_button, const Vector2 & size)
	{
	}

	void GuiSimpleEngine::BackgroundRenderer::Region::render(Real left, Real bottom, Real right, Real top)
	{
		if (type == TYPE_COLOR)
		{	glColor4(mColor);
			glBegin(GL_QUADS);
				glVertex2f(left,	bottom);
				glVertex2f(left,	top);
				glVertex2f(right,	top);
				glVertex2f(right,	bottom);
			glEnd();
		}
		else
		{	glColor4(Color::WHITE);
			glEnable(GL_TEXTURE_2D);
			pTexture->glBind2d();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex2f(left,	bottom);
				glTexCoord2f(0,1); glVertex2f(left,	top);
				glTexCoord2f(1,1); glVertex2f(right,	top);
				glTexCoord2f(1,0); glVertex2f(right,	bottom);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
	}

	void GuiSimpleEngine::BackgroundRenderer::render( const Vector2 & size)
	{
		// Calculate markers
		Real marker_left = split_left;
		Real marker_right = size.x - split_right;
		Real marker_bottom = split_bottom;
		Real marker_top = size.y - split_top;

		v_regions[REGION_TOP_LEFT].render(0, marker_top, marker_left, size.y);
		v_regions[REGION_TOP].render(marker_left, marker_top, marker_right, size.y);
		v_regions[REGION_TOP_RIGHT].render(marker_right, marker_top, size.x, size.y);
		v_regions[REGION_LEFT].render(0, marker_bottom, marker_left, marker_top);
		v_regions[REGION_MIDDLE].render(marker_left, marker_bottom, marker_right, marker_top);
		v_regions[REGION_RIGHT].render(marker_right, marker_bottom, size.x, marker_top);
		v_regions[REGION_BOTTOM_LEFT].render(0, 0, marker_left, marker_bottom);
		v_regions[REGION_BOTTOM].render(marker_left, 0, marker_right, marker_bottom);
		v_regions[REGION_BOTTOM_RIGHT].render(marker_right, 0, size.x, marker_bottom);
	}
}
