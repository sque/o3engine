#ifndef O3ENGINE_RENDERLINE_TEXTUREOUTPUT_HPP_INCLUDED
#define O3ENGINE_RENDERLINE_TEXTUREOUTPUT_HPP_INCLUDED

#include "./../prereqs.hpp"
#include "./../texture.hpp"
#include "./output.hpp"
#include "./../platform/offscreen.hpp"

namespace o3engine {
namespace RenderLine {
	//! [R4] Render lile  output to texture (RTT)
	/**
	 * @par Class Characteristics
	 * RenderOutputTexture is @ref noncopyable_page, @ref inherit_page and follows the @ref sfn_page
	 */
	class TextureOutput: protected Texture,
			public RenderLine::Output,
			public SurfaceListener {
	private:
		// Non-copyable
		TextureOutput(const TextureOutput &);
		TextureOutput& operator=(const TextureOutput &);

	protected:

		//! OpenGL name of our's fbo
		GLuint m_gli_fbo;

		//! Use fbo to create RTT
		bool m_use_fbo;

		//! Binded offscreen surface
		OffScreen & m_offscreen;

	public:
		//! Default constructor
		TextureOutput(OffScreen & offscreen, bool use_fbo = true);

		//! Destructor
		virtual ~TextureOutput();

		virtual void render();

		//! @name Events from Surface listener
		//! @{

		//! Raised when surface changed size
		virtual void onSurfaceResized(int old_width, int old_height, int new_width,
				int new_height);

		//! Raised when window must be drawn
		virtual void onSurfaceRepaint() {
			render();
		}

		//! @}

	};
}
}
#endif
