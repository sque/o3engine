#ifndef O3ENGINE_LOOPIDLELISTENER_HPP_INCLUDED
#define O3ENGINE_LOOPIDLELISTENER_HPP_INCLUDED

namespace o3engine {

	/**
	 * Base class to listen for loop idles
	 */
	class LoopIdleListener {
	public:
		virtual ~LoopIdleListener() {
		}

		//! Called between frames after all rendering has been finished
		virtual void onLoopIdle() = 0;
	};
}

#endif /* LOOPIDLE_HPP_ */
