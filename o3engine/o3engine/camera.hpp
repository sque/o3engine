#ifndef O3ENGINE_CAMERA_HPP_INCLUDED
#define O3ENGINE_CAMERA_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./skybox.hpp"
#include "./renderline/node.hpp"

namespace o3engine {
	//! Camera handler
	/**
	 * To create a new camera, create an object from this class,
	 * and attach it on node.
	 */
	class Camera:
		public RenderLine::Node{
		friend class SceneNode;
	protected:
		//! Pointer to attached scene node;
		SceneNode * mp_scene_node;

		//! Camera's target vector
		Vector3 m_target_point;

		//! Camera's up vector
		Vector3 m_up_vector;

		//! Camera parameter
		Real left, top, bottom, right, width, height, lim_near, lim_far;

		//! Aspect ratio of camera
		Real m_aspect_ratio;

		//! The theta of the perspective
		Real fovY;

		// Initialize Values
		void _initvalues(void);

		//! Calculate Frustum values from perspective angle
		void calcFromPrespective();
	public:

		//! Default constructor
		Camera() {
			_initvalues();
			calcFromPrespective();
		}

		//! Constructor with basic parameters
		Camera(const Vector3 & target_point, const Vector3 & up_vector){
			_initvalues();
			m_target_point = target_point;
			m_up_vector = up_vector;
			calcFromPrespective();
		}

		//! Constructor with extended parameters
		Camera(const Vector3 & target_point, const Vector3 & up_vector, Real fovy,
				Real _near, Real _far) {
			_initvalues();
			m_target_point = target_point;
			m_up_vector = up_vector;
			lim_near = _near;
			lim_far = _far;
			fovY = fovy;
			calcFromPrespective();
		}

		virtual ~Camera();

		//! Get camera's target point
		inline const Vector3 & getTargetPoint() const {
			return m_target_point;
		}

		//! Set camera's target point
		inline Vector3 & setTargetPoint(const Vector3 & target_point) {
			return m_target_point = target_point;
		}

		//! Get camera's up vector
		inline const Vector3 & getUpVector() {
			return m_up_vector;
		}

		//! Set camera's up vector
		inline Vector3 & setUpVector(const Vector3 & up_vector) {
			return m_up_vector = up_vector;
		}

		//! Get camera's near cut-off distance
		/**
		 * Anything existing below this distance, will not be
		 * displayed by the camera. Not even processed to be rendered.
		 * @see setNear getFar setFar
		 */
		inline Real getNear() const {
			return lim_near;
		}

		//! Set camera's near cut-off distance
		/**
		 * Anything existing below this distance, will not be
		 * displayed by the camera. Not even processed to be rendered.
		 * @see getNear getFar setFar
		 * */
		inline void setNear(Real _near) {
			lim_near = _near;
			calcFromPrespective();
		}

		//! Get camera's far cut-off distance
		/**
		 * Anything existing above this distance, will not be
		 * displayed by the camera. Not even processed to be rendered.
		 * @see getNear setNear setFar
		 */
		inline Real getFar() const {
			return lim_far;
		}

		//! Set camera's far cut-off distance
		/**
		 * Anything existing above this distance, will not be
		 * displayed by the camera. Not even processed to be rendered.
		 * @see getNear setNear getFar
		 * */
		inline void setFar(Real _far) {
			lim_far = _far;
			calcFromPrespective();
		}

		//! Get the camera's viewing angle (FOV)
		inline Real getFovY() const {
			return fovY;
		}

		//! Set the Camera's viewing angle (FOV)
		inline void setFovY(Real _y) {
			fovY = _y;
			calcFromPrespective();
		}

		//! Get camera's aspect ration
		inline Real getAspectRatio() const {
			return m_aspect_ratio;
		}

		//! Set camera's aspect ratio
		inline void setAspectRatio(Real aspect_ratio) {
			m_aspect_ratio = aspect_ratio;
			calcFromPrespective();
		}

		// Run gluLookAt with those parameters
		inline virtual void useme_to_gluLookAt() {
			::gluLookAt(0, 0, 0, m_target_point.x, m_target_point.y, m_target_point.z,
					m_up_vector.x, m_up_vector.y, m_up_vector.z);
		}

		// Run glFrustum with a specific aspect ratio
		inline virtual void useme_to_glFrustum() {
			::glFrustum(left, right, bottom, top, lim_near, lim_far);
		}

		inline SceneNode * getSceneNode() {
			return mp_scene_node;
		}

		void render();

		void onStateAltered();
	};
}

#endif
