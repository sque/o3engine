#ifndef O3ENGINE_WINDOW_HPP_INCLUDED
#define O3ENGINE_WINDOW_HPP_INCLUDED

#include "../prereqs.hpp"
#include "./surface.hpp"
#include "./inputprocessor.hpp"

namespace o3engine {

	//! [R4] Abstraction layer to platform windows
	/**
	 * This class is an abstract way to speak with window.
	 * It provides the same API across all platforms but its back-end
	 * may be implemented differently among systems.
	 * @par Class Characteristics
	 * Platform is @ref noncopyable_page, @ref noninherit_page and follows the @ref sfn_page
	 */
	class Window :public Surface{
		friend class InputProcessor;
		friend class Plaform;
	public:

		//! Construct a new window
		Window(int width, int height, int x = 0, int y = 0);

		// Destructor
		~Window();

		//! Get height of window
		int getHeight() const;

		//! Get width of window
		int getWidth() const;

		//! Set window size
		void resize(int width, int height);

		//! Get window position
		void getPosition(int & x, int & y) const;

		//! Get current window title
		const string getTitle() const;

		//! Set window title
		void setTitle(const string & title);

		//! Set background color
		void setBackColor(const Color & col);

		//! Get background color
		const Color & getBackColor() const;

		//! Get input processor for this window
		InputProcessor & getInputProcessor();

	private:
		Window(const Window &);
		Window & operator=(const Window &);

		// Pimpl idiom
		class impl;
		impl * pimpl;
	};
}


#endif /* O3ENGINE_WINDOW_HPP_INCLUDED */
