#include "pch.h"

using namespace std;

namespace Library
{
    map<TextureType, uint32_t> ModelMaterial::sTextureTypeMappings;

    ModelMaterial::ModelMaterial(Model& model) :
		mModel(model), mTextures()
    {
        InitializeTextureTypeMappings();
    }

    ModelMaterial::ModelMaterial(Model& model, aiMaterial* material) :
		mModel(model), mTextures()
    {
        InitializeTextureTypeMappings();

        aiString name;
        material->Get(AI_MATKEY_NAME, name);
        mName = name.C_Str();

        for (TextureType textureType = TextureType(0); textureType < TextureType::End; textureType = TextureType(static_cast<int>(textureType) + 1))
        {
            aiTextureType mappedTextureType = (aiTextureType)sTextureTypeMappings[textureType];

            uint32_t textureCount = material->GetTextureCount(mappedTextureType);
            if (textureCount > 0)
            {
                vector<wstring>* textures = new vector<wstring>();
                mTextures.insert(pair<TextureType, vector<wstring>*>(textureType, textures));

                textures->reserve(textureCount);
                for (uint32_t textureIndex = 0; textureIndex < textureCount; textureIndex++)
                {
                    aiString path;
                    if (material->GetTexture(mappedTextureType, textureIndex, &path) == AI_SUCCESS)
                    {
                        wstring wPath;
                        Utility::ToWideString(path.C_Str(), wPath);

                        textures->push_back(wPath);
                    }
                }
            }
        }
    }

    ModelMaterial::~ModelMaterial()
    {
        for (pair<TextureType, vector<wstring>*> textures : mTextures)
        {
			delete textures.second;
        }
    }

    Model& ModelMaterial::GetModel()
    {
        return mModel;
    }

    const string& ModelMaterial::Name() const
    {
        return mName;
    }

    const map<TextureType, vector<wstring>*>& ModelMaterial::Textures() const
    {
        return mTextures;
    }

    void ModelMaterial::InitializeTextureTypeMappings()
    {
		if (sTextureTypeMappings.size() != static_cast<int>(TextureType::End))
        {
            sTextureTypeMappings[TextureType::Difffuse] = aiTextureType_DIFFUSE;
            sTextureTypeMappings[TextureType::SpecularMap] = aiTextureType_SPECULAR;
            sTextureTypeMappings[TextureType::Ambient] = aiTextureType_AMBIENT;
            sTextureTypeMappings[TextureType::Heightmap] = aiTextureType_HEIGHT;
            sTextureTypeMappings[TextureType::NormalMap] = aiTextureType_NORMALS;
            sTextureTypeMappings[TextureType::SpecularPowerMap] = aiTextureType_SHININESS;
            sTextureTypeMappings[TextureType::DisplacementMap] = aiTextureType_DISPLACEMENT;
            sTextureTypeMappings[TextureType::LightMap] = aiTextureType_LIGHTMAP;
        }
    }
}