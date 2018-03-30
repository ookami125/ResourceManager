#pragma once
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stdint.h>
#include "Skeleton.h"

class Model {
	struct Vertex {
		float x, y, z;
	};
	Vertex* Vertices = nullptr;
	size_t VertCount = 0;
	uint32_t* Indices = nullptr;
	size_t IndexCount = 0;
	Skeleton* Skeletons = nullptr;
	size_t SkeletonCount = 0;
public:
	Model(const char* filename);
	~Model();
};

Model::Model(const char* filename)
{
	auto model = aiImportFile(filename, aiProcessPreset_TargetRealtime_MaxQuality);

	//Count total number of verts;
	for (unsigned i = 0; i < model->mNumMeshes; ++i)
	{
		auto mesh = model->mMeshes[i];
		VertCount += mesh->mNumVertices;
		SkeletonCount += mesh->HasBones();
		for (unsigned face_idx = 0; face_idx < mesh->mNumFaces; ++face_idx)
		{
			auto face = mesh->mFaces[face_idx];
			IndexCount += face.mNumIndices;
		}
	}

	Vertices = (Vertex*)malloc(VertCount * sizeof(Vertex));
	Indices = (uint32_t*)malloc(IndexCount * sizeof(uint32_t));
	Skeletons = (Skeleton*)calloc(SkeletonCount, sizeof(Skeleton));
	//Load Verts into Vertices
	int offset = 0, indice_offset = 0, skeleton_offset = 0;
	for (unsigned mesh_idx = 0; mesh_idx < model->mNumMeshes; ++mesh_idx)
	{
		auto mesh = model->mMeshes[mesh_idx];
		if(mesh->HasPositions())
			for (unsigned vert_idx = 0; vert_idx < mesh->mNumVertices; ++vert_idx)
			{
				auto vert = mesh->mVertices[vert_idx];
				Vertices[vert_idx + offset].x = vert.x;
				Vertices[vert_idx + offset].y = vert.y;
				Vertices[vert_idx + offset].z = vert.z;
			}
		if (mesh->HasFaces())
			for (unsigned face_idx = 0; face_idx < mesh->mNumFaces; ++face_idx)
			{
				auto face = mesh->mFaces[face_idx];
				Indices[0 + indice_offset] = face.mIndices[0] + offset;
				Indices[1 + indice_offset] = face.mIndices[1] + offset;
				Indices[2 + indice_offset] = face.mIndices[2] + offset;
				indice_offset += 3;
			}
		if (mesh->HasBones())
		{
			Skeletons[skeleton_offset].bones = (Skeleton::Bone*)malloc(mesh->mNumBones * sizeof(Skeleton::Bone));
			for (unsigned bone_idx = 0; bone_idx < mesh->mNumBones; ++bone_idx)
			{
				auto bone = mesh->mBones[bone_idx];
				//bone->
				printf("%s\n", bone->mName.C_Str());
			}
			++skeleton_offset;
		}
		offset += mesh->mNumVertices;
	}

	delete model;
}

Model::~Model()
{
	free(Vertices);
	free(Indices);
	free(Skeletons);
}