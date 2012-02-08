#ifndef O3ENGINE_FRAMELISTENER_HPP_INCLUDED
#define O3ENGINE_FRAMELISTENER_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./timesensitive.hpp"

namespace o3engine
{
    //! [R4] Abstract definition of a frame interval listener
	/**
	 @remarks Frame listener is not activated by default.
     @par Class Characteristics
         FrameListener is @ref copyable_page, @ref inherit_page and follows the @ref sfn_page
     */
	class FrameListener : private TimeSensitive
	{
    friend class O3Engine;
    private:

        //! Raise the frame interval event
        inline void raiseRenderInterval(void)
		{   onRenderInterval(timePassed());    }

	protected:
        //! Raised between each rendered frame
		/**
		@param secs The time passed since this function was last called.
		 */
		virtual void onRenderInterval(Real secs) = 0;

	public:
		//! Virtual destructor Destructor
		virtual ~FrameListener();

		//! @name Control this frame listener's status
        //! @{

		//! Activate this listener
		/**
		@return
		    - @b true If the listener activated succesfully
            - @b false If the listener was already activated
		    .
        */
		bool enableFrameListening();

		//! Stop listening for events
		/**
		@return
		    - @b true If the listener was previously monitoring
            - @b false If the listener was not monitoring at all.
		    .
        */
		bool disableFrameListening();

		//! Check if listener is activated
		bool isFrameListeningEnabled();
        //! @}

	};
}
#endif
