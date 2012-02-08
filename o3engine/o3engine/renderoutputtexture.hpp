#ifndef O3ENGINE_RENDEROUTPUTTEXTURE_HPP_INCLUDED
#define O3ENGINE_RENDEROUTPUTTEXTURE_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./texture.hpp"
#include "./renderoutput.hpp"

namespace o3engine
{
    //! [R4] An output to a texture (RTT)
	/**
	    Implemetation of RenderOutput target on a texture. This is
	    also known as RenderToTexture (RTT).
	@par Class Characteristics
         RenderOutputTexture is @ref noncopyable_page, @ref inherit_page and follows the @ref sfn_page
    */
	class RenderOutputTexture : protected Texture, public RenderOutput
	{
    private:
        // Non-copyable
        RenderOutputTexture(const RenderOutputTexture &);
        RenderOutputTexture& operator=(const RenderOutputTexture &);

	protected:
		GLuint m_gli_fbo;		//!< OpenGL name of our's fbo
		bool m_use_fbo; 		//!< Use fbo to create RTT

	public:
		//! Default constructor
		/**
        @name name The name of the texture object
        */
		RenderOutputTexture(const string & name, int width, int height, bool use_fbo = true);

		//! Desturctor
		virtual ~RenderOutputTexture();

		//! @name Events from RenderOutput
		//! @{
		virtual void onPreRender();
		virtual void onPostRender();
		virtual void onWindowResize(int new_width, int new_height){}
		//! @}

	};
}
#endif
