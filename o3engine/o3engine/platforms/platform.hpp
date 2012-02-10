#ifndef O3ENGINE_PLATFORM_HPP_INCLUDED
#define O3ENGINE_PLATFORM_HPP_INCLUDED

#include "../prereqs.hpp"
#include "./timer.hpp"
#include "./input_processor.hpp"
#include "./window.hpp"

namespace o3engine {

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

		//! @name Manage windows
		//! @{

		//! Create a new window
		/**
		 * @param name This is a unique identifier name for the window.
		 * @param width The width of window
		 * @param height The height of window
		 */
		Window & createWindow(const string & name, int width, int height);

		//! Get a window based on its name
		Window & getWindow(const string & name);

		//! Destroy a window based on its name
		bool destroyWindow(const string &name);

		//! @}

		//! Called by engine to initialize platform
		bool init();
	};
}

#endif
