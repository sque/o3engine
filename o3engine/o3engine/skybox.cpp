/*#include "./skybox.hpp"
#include "./camera.hpp"
#include "./scenenode.hpp"

namespace o3engine {
	void Skybox::drawObject(Camera * _pCamera) {
		// Skip it if we don't have textures
		if (!bHasTextures)
			return;

		// Set appropriate states
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glColor3d(255, 255, 255);

		glPushMatrix();
		SceneNode * pNodeCame = _pCamera->getSceneNode();
		glTranslate(pNodeCame->getGlobalPosition());

		// Draw front face
		if (ptextures[FACE_FRONT]) {
			//ptextures[FACE_FRONT]->glBind2d();
			glBegin(GL_QUADS);
			glTexCoord2d(0, 1);
			glVertex3f(-(GLfloat) half_size, (GLfloat) half_size,
					-(GLfloat) half_size);
			glTexCoord2d(1, 1);
			glVertex3f((GLfloat) half_size, (GLfloat) half_size,
					-(GLfloat) half_size);
			glTexCoord2d(1, 0);
			glVertex3f((GLfloat) half_size, -(GLfloat) half_size,
					-(GLfloat) half_size);
			glTexCoord2d(0, 0);
			glVertex3f(-(GLfloat) half_size, -(GLfloat) half_size,
					-(GLfloat) half_size);
			glEnd();
		}

		// Draw back face
		if (ptextures[FACE_BACK]) {
			ptextures[FACE_BACK]->glBind2d();
			glBegin(GL_QUADS);
			glTexCoord2d(0, 1);
			glVertex3f((GLfloat) half_size, (GLfloat) half_size,
					(GLfloat) half_size);
			glTexCoord2d(1, 1);
			glVertex3f(-(GLfloat) half_size, (GLfloat) half_size,
					(GLfloat) half_size);
			glTexCoord2d(1, 0);
			glVertex3f(-(GLfloat) half_size, -(GLfloat) half_size,
					(GLfloat) half_size);
			glTexCoord2d(0, 0);
			glVertex3f((GLfloat) half_size, -(GLfloat) half_size,
					(GLfloat) half_size);
			glEnd();
		}

		// Draw left face
		if (ptextures[FACE_LEFT]) {
			ptextures[FACE_LEFT]->glBind2d();
			glBegin(GL_QUADS);
			glTexCoord2d(0, 1);
			glVertex3f(-(GLfloat) half_size, (GLfloat) half_size,
					(GLfloat) half_size);
			glTexCoord2d(1, 1);
			glVertex3f(-(GLfloat) half_size, (GLfloat) half_size,
					-(GLfloat) half_size);
			glTexCoord2d(1, 0);
			glVertex3f(-(GLfloat) half_size, -(GLfloat) half_size,
					-(GLfloat) half_size);
			glTexCoord2d(0, 0);
			glVertex3f(-(GLfloat) half_size, -(GLfloat) half_size,
					(GLfloat) half_size);
			glEnd();
		}

		// Draw right face
		if (ptextures[FACE_RIGHT]) {
			ptextures[FACE_RIGHT]->glBind2d();
			glBegin(GL_QUADS);
			glTexCoord2d(0, 1);
			glVertex3f((GLfloat) half_size, (GLfloat) half_size,
					-(GLfloat) half_size);
			glTexCoord2d(1, 1);
			glVertex3f((GLfloat) half_size, (GLfloat) half_size,
					(GLfloat) half_size);
			glTexCoord2d(1, 0);
			glVertex3f((GLfloat) half_size, -(GLfloat) half_size,
					(GLfloat) half_size);
			glTexCoord2d(0, 0);
			glVertex3f((GLfloat) half_size, -(GLfloat) half_size,
					-(GLfloat) half_size);
			glEnd();
		}

		// Draw top face
		if (ptextures[FACE_TOP]) {
			ptextures[FACE_TOP]->glBind2d();
			glBegin(GL_QUADS);
			glTexCoord2d(0, 0);
			glVertex3f(-(GLfloat) half_size, (GLfloat) half_size,
					(GLfloat) half_size);
			glTexCoord2d(1, 0);
			glVertex3f((GLfloat) half_size, (GLfloat) half_size,
					(GLfloat) half_size);
			glTexCoord2d(1, 1);
			glVertex3f((GLfloat) half_size, (GLfloat) half_size,
					-(GLfloat) half_size);
			glTexCoord2d(0, 1);
			glVertex3f(-(GLfloat) half_size, (GLfloat) half_size,
					-(GLfloat) half_size);
			glEnd();
		}

		// Draw bottom face
		if (ptextures[FACE_BOTTOM]) {
			ptextures[FACE_BOTTOM]->glBind2d();
			glBegin(GL_QUADS);
			glTexCoord2d(0, 0);
			glVertex3f(-(GLfloat) half_size, -(GLfloat) half_size,
					-(GLfloat) half_size);
			glTexCoord2d(1, 0);
			glVertex3f((GLfloat) half_size, -(GLfloat) half_size,
					-(GLfloat) half_size);
			glTexCoord2d(1, 1);
			glVertex3f((GLfloat) half_size, -(GLfloat) half_size,
					(GLfloat) half_size);
			glTexCoord2d(0, 1);
			glVertex3f(-(GLfloat) half_size, -(GLfloat) half_size,
					(GLfloat) half_size);
			glEnd();
		}
		// Stop states
		glPopMatrix();
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
	}
}
*/
