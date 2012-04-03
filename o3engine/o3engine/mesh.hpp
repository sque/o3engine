#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "./prereqs.hpp"
#include "./submesh.hpp"
#include "./drawableobject.hpp"
#include "./face.hpp"
#include <vector>

namespace o3engine {
//! Handles a mesh and renders it.
/**
 * A mesh is a batch of triangles faces, with materials
 * and textures. This class is responsible for rendering
 * that kind of objects. Mesh can be designed by code
 * or can be loaded from mesh file.
 */
class Mesh: public DrawableObject {
protected:
	typedef std::vector<SubMesh>::iterator SubMeshIterator;
	std::vector<SubMesh> v_submeshes; //! Vector of submeshes
	Material * pmat_WireFrame; //! Wireframe material
	bool bHasTransperant; //! A flag if mesh has transperant parts

public:

	//! Default constructor creates an empty mesh
	inline Mesh(const string & name) :
			DrawableObject(name) {
		pmat_WireFrame = NULL;
	}

	//! Constructor that loads a mesh from file
	inline Mesh(const string & name, const string & model_file) :
			DrawableObject(name) {
		pmat_WireFrame = NULL;
		loadModel(model_file);
	}

	//! Destructor
	inline virtual ~Mesh() {

	}

	void recacheWireObject();

	void recacheObject();

	//! Translate object's parts
	inline void translate(const Vector3 & _trans) {
		std::vector<SubMesh>::iterator it;
		for (it = v_submeshes.begin(); it != v_submeshes.end(); it++) {
			(*it).translate(_trans);
		}
		recacheObject();
	}

	//! Load a model from file
	bool loadModel(const string & fname);

	//! Add a submesh inside mesh
	inline void addSubMesh(const SubMesh & _sm) {
		v_submeshes.push_back(_sm);
		recacheObject();
	}

	//! Count triangles in model
	unsigned long countTriangles() {
		unsigned long count = 0;
		std::vector<SubMesh>::iterator it;
		for (it = v_submeshes.begin(); it != v_submeshes.end(); it++) {
			count += (*it).countFaces();
		}
		return count;
	}

	//! Set wireframe mode
	/**
	 If this is setted true, the mesh will be rendered in wireframe mode.
	 @param _enabled true means that will be rendered in wireframe mode
	 @param mat_name The name of the material to be used while drawing wireframe. If mat_name is NULL
	 then it will use the material of each submesh.
	 */
	inline void setWireFrame(bool _enabled, const char * mat_name) {
		b_WireFrame = _enabled;
		if (mat_name)
			pmat_WireFrame = MaterialManager::getObjectPtr(mat_name);
		else
			pmat_WireFrame = NULL;

		if (b_WireFrame)
			recacheWireObject();
		else
			recacheObject();
	}

	//! Check if we are rendering wireframe
	inline bool isWireFrame() const {
		return b_WireFrame;
	}

	//! Get spherical size of object
	/**
	 It calculates the smallest sphere <i>with the same center
	 as mesh's pivot point</i> that can fit all parts of Mesh.
	 @return The <b>radius</b> of the sphere
	 */
	inline Real getSphericalSize() const {
		std::vector<SubMesh>::const_iterator it;
		Real spherical_size = 0;

		for (it = v_submeshes.begin(); it != v_submeshes.end(); it++) {
			if (spherical_size < (*it).calcSphericalSize())
				spherical_size = (*it).calcSphericalSize();
		}

		return spherical_size;
	}

	inline virtual bool hasTransperant() {
		return bHasTransperant;
	}
};
}

#endif // MESH_H_INCLUDED
