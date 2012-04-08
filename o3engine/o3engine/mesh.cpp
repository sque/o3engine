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
		for (auto & submesh : m_geometries) {
			submesh.translate(trans);
		}
	}

	void boundary_sphere(const Mesh & m, Real & radius) {
		radius = 0;
		for(auto & gm: m.geometries()) {
			Real gm_radius;
			boundary_sphere(gm, gm_radius);
			if (radius > gm_radius)
				radius = gm_radius;
		}
	}

	//! Calculate boundary box
	void boundary_box(const Mesh & m, Real & x_min, Real & x_max, Real & y_min, Real & y_max, Real & z_min, Real & z_max) {
		x_min = y_min = z_min = std::numeric_limits<Real>::max();
		x_max = y_max = z_max = std::numeric_limits<Real>::min();

		for(auto & gm : m.geometries()) {
			for(auto vertex : gm.vertices()) {
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
		m_geometries_renderers.clear();

		for(auto & gm: m_geometries) {
			geometry_renderer_container_type::value_type geo_renderer(new GeometryRenderer(gm));
			geo_renderer->uploadToGPU();
			m_geometries_renderers.push_back(geo_renderer);
		}
		ogl::gl_error_checkpoint("Error uploading Mesh geometry to GPU");
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
			Geometry::attributesflags_type aflags = {VertexAttributes::position};
			if (pMesh->HasNormals())
				aflags = aflags | Geometry::attributesflags_type({VertexAttributes::normal});
			if (pMesh->HasTextureCoords(0))
				aflags = aflags | Geometry::attributesflags_type({VertexAttributes::tex_coords_0});
			if (pMesh->HasTextureCoords(1))
				aflags = aflags | Geometry::attributesflags_type({VertexAttributes::tex_coords_1});
			if (pMesh->HasTextureCoords(2))
				aflags = aflags | Geometry::attributesflags_type({VertexAttributes::tex_coords_2});
			if (pMesh->HasTextureCoords(3))
				aflags = aflags | Geometry::attributesflags_type({VertexAttributes::tex_coords_3});
			if (pMesh->HasTextureCoords(4))
				aflags = aflags | Geometry::attributesflags_type({VertexAttributes::tex_coords_4});
			if (pMesh->HasTextureCoords(5))
				aflags = aflags | Geometry::attributesflags_type({VertexAttributes::tex_coords_5});
			if (pMesh->HasTangentsAndBitangents())
				aflags = aflags | Geometry::attributesflags_type({VertexAttributes::tangent_bitangent});
			Geometry gm(aflags);
			gm.vertices().resize(pMesh->mNumVertices);

			// Load positions
			for(size_t i = 0; i < pMesh->mNumVertices; i++ ) {
				gm.vertices()[i].position = Vector3(pMesh->mVertices[i].x, pMesh->mVertices[i].y, pMesh->mVertices[i].z);
			}

			// Load normals
			if (gm.attributes().has_flag(VertexAttributes::normal)) {
				for(size_t i = 0; i < pMesh->mNumVertices; i++ ) {
					gm.vertices()[i].normal = Vector3(pMesh->mNormals[i].x, pMesh->mNormals[i].y, pMesh->mNormals[i].z);
				}
			}

			// Load texcoords (0)
			if (gm.attributes().has_flag(VertexAttributes::tex_coords_0)) {
				for(size_t i = 0; i < pMesh->mNumVertices; i++ ) {
					gm.vertices()[i].tex_coords[0] = Vector3(pMesh->mTextureCoords[0][i].x, pMesh->mTextureCoords[0][i].y, pMesh->mTextureCoords[0][i].z);
				}
			}

			// Load tangents bitangents
			if (gm.attributes().has_flag(VertexAttributes::tangent_bitangent)) {
				for(size_t i = 0; i < pMesh->mNumVertices; i++ ) {
					gm.vertices()[i].tangent =  Vector3(pMesh->mTangents[i].x, pMesh->mTangents[i].y, pMesh->mTangents[i].z);
					gm.vertices()[i].bitangent = Vector3(pMesh->mBitangents[i].x, pMesh->mBitangents[i].y, pMesh->mBitangents[i].z);
				}
			}

			// Load faces indices (triangles)
			gm.indices().resize(pMesh->mNumFaces * 3);
			for(size_t i =0;i < pMesh->mNumFaces;i++) {
				gm.indices()[i * 3] = pMesh->mFaces[i].mIndices[0];
				gm.indices()[i * 3 + 1] = pMesh->mFaces[i].mIndices[1];
				gm.indices()[i * 3 + 2] = pMesh->mFaces[i].mIndices[2];
			}

			m_geometries.push_back(gm);
		}

		uploadToGPU();
		return true;
	}

	//! Get an info string about a mesh
	std::string info(const Mesh & m) {
		std::ostringstream ss;
		ss << "Mesh(" << m.getName() << "){ Geometries: " << m.totalGeometries() <<
				", Vertices: " << m.totalVertices() << ", Elements: " <<  m.totalElements() <<" }" << std::endl;
		for(auto & gm : m.geometries()) {
			ss << "  " << info(gm) << std::endl;
		}
		return ss.str();
	}
}
