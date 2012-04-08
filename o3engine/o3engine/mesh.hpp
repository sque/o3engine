#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "./prereqs.hpp"
#include "./geometry.hpp"
#include "./drawableobject.hpp"
#include <vector>
#include <memory>

namespace o3engine {

	//! General mesh holder
	class Mesh: public DrawableObject {
	public:

		//! Type to hold geometries
		typedef std::vector<Geometry> geometry_container_type;

		//! Default constructor creates an empty mesh
		Mesh(const string & name) :
			DrawableObject(name) {
		}

		//! Destructor
		virtual ~Mesh() {
		}

		//! Translate object's parts
		void translate(const Vector3 & trans);

		//! Import a mesh from file and upload to GPU
		bool importFromFile(const string & fname);

		//! Get sub geometries
		geometry_container_type & geometries() {
			return m_geometries;
		}

		//! Get sub geometries
		const geometry_container_type & geometries() const {
			return m_geometries;
		}

		//! Total vertices in model
		size_t totalVertices() const {
			size_t total = 0;
			for(auto & sm :m_geometries) {
				total += sm.totalVertices();
			}
			return total;
		}

		//! Total number of elemensts (triangles/lines/...)
		size_t totalElements() const {
			size_t total = 0;
			for(auto & sm :m_geometries) {
				total += sm.totalElements();
			}
			return total;
		}

		//! Total independent geometries
		size_t totalGeometries() const {
			return m_geometries.size();
		}

		//! Render the solid part of object
		virtual void draw(SceneRendererVisitor * pvisitor){
			for(auto & r : m_geometries_renderers) {
				r->draw(pvisitor);
			}
		}

		//! Upload this mesh to GPU (so it is rendable)
		void uploadToGPU();

	protected:

		//! Container of submeshes
		geometry_container_type m_geometries;

		typedef std::vector<std::shared_ptr<GeometryRenderer>> geometry_renderer_container_type;

		//! Container of geometry renderers
		geometry_renderer_container_type m_geometries_renderers;
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
