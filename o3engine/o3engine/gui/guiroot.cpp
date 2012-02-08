#include "./guiroot.hpp"

namespace o3engine
{
	GuiRoot::GuiRoot(Overlay * p_parent, const Vector2 & pos, const Vector2 & size, GuiEngine * p_engine)
		:GuiWindow(p_parent, pos, size, "builtin_root")
	{
		// Save engine
		mp_gui_engine = p_engine;
	}
}
