#include "./billboard.hpp"
#include "./o3engine.hpp"

namespace o3engine
{
	Billboard::Billboard()
	{
		mp_engine = O3Engine::getSingletonPtr();
		p_renderer = mp_engine->getRendererPtr();
	}

	// SPHERICAL - CHEAT
	void Billboard::beginBillboardSphericalCheat()
	{   GLfloat matrix[16];

		// Get modelview matrix
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

		// Load identity matrix on 3x3 submatrix
		matrix[0] = 1;
		matrix[1] = 0;
		matrix[2] = 0;

		matrix[4] = 0;
		matrix[5] = 1;
		matrix[6] = 0;

		matrix[8] = 0;
		matrix[9] = 0;
		matrix[10] = 1;

		// Save old matrix
		glPushMatrix();

		// Load our mangled matrix
		glLoadMatrixf(matrix);
	}

	// CYLINDRICAL - CHEAT
	void Billboard::beginBillboardCylindricalCheat(E_FIXED_AXIS fixed_axis)
	{   GLfloat matrix[16];

		// Get modelview matrix
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

		switch(fixed_axis)
		{
		case AXIS_UP:
			// Load identity matrix on 3x3 submatrix
			matrix[4] = 0;
			matrix[5] = 1;
			matrix[6] = 0;

			matrix[8] = 0;
			matrix[9] = 0;
			matrix[10] = 1;
			break;
		case AXIS_RIGHT:
			// Load identity matrix on 3x3 submatrix
			matrix[0] = 1;
			matrix[1] = 0;
			matrix[2] = 0;

			matrix[8] = 0;
			matrix[9] = 0;
			matrix[10] = 1;
			break;
		case AXIS_LOOKAT:
			// Load identity matrix on 3x3 submatrix
			matrix[0] = 1;
			matrix[1] = 0;
			matrix[2] = 0;

			matrix[4] = 0;
			matrix[5] = 1;
			matrix[6] = 0;
			break;
		}

		// Save old matrix
		glPushMatrix();

		// Load our mangled matrix
		glLoadMatrixf(matrix);
	}

	//! True cylindrical billboard on Y
	void Billboard::beginBillboardCylindricalOnY()
	{   GLfloat matrix[16];

		// Get modelview matrix
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

		// Get Object to Camera
		Vector3 vObjToCam(getObjectToCamera(matrix));

		// Make the projection on ZX
		Vector3 vObjToCamOnZX(vObjToCam.x , 0, vObjToCam.z);
		vObjToCamOnZX.normalize();

		// Calculate needed rotation of object
		Real cosine = vObjToCamOnZX.dotProduct(Vector3::UNIT_Z);
		Real degs = math::radianToDegree(math::arcCos(cosine));
		Vector3 UpVec = -vObjToCamOnZX.crossProduct(Vector3::UNIT_Z);

		// Rotate the object appropriatly
		glPushMatrix();
		glRotatef((GLfloat)degs, (GLfloat)UpVec[0], (GLfloat)UpVec[1], (GLfloat)UpVec[2]);
	}
}
