#ifndef SUBMESH_H_INCLUDED
#define SUBMESH_H_INCLUDED

#include "./prereqs.hpp"
#include "./face.hpp"
#include <vector>
#include "./materialmanager.hpp"

namespace o3engine
{
	class SubMesh
	{
	protected:
		typedef std::vector<Face>::iterator FaceIterator;
		std::vector<Face> v_faces;      // Faces
		Material * pMat;
		bool bTextCords;                // If it has texture cords

	public:
		// Constructor
		SubMesh(){ pMat = NULL; bTextCords = false; }

		// Copy constructor
		inline SubMesh(const SubMesh & r){ v_faces = r.v_faces; pMat = r.pMat; bTextCords = r.bTextCords; }

		// Copy operator
		inline SubMesh & operator=(const SubMesh & r) { v_faces = r.v_faces; pMat = r.pMat; bTextCords = r.bTextCords; return *this;}

		// Add face to submesh
		inline void addFace(const Face & _f)
		{   v_faces.push_back(_f);  }

		// Set material
		inline Material * setMaterial(const string & mat)
		{   return pMat = MaterialManager::getObjectPtr(mat); }

		// Get current material
		inline const Material * getMaterialPtr() const { return pMat; }

		// Enable texturing
		inline void enableTexturecords() { bTextCords = true; }

		// Use this function to render submesh
		void useme_to_glRender(bool b_WireFrame, bool b_WireFrameOwnMaterial = true);

		// Translate all points
		inline void translate(const Vector3 & _trans)
		{   std::vector<Face>::iterator it;
			for(it = v_faces.begin();it != v_faces.end();it++)
				(*it).translate(_trans);
		}

		inline unsigned long countFaces()
		{   return (unsigned long)v_faces.size();  }

		// Reset submesh
		inline void Reset() {  v_faces.clear(); pMat = NULL; bTextCords = false; }

		// Calculate Spherical size
		Real calcSphericalSize() const
		{   Real size = 0;
			std::vector<Face>::const_iterator it;
			for(it = v_faces.begin();it != v_faces.end();it++)
				if ((*it).calcSphericalSize() > size)
					size = (*it).calcSphericalSize();

			return size;
		}

		// Check if it is transperant
		bool isTransperant()
		{
			if (pMat)
				return !pMat->getDepthWrite();
			else
				return false;
		}
	};
}

#endif // SUBMESH_H_INCLUDED
