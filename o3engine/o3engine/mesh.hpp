#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "./prereqs.hpp"
#include "./submesh.hpp"
#include "./drawableobject.hpp"
#include "./face.hpp"
#include <vector>
#include <memory>

namespace o3engine {

	//! General mesh holder
	class Mesh: public DrawableObject {
	public:

		//! Type to hold submeshes
		typedef std::vector<SubMesh> submesh_container_type;

		//! Default constructor creates an empty mesh
		Mesh(const string & name) :
			DrawableObject(name) {
		}

		//! Destructor
		virtual ~Mesh() {
		}

		//! Translate object's parts
		void translate(const Vector3 & trans);

		//! Imprort a mesh from file and upload to gpu
		bool importFromFile(const string & fname);

		//! Get submeshes
		submesh_container_type & submeshes() {
			return m_submeshes;
		}

		//! Get submeshes
		const submesh_container_type & submeshes() const {
			return m_submeshes;
		}

		//! Total vertices in model
		size_t totalVertices() const {
			size_t total = 0;
			for(auto & sm :m_submeshes) {
				total += sm.totalVertices();
			}
			return total;
		}

		//! Total number of elemensts (triangles/lines/...)
		size_t totalElements() const {
			size_t total = 0;
			for(auto & sm :m_submeshes) {
				total += sm.totalElements();
			}
			return total;
		}

		//! Total submeshes
		size_t totalSubmeshes() const {
			return m_submeshes.size();
		}

		//! Render the solid part of object
		virtual void drawSolidPart(){
			for(auto & r : m_submeshes_renderers) {
				r->draw();
			}
		}

		//! Render the transperant part of object
		virtual void drawTransperantPart() {}

		//! Check if it is transperant object
		virtual bool hasTransperant() { return true; }

		//! Upload this mesh to gpu (so it is rendable)
		void uploadToGPU();
	protected:

		//! Container of submeshes
		submesh_container_type m_submeshes;

		std::vector<std::shared_ptr<SubMeshRenderer> > m_submeshes_renderers;
	};

	//! Calculate boundary sphere
	/**
	 * @param radius [out] The minimum radius of a sphere that can hold this mesh
	 */
	void boundary_sphere(const Mesh & m, Real & radius);

	//! Calculate boundary box
	void boundary_box(const Mesh & m, Real & x_min, Real & x_max, Real & y_min, Real & y_max, Real & z_min, Real & z_max);

	//! Get an info string about a mesh
	std::string info (const Mesh & m);
}

#endif // MESH_H_INCLUDED
