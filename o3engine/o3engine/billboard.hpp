#ifndef BILLBOARD_H_INCLUDED
#define BILLBOARD_H_INCLUDED

#include "./prereqs.hpp"

namespace o3engine
{
	//! A class for setting an object as billboard
	/**
		The class provides usefull routines that will
		transform the MODEL_VIEW matrix in a way
		to perform a billboard effect. To use it call
		method <b>beginBillboard*</b> and after
		the drawing of billboarded object call <b>endBillboard</b>
	*/
	class Billboard
	{
	protected:
		//! Pointer to engine
		O3Engine * mp_engine;
		Node * p_camnode;

		//! Constructor
		Billboard();

		//! Billboard fixed axis
		enum E_FIXED_AXIS
		{
			AXIS_UP,        //!< The up vector is fixed at its original position
			AXIS_RIGHT,     //!< The right vector is fixed at its original position
			AXIS_LOOKAT     //!< The lookat vector
		};

		//! Calculate vector Camera to Object
		inline Vector3 getCameraToObject(GLfloat *model_view)
		{
			// Direction of Cam to Obj
			return Vector3(model_view[12], model_view[13], model_view[14]);
		}

		//! Calculate vector Object to Camera
		inline Vector3 getObjectToCamera(GLfloat *model_view)
		{
			// Current transformation matrix
			Matrix3 A(model_view[0], model_view[4], model_view[8],
				model_view[1], model_view[5], model_view[9],
				model_view[2], model_view[6], model_view[10]);

			// Transpose matrix of A
			Matrix3 transA(A.transpose());
			Vector3 lc_pos(-model_view[12], -model_view[13], -model_view[14]);
			return transA * lc_pos;
		}

		//! Cylindrical billboard with fixed Y-axis(True - Slower)
		/**
			It will create an illusion of true cylindrical billboarding
			on axis Y.
		@remarks Call this before you start drawing your object
		*/
		void beginBillboardCylindricalOnY();

		//! Spherical billboard (Cheat method - Faster)
		/**
			It will create an illusion of almost spherical billboarding
		@remarks Call this before you start drawing your object
		*/
		void beginBillboardSphericalCheat();

		//! Cylindrical billboard (Cheat method - Faster)
		/**
			It will create an illusion of almost cylindrical billboarding,
			you can select the fixed axis, that will not be billboard
		@remarks Call this before you start drawing your object
		@param fixed_axis There are two options here, Up vector or Right vector
		*/
		void beginBillboardCylindricalCheat(E_FIXED_AXIS fixed_axis);

		//! Call this when you are finished with drawing your billboard object
		inline void endBillboard()
		{   glPopMatrix();    }
	};
}
#endif // BILLBOARD_H_INCLUDED
