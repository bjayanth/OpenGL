#include "pch.h"

using namespace std;

namespace Library
{
    Model::Model(const string& filename, bool flipUVs) :
		mMeshes(), mMaterials()
    {
        Assimp::Importer importer;

		uint32_t flags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType;
        if (flipUVs)
        {
            flags |= aiProcess_FlipUVs;
        }

        const aiScene* scene = importer.ReadFile(filename, flags);
        if (scene == nullptr)
        {
            throw GameException(importer.GetErrorString());
        }

        if (scene->HasMaterials())
        {
            for (uint32_t i = 0; i < scene->mNumMaterials; i++)
            {
                mMaterials.push_back(new ModelMaterial(*this, scene->mMaterials[i]));
            }
        }

        if (scene->HasMeshes())
        {
            for (uint32_t i = 0; i < scene->mNumMeshes; i++)
            {	
				Mesh* mesh = new Mesh(*this, *(scene->mMeshes[i]));
                mMeshes.push_back(mesh);
            }
        }
	}

	Model::Model(Model&& rhs) :
		mMeshes(move(rhs.mMeshes)), mMaterials(move(rhs.mMaterials))
	{
	}

	Model & Model::operator=(Model&& rhs)
	{
		if (this != &rhs)
		{
			mMeshes = move(rhs.mMeshes);
			mMaterials = move(rhs.mMaterials);
		}

		return *this;
	}
	
    Model::~Model()
    {
        for (Mesh* mesh : mMeshes)
        {
            delete mesh;
        }

        for (ModelMaterial* material : mMaterials)
        {
            delete material;
        }
    }

    bool Model::HasMeshes() const
    {
        return (mMeshes.size() > 0);
    }

    bool Model::HasMaterials() const
    {
        return (mMaterials.size() > 0);
    }

    const vector<Mesh*>& Model::Meshes() const
    {
        return mMeshes;
    }

    const vector<ModelMaterial*>& Model::Materials() const
    {
        return mMaterials;
    }
}
