#ifndef O3ENGINE_PLATFORM_HPP_INCLUDED
#define O3ENGINE_PLATFORM_HPP_INCLUDED

#include "../prereqs.hpp"
#include "./timer.hpp"
#include "./input_processor.hpp"

namespace o3engine {

	//! [R4] Base class for object that need to get informed about windows events
	/**
	 * @remarks Currently only one window listener is supported and this is reserved
	 * for internal reasons, so this function is useless at the moment for the user
	 * of the library.
	 * @par Class Characteristics
	 * WindowEventsListener is @ref copyable_page, @ref inherit_page and follows the @ref sfn_page
	 */
	class WindowEventsListener {
	public:
		//! Default virtual destructor
		virtual ~WindowEventsListener() {
		}

		//! @name Events that can be implemented by derived classes
		//! @{

		//! Raised when the current window gets resized
		/**
		 * @param old_width The previous width of window before reshaping.
		 * @param old_height The previous height of window before reshaping.
		 * @param new_width The new width of window after reshaping.
		 * @param new_height The new height of window after reshaping.
		 */
		virtual void onWindowResized(int old_width, int old_height, int new_width,
				int new_height) = 0;

		//! Raised when window must be drawn
		virtual void onWindowRepaint() = 0;

		//! Raised when there is idle time between paintings
		virtual void onWindowIdle() = 0;

		//! @}
	};

	//! [R4] Abstraction layer to underlying platform
	/**
	 * This class is an abstract way to speak with runtime platform.
	 * It provides the same API across all platforms but its back-end
	 * may be implemented differently among systems.
	 * @par Class Characteristics
	 * Platform is @ref noncopyable_page, @ref noninherit_page and follows the @ref sfn_page
	 */
	class Platform: public Singleton<Platform> {
	private:
		//! Pointer to timer object
		Timer * mp_timer;

		//! Pointer to input processor
		InputProcessor * mp_inputproc;

		// Pimpl idiom
		class impl;
		impl * pimpl;

		// Noncopyable
		Platform(const Platform &);
		Platform & operator=(const Platform &);

	public:
		//! General constructor
		Platform();

		//! Destructor
		~Platform();

		//! @name Access Platform Attributes
		//! @{
		inline const Timer * getTimerPtr() const {
			return mp_timer;
		}

		inline const Timer & getTimer() const {
			return *mp_timer;
		}

		inline InputProcessor * getInputProcessorPtr() {
			return mp_inputproc;
		}

		inline InputProcessor & getInputProcessor() {
			return *mp_inputproc;
		}
		//! @}

		//! @name Access window attributes
		//! @{

		//! Set the background color of window
		void setWindowBackColor(const Color & back_color);

		//! Get the window back color
		const Color & getWindowBackColor(const Color & color) const;

		//! Get the current window title
		const string & getWindowTitle() const;

		//! Set the current window title
		void setWindowTitle(const string & name);

		//! Get window height
		int getWindowHeight() const;

		//! Get window width
		int getWindowWidth() const;

		//! Set window size
		void setWindowSize(int width, int height);

		//! Set/Unset windows events listener
		void setWindowEventsListener(WindowEventsListener * p_listener);

		//! Get the current windows events listener
		WindowEventsListener * getWindowEventsListener();
		//! @}

		//! Called by engine to initialize platform
		bool init();
	};
}

#endif
