#ifndef O3ENGINE_PERSPECTIVECAMERA_HPP_INCLUDED
#define O3ENGINE_PERSPECTIVECAMERA_HPP_INCLUDED

#include "./camera.hpp"

namespace o3engine {

	//! Perspective camera handler
	/**
	 * To create a new camera, create an object from this class,
	 * and attach it on node.
	 */
	class PerspectiveCamera:
		public Camera{
	protected:

		//! The theta of the perspective
		Angle m_fovy;

		//! Aspect ratio of camera
		Real m_aspect_ratio;

		//! Frustum near clipping
		Real m_znear;

		//! Frustum far clipping
		Real m_zfar;

		//! Calculate projection matrix for perspective view
		void calcProjMatrix();
	public:

		//! Default constructor
		PerspectiveCamera() :
			m_fovy(Degree(60)),
			m_aspect_ratio(1),
			m_znear(1),
			m_zfar(20){
			calcProjMatrix();
		}

		//! Constructor with extended parameters
		PerspectiveCamera(Angle fovy, Real aspect, Real znear, Real zfar) :
			m_fovy(fovy),
			m_aspect_ratio(aspect),
			m_znear(znear),
			m_zfar(zfar){
			calcProjMatrix();
		}

		virtual ~PerspectiveCamera(){}

		//! Get camera's near cut-off distance
		/**
		 * Anything existing below this distance, will not be
		 * displayed by the camera. Not even processed to be rendered.
		 * @see setNear getFar setFar
		 */
		inline Real getNear() const {
			return m_znear;
		}

		//! Set camera's near cut-off distance
		/**
		 * Anything existing below this distance, will not be
		 * displayed by the camera. Not even processed to be rendered.
		 * @see getNear getFar setFar
		 * */
		inline void setNear(Real znear) {
			m_znear = znear;
			calcProjMatrix();
		}

		//! Get camera's far cut-off distance
		/**
		 * Anything existing above this distance, will not be
		 * displayed by the camera. Not even processed to be rendered.
		 * @see getNear setNear setFar
		 */
		inline Real getFar() const {
			return m_zfar;
		}

		//! Set camera's far cut-off distance
		/**
		 * Anything existing above this distance, will not be
		 * displayed by the camera. Not even processed to be rendered.
		 * @see getNear setNear getFar
		 * */
		inline void setFar(Real zfar) {
			m_zfar = zfar;
			calcProjMatrix();
		}

		//! Get the camera's viewing angle (FOV)
		inline const Angle & getFovY() const {
			return m_fovy;
		}

		//! Set the Camera's viewing angle (FOV)
		inline void setFovY(Angle fovy) {
			m_fovy = fovy;
			calcProjMatrix();
		}

		//! Get camera's aspect ration
		inline Real getAspectRatio() const {
			return m_aspect_ratio;
		}

		//! Set camera's aspect ratio
		inline void setAspectRatio(Real aspect_ratio) {
			m_aspect_ratio = aspect_ratio;
			calcProjMatrix();
		}

		//! Auto change aspect ration
		virtual void onStateAltered();
	};
}

#endif
