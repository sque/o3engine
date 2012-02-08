#include "./submesh.hpp"

namespace o3engine
{
	// Use this function to render submesh
	void SubMesh::useme_to_glRender(bool b_WireFrame, bool b_WireFrameOwnMaterial)
	{   std::vector<Face>::iterator it;

	   if (b_WireFrame)
		{

			if ((b_WireFrameOwnMaterial) && (pMat)) pMat->useme_to_glPreDraw();   // Material

			for(it = v_faces.begin();it != v_faces.end();it++)
			{
				glBegin(GL_LINE_LOOP);
				(*it).myglVertex();
				glEnd();
			}

			if ((b_WireFrameOwnMaterial) && (pMat)) pMat->useme_to_glPostDraw();
		}
		else
		{
			if (pMat) pMat->useme_to_glPreDraw();   // Material

			// Textured submesh
			if (bTextCords)
			{
				glBegin(GL_TRIANGLES);
					for(it = v_faces.begin();it != v_faces.end();it++)
						(*it).glVertex_with_normal_n_textcoords();
				glEnd();
			}
			else
			{
				glBegin(GL_TRIANGLES);
					for(it = v_faces.begin();it != v_faces.end();it++)
						(*it).glVertex_with_normal();
				glEnd();
			}
			if (pMat) pMat->useme_to_glPostDraw();
		}
	}
}
