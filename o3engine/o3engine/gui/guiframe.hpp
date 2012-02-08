#ifndef GUIFRAME_H_INCLUDED
#define GUIFRAME_H_INCLUDED

#include "../prereqs.hpp"
#include "./guiwindow.hpp"

namespace o3engine
{
    /**
    @ingroup gui_group
    */
	class GuiFrame : public GuiWindow
	{
	protected:
		bool bHasResizeMark;
		bool bHasXMark;
		string sTitle;

	public:
		GuiFrame(GuiWindow * _parent, const Vector2 & pos = Vector2::ZERO, const Vector2 & size = Vector2::ZERO)
			:GuiWindow(_parent, "builtin_frame"),
			sTitle("Unnamed")
		{
			setSize(size);
			setPosition(pos);
		}

		bool hasXMark() const
		{	return bHasXMark;	}

		bool hasResizeMark() const
		{	return bHasResizeMark;	}

		void setXMark(bool enabled)
		{	bHasXMark = enabled;	}

		void setResizeMark(bool enabled)
		{	bHasResizeMark = enabled;	}

		void setTitle(const string & _t)
		{	sTitle = _t;	}

		const string & getTitle() const
		{	return sTitle;	}
	};
}
#endif // GUIFRAME_H_INCLUDED
