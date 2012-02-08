#include "./mesh.hpp"
#include "./tinyxml/tinyxml.h"

namespace o3engine
{
	// load from file
	bool Mesh::loadModel(const string & fname)
	{
		// XML element pointers
		TiXmlElement * pxmlelem_mesh;
		TiXmlElement * pxmlelem_submeshes;
		TiXmlElement * pxmlelem_submesh;
		TiXmlElement * pxmlelem_geometry;
		TiXmlElement * pxmlelem_vertexbuffer;
		TiXmlElement * pxmlelem_faces;
		TiXmlElement * pxmlelem_face;
		TiXmlElement * pxmlelem_vertex;
		TiXmlElement * pxmlelem_position;
		TiXmlElement * pxmlelem_normal;
		TiXmlElement * pxmlelem_texcoord;
		const char * pTmpText;
		std::vector<Vector3> points, normals;
		std::vector<Vector2> textcoords;
		Vector3 tmpVertex;
		Vector2 tmpUVcord;
		Face tmpFace;
		SubMesh tmpSubMesh;
		bool bTexturized;   // If submesh is texturized

		// Start reading mesh
		printf(">> LOAD mesh: \"%s\"\n", fname.c_str());

		// Open file
		TiXmlDocument MeshXML(fname.c_str());
		if (!MeshXML.LoadFile())
		{
			printf("  >> ERROR: Cannot read xml file \"%s\"!\n", fname.c_str());
			return false;
		}

		// Load "mesh" and "submeshes" elements
		if (!(((pxmlelem_mesh = MeshXML.FirstChildElement("mesh"))) &&
			((pxmlelem_submeshes = pxmlelem_mesh->FirstChildElement("submeshes")))))
		{
			printf("  >> ERROR: Cannot find mesh's data in xml file \"%s\"!\n", fname.c_str());
			return false;
		}

		// Loop arround all submeshes
		for (pxmlelem_submesh = pxmlelem_submeshes->FirstChildElement("submesh"); pxmlelem_submesh; pxmlelem_submesh = pxmlelem_submesh->NextSiblingElement("submesh"))
		{
			// Clean up temporary data
			points.clear();
			normals.clear();
			textcoords.clear();
			tmpSubMesh.Reset();
			bTexturized = false;

			// Check attributes of mesh
			if ((pTmpText = pxmlelem_submesh->Attribute("material")))
			{
					printf("  >> Submesh needs material \"%s\":\n", pTmpText);
					tmpSubMesh.setMaterial(pTmpText);
			}

			// Load geometry
			if (NULL == (pxmlelem_geometry = pxmlelem_submesh->FirstChildElement("geometry")))
				return false;
			if (NULL == (pxmlelem_vertexbuffer = pxmlelem_geometry->FirstChildElement("vertexbuffer")))
				return false;

			// Check if we have texture coordinates
			int textAttribute_Value = 0;
			if ((TIXML_SUCCESS == pxmlelem_vertexbuffer->QueryIntAttribute("texture_coords", &textAttribute_Value))
				&& (textAttribute_Value == 1))
			{
				bTexturized = true;
			}

			// Get vertices
			for (pxmlelem_vertex = pxmlelem_vertexbuffer->FirstChildElement("vertex"); pxmlelem_vertex;
				pxmlelem_vertex = pxmlelem_vertex->NextSiblingElement("vertex"))
			{	double x, y, z, u, v;

				// POSITION OF VERTEX
				pxmlelem_position = pxmlelem_vertex->FirstChildElement("position");
				pxmlelem_position->QueryDoubleAttribute("x", &x);
				pxmlelem_position->QueryDoubleAttribute("y", &y);
				pxmlelem_position->QueryDoubleAttribute("z", &z);
				tmpVertex = Vector3(x,y,z);
				points.push_back(tmpVertex);		// Save it

				// LIGHT NORMAL VECTOR
				pxmlelem_normal = pxmlelem_vertex->FirstChildElement("normal");
				pxmlelem_normal->QueryDoubleAttribute("x", &x);
				pxmlelem_normal->QueryDoubleAttribute("y", &y);
				pxmlelem_normal->QueryDoubleAttribute("z", &z);
				tmpVertex = Vector3(x,y,z);
				normals.push_back(tmpVertex);		// Save it

				if (!bTexturized)
					continue;

				// TEXTURE CORDS
				pxmlelem_texcoord = pxmlelem_vertex->FirstChildElement("texcoord");
				pxmlelem_texcoord->QueryDoubleAttribute("u", &u);
				pxmlelem_texcoord->QueryDoubleAttribute("v", &v);
				tmpUVcord = Vector2(u, 1 - v);
				textcoords.push_back(tmpUVcord);	// Save it
			}

			// Get faces
			pxmlelem_faces = pxmlelem_submesh->FirstChildElement("faces");
			for (pxmlelem_face = pxmlelem_faces->FirstChildElement("face"); pxmlelem_face;
				pxmlelem_face = pxmlelem_face->NextSiblingElement("face"))
			{	int v1, v2, v3;

				// Loop attributes
				pxmlelem_face->QueryIntAttribute("v1", &v1);
				pxmlelem_face->QueryIntAttribute("v2", &v2);
				pxmlelem_face->QueryIntAttribute("v3", &v3);
				tmpFace = Face(points[v1], points[v2], points[v3], normals[v1], normals[v2], normals[v3]);
				if (bTexturized)
				{
					tmpFace.setTextCoord1(textcoords[v1]);
					tmpFace.setTextCoord2(textcoords[v2]);
					tmpFace.setTextCoord3(textcoords[v3]);
				}
				tmpSubMesh.addFace(tmpFace);    // add faces to submesh
			}

			// Enable texture coords on submesh if needed
			if (bTexturized)
				tmpSubMesh.enableTexturecords();

			// Add submesh
			v_submeshes.push_back(tmpSubMesh);
		}
		printf("  >> Finished: %lu triangles!\n", countTriangles());

		// regenerate list
		recacheObject();

		return true;
	}


