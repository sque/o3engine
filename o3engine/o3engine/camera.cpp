#include "./camera.hpp"
#include "./renderoutput.hpp"
#include "./scenenode.hpp"

namespace o3engine {
	// Initialize Values
	void Camera::_initvalues(void) {
		target_point = Vector3::UNIT_Z;
		up_vector = Vector3::UNIT_Y;
		lim_near = 1;
		lim_far = 20;
		aspect = 1;
		fovY = 60;
		pSkybox = NULL;
		pAttachedNode = NULL;
	}

	Camera::~Camera() {
		if (pAttachedNode)
			pAttachedNode->dettachCamera();
	}

	// Calculate Frustum values from perspective angle
	void Camera::calcFromPrespective() {
		Real fov2;
		fov2 = ((fovY * math::PI) / 180.0) / 2.0;
		top = lim_near / (math::cos(fov2) / math::sin(fov2));
		bottom = -top;
		right = top * aspect;
		left = -right;
		width = right - left;
		height = top - bottom;
	}

	void Camera::drawCamera() {
		// Setup camera lens
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		useme_to_glFrustum();

		// Reset ModelView matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Setup camera
		useme_to_gluLookAt();

		if (pAttachedNode)
			pAttachedNode->useme_to_glInvertPosition();
	}
}
