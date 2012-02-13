#ifndef O3ENGINE_RENDERLINE_OUTPUT_HPP_INCLUDED
#define O3ENGINE_RENDERLINE_OUTPUT_HPP_INCLUDED

#include "./../prereqs.hpp"
#include "./node.hpp"
#include "./state.hpp"

namespace o3engine {
namespace RenderLine {

	//! [R4] Class for defining a render line output destination
	/**
	 * This the abstract definition of the output of 3d render line.
	 * @par Class Characteristics
	 * 	RendereOutput is @ref noncopyable_page, @ref inherit_page and follows the @ref sfn_page
	 */
	class Output: public Node {
	private:
		// Uncopiable
		Output(const Output &);
		Output & operator=(const Output &);

	protected:

		//! Render line state
		State m_state;

	public:

		//! Default constructor (@b NOT activated)
		/**
		 * @remarks By default RenderOutput is not activated and you
		 * must enableRendering() to order engine to use this output.
		 */
		Output(int width, int height);

		//! Destructor
		virtual ~Output();

		//! @name Access attributes
		//! @{

		//! Get the current width of the output
		inline int getWidth() const {
			return m_state.width;
		}

		//! Get the current height of the output
		inline int getHeight() const {
			return m_state.height;
		}

		//! Get the current size
		inline const Vector2 getSize() {
			return Vector2(m_state.width, m_state.height);
		}
		//! @}

		//! Calculate and return the aspect ratio of this output
		inline GLfloat aspectRatio() const {
			return (GLfloat) ((double) m_state.width / (double) m_state.height);
		}

		//! No need to implement at output node
		virtual void onStateAltered();
	};
}
}

#endif
