#ifndef GUIENGINE_H_INCLUDED
#define GUIENGINE_H_INCLUDED

#include "../prereqs.hpp"

namespace o3engine
{
    /**
    @ingroup gui_group
    */
	class GuiEngine
	{

	public:
		enum E_GUI_REGION_STATE
		{
			REGION_NORMAL,
			REGION_HOVER,
			REGION_PRESSED,
			REGION_DISABLED,
			REGION_OFF
		};

		// Constructor
		GuiEngine(){}

		// Destructor
		virtual ~GuiEngine(){}

		virtual void drawWnd(GuiWindow * p_wnd) = 0;
	};
}

#endif // GUIENGINE_H_INCLUDED