	void Mesh::recacheWireObject()
	{   std::vector<SubMesh>::iterator it;

		// Calculate transperancy
		if (pmat_WireFrame)
			bHasTransperant = !pmat_WireFrame->getDepthWrite();
		else
			bHasTransperant = false;

		// Render
		if (bHasTransperant)
		{
			glNewList(gli_calllistSolid, GL_COMPILE);
			glEnd();
			glNewList(gli_calllistTrans, GL_COMPILE);
		}
		else
		{
			glNewList(gli_calllistSolid, GL_COMPILE);
			glEnd();
			glNewList(gli_calllistTrans, GL_COMPILE);
		}


			// Apply material if one
			if (pmat_WireFrame)
				pmat_WireFrame->useme_to_glPreDraw();

			// Render submeshes
			for(it = v_submeshes.begin();it != v_submeshes.end();it++)
			{   (*it).useme_to_glRender(true, (pmat_WireFrame == NULL)?true:false);        }

			// De-apply material
			if (pmat_WireFrame)
				pmat_WireFrame->useme_to_glPostDraw();

		glEndList();
	}

	void Mesh::recacheObject()
	{   std::vector<SubMesh>::iterator it;
		SubMesh * pMesh;
		bHasTransperant = false;

		// Render solid parts
		glNewList(gli_calllistSolid, GL_COMPILE);

			// Render submeshes
			for(it = v_submeshes.begin();it != v_submeshes.end();it++)
			{   pMesh = &(*it);
				if (pMesh->isTransperant())
					bHasTransperant = true;
				else
					pMesh->useme_to_glRender(false, true);
			}

		glEndList();

		// Render transperant
		glNewList(gli_calllistTrans, GL_COMPILE);

			for(it = v_submeshes.begin();it != v_submeshes.end();it++)
			{   pMesh = &(*it);
				if (pMesh->isTransperant())
					pMesh->useme_to_glRender(false, true);
			}
		glEndList();
	}
}
