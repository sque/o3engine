#ifndef O3ENGINE_RENDERLINK_HPP_INCLUDED
#define O3ENGINE_RENDERLINK_HPP_INCLUDED

namespace o3engine {

	class RenderLink {
	protected:
		//! Pointer to next link
		RenderLink * p_next;
	public:

		RenderLink() :
			p_next(NULL) {
		}

		virtual ~RenderLink(){
		}

		//! Populate with actual render code
		virtual void render() = 0;

		//! Render from this link and after
		inline void renderNext() {
			if (p_next)
				p_next->render();
		}

	};
};

#endif
