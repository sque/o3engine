#include "./mesh.hpp"
#include "./tinyxml/tinyxml.h"
#include <assimp.hpp>
#include <aiScene.h>
#include <aiPostProcess.h>
#include <iostream>
#include <sstream>

namespace o3engine
{
	void Mesh::translate(const Vector3 & trans) {
		for (auto & submesh : m_submeshes) {
			submesh.translate(trans);
		}
	}

	//! Calculate boundary sphere
	/**
	 * @param radius [out] The minimum radius of a sphere that can hold this mesh
	 */
	void boundary_sphere(const Mesh & m, Real & radius) {
		radius = 0;
		for(auto & sm: m.submeshes()) {
			Real sm_radius;
			boundary_sphere(sm, sm_radius);
			if (radius > sm_radius)
				radius = sm_radius;
		}
	}

	//! Calculate boundary box
	void boundary_box(const Mesh & m, Real & x_min, Real & x_max, Real & y_min, Real & y_max, Real & z_min, Real & z_max) {
		x_min = y_min = z_min = std::numeric_limits<Real>::max();
		x_max = y_max = z_max = std::numeric_limits<Real>::min();

		for(auto & sm : m.submeshes()) {
			for(auto vertex : sm.vertices()) {
				if (vertex.position.x < x_min)
					x_min = vertex.position.x;
				if (vertex.position.y < y_min)
					y_min = vertex.position.y;
				if (vertex.position.z < z_min)
					z_min = vertex.position.z;

				if (vertex.position.x > x_max)
					x_max = vertex.position.x;
				if (vertex.position.y > y_max)
					y_max = vertex.position.y;
				if (vertex.position.z > z_max)
					z_max = vertex.position.z;
			}
		}
	}

	//! Upload file to GPU
	void Mesh::uploadToGPU() {
		m_submeshes_renderers.clear();

		for(auto & sm: m_submeshes) {
			std::shared_ptr<SubMeshRenderer> mesh_renderer(new SubMeshRenderer(sm));
			mesh_renderer->uploadToGPU();
			m_submeshes_renderers.push_back(mesh_renderer);
		}
		ogl::gl_error_checkpoint("Uploaded to gpu");
	}

	//! Import a mesh from file
	bool Mesh::importFromFile(const string & fname) {

		// Create an instance of the Importer class
		Assimp::Importer importer;

		// And have it read the given file with some example postprocessing
		// Usually - if speed is not the most important aspect for you - you'll
		// propably to request more postprocessing than we do in this example.
		const aiScene* scene = importer.ReadFile(fname,
			aiProcess_CalcTangentSpace       |
			aiProcess_Triangulate            |
			aiProcess_JoinIdenticalVertices  |
			aiProcess_SortByPType);

		// If the import failed, report it
		if( !scene)	{
			std::cerr << importer.GetErrorString();
			throw std::invalid_argument("cannot open this file!");
		}

		if (scene->mNumMeshes == 0) {
			std::cerr << "This file has no meshes inside" << std::endl;
		}

		for(size_t mesh_index = 0; mesh_index < scene->mNumMeshes; mesh_index++ ) {
			aiMesh * pMesh = scene->mMeshes[mesh_index];
			// Prepare submesh
			SubMesh::attributesflags_type aflags = {VertexAttributes::position};
			if (pMesh->HasNormals())
				aflags = aflags | SubMesh::attributesflags_type({VertexAttributes::normal});
			if (pMesh->HasTextureCoords(0))
				aflags = aflags | SubMesh::attributesflags_type({VertexAttributes::tex_coords_0});
			if (pMesh->HasTextureCoords(1))
				aflags = aflags | SubMesh::attributesflags_type({VertexAttributes::tex_coords_1});
			if (pMesh->HasTextureCoords(2))
				aflags = aflags | SubMesh::attributesflags_type({VertexAttributes::tex_coords_2});
			if (pMesh->HasTextureCoords(3))
				aflags = aflags | SubMesh::attributesflags_type({VertexAttributes::tex_coords_3});
			if (pMesh->HasTextureCoords(4))
				aflags = aflags | SubMesh::attributesflags_type({VertexAttributes::tex_coords_4});
			if (pMesh->HasTextureCoords(5))
				aflags = aflags | SubMesh::attributesflags_type({VertexAttributes::tex_coords_5});
			if (pMesh->HasTangentsAndBitangents())
				aflags = aflags | SubMesh::attributesflags_type({VertexAttributes::tangent_bitangent});
			SubMesh sm(aflags);
			sm.vertices().resize(pMesh->mNumVertices);

			// Load positions
			for(size_t i = 0; i < pMesh->mNumVertices; i++ ) {
				sm.vertices()[i].position = *reinterpret_cast<Vector3*>(pMesh->mVertices + i);
			}

			// Load normals
			if (sm.attributes().has_flag(VertexAttributes::normal)) {
				for(size_t i = 0; i < pMesh->mNumVertices; i++ ) {
					sm.vertices()[i].normal = *reinterpret_cast<Vector3*>(pMesh->mNormals + i);
				}
			}

			// Load texcoords (0)
			if (sm.attributes().has_flag(VertexAttributes::tex_coords_0)) {
				for(size_t i = 0; i < pMesh->mNumVertices; i++ ) {
					sm.vertices()[i].tex_coords[0] = *reinterpret_cast<Vector3*>(pMesh->mTextureCoords[0] + i);
				}
			}

			// Load tangents bitangents
			if (sm.attributes().has_flag(VertexAttributes::tangent_bitangent)) {
				for(size_t i = 0; i < pMesh->mNumVertices; i++ ) {
					sm.vertices()[i].tangent = *reinterpret_cast<Vector3*>(pMesh->mTangents + i);
					sm.vertices()[i].bitangent = *reinterpret_cast<Vector3*>(pMesh->mBitangents + i);
				}
			}

			// Load faces indices (triangles)
			sm.indices().resize(pMesh->mNumFaces * 3);
			for(size_t i =0;i < pMesh->mNumFaces;i++) {
				sm.indices()[i * 3] = pMesh->mFaces[i].mIndices[0];
				sm.indices()[i * 3 + 1] = pMesh->mFaces[i].mIndices[1];
				sm.indices()[i * 3 + 2] = pMesh->mFaces[i].mIndices[2];
			}

			m_submeshes.push_back(sm);
		}

		uploadToGPU();
		return true;
	}

	//! Get an info string about a mesh
	std::string info(const Mesh & m) {
		std::ostringstream ss;
		ss << "Mesh(" << m.getName() << "){ Submeshes: " << m.totalSubmeshes() <<
				", Vertices: " << m.totalVertices() << ", Elements: " <<  m.totalElements() <<" }" << std::endl;
		for(auto & sm : m.submeshes()) {
			ss << "  " << info(sm) << std::endl;
		}
		return ss.str();
	}
}
