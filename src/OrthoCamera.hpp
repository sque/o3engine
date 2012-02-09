/*
 * OrthoCamera.hpp
 *
 *  Created on: Feb 8, 2012
 *      Author: sque
 */

#ifndef ORTHOCAMERA_HPP_
#define ORTHOCAMERA_HPP_

#include <o3engine/camera.hpp>

using namespace o3engine;

class OrthoCamera : public Camera{
protected:
	float ortho_width;
	float ortho_height;
public:
	OrthoCamera(const Vector3 & _target,const Vector3 & _up_vector, float width, float height) :
		Camera(_target, _up_vector),
		ortho_width(width), ortho_height(height){
	}

	inline virtual void useme_to_glFrustum()
	{
		//glOrtho(left, right, bottom ,top, lim_near, lim_far);
		glOrtho(-ortho_width/2, ortho_width/2, -ortho_height/2, ortho_height/2, lim_near, lim_far);
	}
};


#endif /* ORTHOCAMERA_HPP_ */
