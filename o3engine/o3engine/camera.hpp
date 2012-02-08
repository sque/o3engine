#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "./prereqs.hpp"
#include "./skybox.hpp"

namespace o3engine
{
	//! Camera handler
	/**
        This is how camera is represented by the system.
        To create a new camera, create an object from this class,
        and attach it on node.
	 */
	class Camera
	{
	friend class SceneNode;
	private:
		Skybox * pSkybox;       	//!< Pointer to skybox of this camera
		SceneNode * pAttachedNode;	//!< Pointer to attached node;

		// Camera position
		Vector3	target_point;   //!< Camera's target vector
		Vector3	up_vector;      //!< Camera's up vector

		// Camera parameter
		Real left, top, bottom, right, width, height, lim_near, lim_far;
		Real aspect;                          //! Aspect ratio of camera
		Real fovY;                            //! The theta of the prespective

		// Initialize Values
		void _initvalues(void);

		//! Calculate Frustum values from prespective angle
		void calcFromPrespective();
	public:

		//! Default constructor
		Camera()
		{   _initvalues();
			calcFromPrespective();
		}

		//! Constructor with basic parameters
		Camera(const Vector3 & _target,const Vector3 & _up_vector)
		{   _initvalues();
			target_point = _target;
			up_vector = _up_vector;
			calcFromPrespective();
		}

		//! Constructor with extended parameters
		Camera(const Vector3 & _target, const Vector3 & _up_vector, Real fovy, Real _near, Real _far)
		{   _initvalues();
			target_point = _target;
			up_vector = _up_vector;
			lim_near = _near;
			lim_far = _far;
			fovY = fovy;
			calcFromPrespective();
		}

		virtual ~Camera();

		//! Get camera's target point
		inline const Vector3 & getTargetPoint() const
		{	return target_point;	}

		//! Set camera's target point
		inline Vector3 & setTargetPoint(const Vector3 & _target)
		{   return target_point = _target;   }

		//! Get camera's up vector
		inline const Vector3 & getUpVector()
		{	return up_vector;		}

		//! Set camera's up vector
		inline Vector3 & setUpVector(const Vector3 & _up)
		{	return up_vector = _up;		}

		//! Get camera's near cut-off distance
		/**
			Anything existing below this distance, will not be
			displayed by the camera. Not even processed to be rendered.
		@see setNear getFar setFar
		*/
		inline Real getNear() const
		{   return lim_near;            }

		//! Set camera's near cut-off distance
		/**
			Anything existing below this distance, will not be
			displayed by the camera. Not even processed to be rendered.
		@see getNear getFar setFar
		*/
		inline void setNear(Real _near)
		{   lim_near = _near; calcFromPrespective();    }

		//! Get camera's far cut-off distance
		/**
			Anything existing above this distance, will not be
			displayed by the camera. Not even processed to be rendered.
		@see getNear setNear setFar
		*/
		inline Real getFar() const
		{   return lim_far;              }

		//! Set camera's far cut-off distance
		/**
			Anything existing above this distance, will not be
			displayed by the camera. Not even processed to be rendered.
		@see getNear setNear getFar
		*/
		inline void setFar(Real _far) {   lim_far = _far;  calcFromPrespective();   }

		//! Get the camera's viewing angle (FOV)
		inline Real getFovY() const {   return fovY;   }

		//! Set the Camera's viewing angle (FOV)
		inline void setFovY(Real _y) {   fovY = _y;	 calcFromPrespective();   }

		//! Get camera's aspect ration
		inline Real getAspectRatio() const
		{	return aspect;	}

		//! Set camera's aspect ratio
		inline void setAspectRatio(Real _aspect)
		{	aspect = _aspect;	calcFromPrespective();	}

		// Run gluLookAt with those paramters
		inline void useme_to_gluLookAt()
		{   gluLookAt(0, 0, 0,
				target_point.x, target_point.y, target_point.z,
				up_vector.x, up_vector.y, up_vector.z
			);
		}

		// Run glFrustum with a specific aspect ratio
		inline void useme_to_glFrustum()
		{   glFrustum(left, right, bottom ,top, lim_near, lim_far);    }

		//! Attach a skybox
		inline void attachSkybox(Skybox * _pSkybox)
		{   pSkybox = _pSkybox; }

		//! Dettach skybox
		inline void dettachSkybox()
		{   pSkybox = NULL; }

		//! Get skybox
		inline Skybox * getSkyboxPtr()
		{   return pSkybox; }

		//! Draw skybox
		inline void drawSkybox()
		{   if (pSkybox) pSkybox->drawObject(this); }

		inline SceneNode * getAttachedNode()
		{	return pAttachedNode;	}

		void drawCamera();
	};
}

#endif // CAMERA_H_INCLUDED
