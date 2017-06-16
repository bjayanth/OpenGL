#pragma once

#include <string>
#include <vector>

struct aiNode;

namespace Library
{
    class Mesh;
    class ModelMaterial;

    class Model final
    {
		friend class Mesh;

    public:
        Model(const std::string& filename, bool flipUVs = false);
		Model(const Model&) = delete;
		Model& operator=(const Model&) = delete;
		Model(Model&&);
		Model& operator=(Model&&);
        ~Model();

        bool HasMeshes() const;
        bool HasMaterials() const;

        const std::vector<Mesh*>& Meshes() const;
        const std::vector<ModelMaterial*>& Materials() const;

    private:
        std::vector<Mesh*> mMeshes;
        std::vector<ModelMaterial*> mMaterials;
    };
}
