#include "./guiwindow.hpp"

namespace o3engine
{
	GuiWindow::GuiWindow(GuiWindow * parent, const string & classname)
		:Overlay(parent, Vector2(0,0), Vector2(10, 10), COORD_TYPE_ABSOLUTE),
		WndClass(classname)
	{
		// Inherit engine
		mp_gui_engine = parent->mp_gui_engine;
	}

	// Constructor for GuiRoot
	GuiWindow::GuiWindow(Overlay * parent, const Vector2 & pos, const Vector2 & size, const string & classname)
		:Overlay(parent, pos, size, COORD_TYPE_ABSOLUTE),
		WndClass(classname)
	{
	}

	GuiWindow::~GuiWindow()
	{
	}


	void GuiWindow::onPaint()
	{
		/*glColor4f(1,1,1,0.4);
		glBegin(GL_QUADS);
			glVertex3f(0,0,0);
			glVertex3f(0,v3_size.getY(),0);
			glVertex3f(v3_size.getX(),v3_size.getY(),0);
			glVertex3f(v3_size.getX(),0,0);
		glEnd();

		printf("draw %s %s\n", WndClass.c_str(), v3_size.toString().c_str());
		*/
		mp_gui_engine->drawWnd(this);
	}
}
