#ifndef GUIWINDOWCLASS_H_INCLUDED
#define GUIWINDOWCLASS_H_INCLUDED

#include "../prereqs.hpp"
#include "../overlay.hpp"
#include "./guiengine.hpp"

namespace o3engine
{
    /**
    @ingroup gui_group
    */
	class GuiWindow : public Overlay
	{
	protected:
		GuiEngine * mp_gui_engine;
		string WndClass;		// Class of this window

		inline virtual void onDrawOverlay()
		{	onPaint();    }

		// Function called to paint the gui element
		virtual void onPaint();

	public:
		// Default Constructor
		GuiWindow(GuiWindow * parent, const string & classname);

		// Constructor for GuiRoot
		GuiWindow(Overlay * parent, const Vector2 & pos, const Vector2 & size, const string & classname);

		// Destructor
		virtual ~GuiWindow();

		// Get parent window
		inline GuiWindow * getParent() const
		{	return (GuiWindow *)mp_parent;	}

		// Get class name
		inline const string & getClassName() const
		{	return WndClass;	}
	};
}
#endif // GUIWINDOWCLASS_H_INCLUDED
