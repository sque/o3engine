#ifndef O3ENGINE_RENDEROUTPUTTEXTURE_HPP_INCLUDED
#define O3ENGINE_RENDEROUTPUTTEXTURE_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./texture.hpp"
#include "./renderoutput.hpp"
#include "./platform/offscreen.hpp"

namespace o3engine {
	//! [R4] An output to a texture (RTT)
	/**
	 * Implementation of RenderOutput target on a texture. This is
	 * also known as RenderToTexture (RTT).
	 * @par Class Characteristics
	 * RenderOutputTexture is @ref noncopyable_page, @ref inherit_page and follows the @ref sfn_page
	 */
	class TextureRenderOutput: protected Texture,
			public RenderOutput,
			public SurfaceListener {
	private:
		// Non-copyable
		TextureRenderOutput(const TextureRenderOutput &);
		TextureRenderOutput& operator=(const TextureRenderOutput &);

	protected:

		//! OpenGL name of our's fbo
		GLuint m_gli_fbo;

		//! Use fbo to create RTT
		bool m_use_fbo;

		//! Binded offscreen surface
		OffScreen & m_offscreen;

	public:
		//! Default constructor
		TextureRenderOutput(OffScreen & offscreen, bool use_fbo = true);

		//! Desturctor
		virtual ~TextureRenderOutput();

		//! @name Events from RenderOutput
		//! @{
		virtual void render();
		virtual void onSurfaceResized(int old_width, int old_height, int new_width, int new_height){

		}

		virtual void onOutputResize(int new_w, int new_h){}

		//! Raised when window must be drawn
		virtual void onSurfaceRepaint(){
			render();
		}
		//! @}

	};
}
#endif
