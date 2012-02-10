#ifndef O3ENGINE_WINDOW_HPP_INCLUDED
#define O3ENGINE_WINDOW_HPP_INCLUDED

#include "../prereqs.hpp"
#include "./window_listener.hpp"

namespace o3engine {

	//! [R4] Abstraction layer to platform windows
	/**
	 * This class is an abstract way to speak with window.
	 * It provides the same API across all platforms but its back-end
	 * may be implemented differently among systems.
	 * @par Class Characteristics
	 * Platform is @ref noncopyable_page, @ref noninherit_page and follows the @ref sfn_page
	 */
	class Window {
	private:
		Window(const Window &) = delete;
		Window & operator=(const Window &);

		// Pimpl idiom
		class impl;
		impl * pimpl;
	public:

		//! Construct a new window
		Window(const string & name, int width, int height, int x = 0, int y = 0);

		// Destructor
		~Window();

		//! Get height of window
		int getHeight() const;

		//! Get width of window
		int getWidth() const;

		//! Calculate aspect ratio
		float getAspectRatio() const;

		//! Set window size
		void setSize(int width, int height);

		//! Set window position
		void setPosition(int x, int y);

		//! Get current window title
		const string getTitle() const;

		//! Set window title
		void setTitle(const string & title);

		//! Set background color
		void setBackColor(const Color & col);

		//! Get background color
		const Color & getBackColor() const;

		//! Set/Unset windows events listener
		void setWindowEventsListener(WindowEventsListener * p_listener);

		//! Get the current windows events listener
		WindowEventsListener * getWindowEventsListener();
	};

}

#endif /* O3ENGINE_WINDOW_HPP_INCLUDED */
