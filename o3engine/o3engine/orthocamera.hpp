#ifndef O3ENGINE_ORTHOCAMERA_HPP_INCLUDED
#define O3ENGINE_ORTHOCAMERA_HPP_INCLUDED

#include "prereqs.hpp"
#include "./camera.hpp"

namespace o3engine {

	//! Orthographic projection camera
	class OrthoCamera : public Camera {
	protected:

		//! Frustum left boundaries
		Real m_left;

		//! Frustum right boundaries
		Real m_right;

		//! Frustum bottom boundaries
		Real m_bottom;

		//! Frustum top boundaries
		Real m_top;

		//! Frustum near clip plane
		Real m_znear;

		//! Frustum far clip plane
		Real m_zfar;

		//! Calculate projection matrix
		void calcProjMatrix();

	public:

		//! Create a center orthographic
		OrthoCamera(Real width, Real height, Real znear, Real zfar) :
			Camera(),
			m_left(-width/2),
			m_right(width/2),
			m_bottom(-height/2),
			m_top(height/2),
			m_znear(znear),
			m_zfar(zfar){
			calcProjMatrix();
		}

		//! Create a center orthographic
		OrthoCamera(Real left, Real right, Real bottom, Real top, Real znear, Real zfar) :
			Camera(),
			m_left(left/2),
			m_right(right/2),
			m_bottom(bottom/2),
			m_top(top/2),
			m_znear(znear),
			m_zfar(zfar){
			calcProjMatrix();
		}

		//! Get left boundary
		Real getLeft() const {
			return m_left;
		}

		//! Set left boundary
		Real setLeft(Real left) {
			m_left = left;
			calcProjMatrix();
			return m_left;
		}

		//! Get right boundaries
		Real getRight() const {
			return m_right;
		}

		//! Set right boundaries
		Real setRight(Real right) {
			m_right = right;
			calcProjMatrix();
			return m_right;
		}

		//! Get bottom boundary
		Real getBottom() const {
			return m_bottom;
		}

		//! Set bottom boundary
		Real setBottom(Real bottom) {
			m_bottom = bottom;
			calcProjMatrix();
			return m_bottom;
		}

		//! Get top boundary
		Real getTop() const {
			return m_top;
		}

		//! Set top boundary
		Real setTop(Real top) {
			m_top = top;
			calcProjMatrix();
			return m_top;
		}

		//! Get near clipping distance
		Real getNear() const {
			return m_znear;
		}

		//! Get near clipping distance
		Real setNear(Real near) {
			m_znear = near;
			calcProjMatrix();
			return m_znear;
		}

		//! Get far clipping distance
		Real getFar() const {
			return m_zfar;
		}

		//! Set far clipping distance
		Real setFar(Real far) {
			m_zfar = far;
			calcProjMatrix();
			return m_zfar;
		}

		//! Get width of frustum
		Real getWidth() const {
			return m_right - m_left;
		}

		//! Get height of frustum
		Real getHeight() const {
			return m_top - m_bottom;
		}

		virtual void onStateAltered(){}
	};

}


#endif
