#ifndef GUIBUTTON_H_INCLUDED
#define GUIBUTTON_H_INCLUDED

#include "../prereqs.hpp"
#include "./guiwindow.hpp"

namespace o3engine
{
    /**
    @ingroup gui_group
    */
	class GuiButton : public GuiWindow
	{
	public:
		// Constructor
		inline GuiButton(GuiWindow * _parent, const Vector2 & pos = Vector2::ZERO, const Vector2 & size = Vector2::ZERO)
			:GuiWindow(_parent, "builtin_button")
		{
			setSize(size);
			setPosition(pos);
		}
	};
}
#endif
