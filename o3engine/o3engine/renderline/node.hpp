#ifndef O3ENGINE_RENDERLINE_NODE_HPP_INCLUDED
#define O3ENGINE_RENDERLINE_NODE_HPP_INCLUDED

#include "./state.hpp"

namespace o3engine {
namespace RenderLine {
	class Node {
	protected:
		//! Pointer to next node
		Node * mp_next;

		//! Pointer to render line state
		const State * mp_state;

		//! Render from this link and after
		inline void renderNext() {
			if (mp_next)
				mp_next->render();
		}
	public:

		Node() :
			mp_next(NULL), mp_state(NULL) {
		}

		inline virtual ~Node() {
		}

		//! Attach another node to this line
		inline void attachNode(Node * pnode) {
			mp_next = pnode;
			propagateState(mp_state);
		}

		//! Detach the next render node
		inline void detachNode() {
			mp_next = NULL;
		}

		//! Get the current attached render node
		Node * getAttachedNode() {
			return mp_next;
		}

		//! Propagate new state object
		inline void propagateState(const State * pstate) {
			mp_state = pstate;
			onStateAltered();
			if (mp_next)
				mp_next->propagateState(pstate);
		}

		//! Propagate state elements altered
		inline void propagateStateAltered() {
			onStateAltered();
			if (mp_next)
				mp_next->propagateStateAltered();
		}

		//! @name Events to be implemented by derived classes
		//! @{

		//! Populate with actual render code
		/**
		 * Don't forget to call renderNext otherwise rendering
		 * will stop on this node.
		 */
		virtual void render() = 0;

		//! When state has changed in some way
		virtual void onStateAltered() = 0;

		//! @}
	};
}
}
;

#endif
