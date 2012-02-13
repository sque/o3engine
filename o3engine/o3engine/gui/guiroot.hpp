#ifndef GUIROOT_H_INCLUDED
#define GUIROOT_H_INCLUDED

#include "../prereqs.hpp"
#include "./guiwindow.hpp"

namespace o3engine {
	/**
	 * @defgroup gui_group Gui System
	 */

	/**
	 * @ingroup gui_group
	 */
	class GuiRoot: public GuiWindow {
	protected:
		virtual void onPaint() {
		}

	public:
		GuiRoot(Overlay * p_parent, const Vector2 & pos, const Vector2 & size,
				GuiEngine * p_engine);

	};
}
#endif // GUIROOT_H_INCLUDED
