#ifndef O3ENGINE_SURFACE_HPP_INCLUDED
#define O3ENGINE_SURFACE_HPP_INCLUDED

#include "../prereqs.hpp"
#include "./surfacelistener.hpp"
#include <vector>

namespace o3engine {

	//! [R4] Abstraction layer to platform surfaces
	/**
	 * @par Class Characteristics
	 * Platform is @ref noncopyable_page, @ref noninherit_page and follows the @ref sfn_page
	 */
	class Surface {
		friend class Plaform;

	private:
		Surface(const Surface &);
		Surface & operator=(const Surface &);

	protected:
		typedef std::vector<SurfaceListener *> surface_listeners_type;
		surface_listeners_type m_sfc_listeners;

	public:

		//! Construct a new surface
		Surface();

		// Destructor
		virtual ~Surface();

		//! Get height of surface
		virtual int getHeight() const = 0;

		//! Get width of surface
		virtual int getWidth() const = 0;

		//! Calculate aspect ratio
		float getAspectRatio() const;

		//! Set new surface size
		virtual void resize(int width, int height) = 0;

		//! Set background color
		virtual void setBackColor(const Color & col) = 0;

		//! Get background color
		virtual const Color & getBackColor() const = 0;

		//! Attach a surface listener
		void attachSurfaceListener(SurfaceListener & listener);

		//! Detach a surface listener
		bool detachSurfaceListener(SurfaceListener & listener);

	};
}


#endif
