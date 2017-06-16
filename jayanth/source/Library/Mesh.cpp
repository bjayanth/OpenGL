#include "pch.h"

using namespace std;

namespace Library
{
    Mesh::Mesh(Model& model, aiMesh& mesh) :
		mModel(model), mMaterial(nullptr), mName(mesh.mName.C_Str()), mFaceCount(0)
    {
		mMaterial = mModel.Materials().at(mesh.mMaterialIndex);

        // Vertices
        mVertices.reserve(mesh.mNumVertices);
        for (uint32_t i = 0; i < mesh.mNumVertices; i++)
        {
			aiVector3D v = mesh.mVertices[i];
			mVertices.push_back(glm::vec3(v.x, v.y, v.z));
        }

        // Normals
        if (mesh.HasNormals())
        {
            mNormals.reserve(mesh.mNumVertices);
            for (uint32_t i = 0; i < mesh.mNumVertices; i++)
            {
				aiVector3D n = mesh.mNormals[i];
                mNormals.push_back(glm::vec3(n.x, n.y, n.z));
            }
        }

        // Tangents and Binormals
        if (mesh.HasTangentsAndBitangents())
        {
            mTangents.reserve(mesh.mNumVertices);
            mBiNormals.reserve(mesh.mNumVertices);
            for (uint32_t i = 0; i < mesh.mNumVertices; i++)
            {
				aiVector3D t = mesh.mTangents[i];
                mTangents.push_back(glm::vec3(t.x, t.y, t.z));
                
				aiVector3D b = mesh.mBitangents[i];
				mBiNormals.push_back(glm::vec3(b.x, b.y, b.z));
            }
        }

        // Texture Coordinates
        uint32_t uvChannelCount = mesh.GetNumUVChannels();
        for (uint32_t i = 0; i < uvChannelCount; i++)
        {
            vector<glm::vec3>* textureCoordinates = new vector<glm::vec3>();
            textureCoordinates->reserve(mesh.mNumVertices);
            mTextureCoordinates.push_back(textureCoordinates);

            aiVector3D* aiTextureCoordinates = mesh.mTextureCoords[i];
            for (uint32_t j = 0; j < mesh.mNumVertices; j++)
            {
				aiVector3D uv = aiTextureCoordinates[j];
                textureCoordinates->push_back(glm::vec3(uv.x, uv.y, uv.z));
            }
        }

        // Vertex Colors
        uint32_t colorChannelCount = mesh.GetNumColorChannels();
        for (uint32_t i = 0; i < colorChannelCount; i++)
        {
            vector<glm::vec4>* vertexColors = new vector<glm::vec4>();
            vertexColors->reserve(mesh.mNumVertices);
            mVertexColors.push_back(vertexColors);

            aiColor4D* aiVertexColors = mesh.mColors[i];
            for (uint32_t j = 0; j < mesh.mNumVertices; j++)
            {
				aiColor4D c = aiVertexColors[j];
                vertexColors->push_back(glm::vec4(c.r, c.g, c.b, c.a));
            }
        }

        // Faces (note: could pre-reserve if we limit primitive types)
        if (mesh.HasFaces())
        {
            mFaceCount = mesh.mNumFaces;
            for (uint32_t i = 0; i < mFaceCount; i++)
            {
                aiFace* face = &mesh.mFaces[i];
            
                for (uint32_t j = 0; j < face->mNumIndices; j++)
                {		
                    mIndices.push_back(face->mIndices[j]);
                }
            }
        }
    }

    Mesh::~Mesh()
    {
        for (vector<glm::vec3>* textureCoordinates : mTextureCoordinates)
        {
            delete textureCoordinates;
        }

        for (vector<glm::vec4>* vertexColors : mVertexColors)
        {
            delete vertexColors;
        }
    }

    Model& Mesh::GetModel()
    {
        return mModel;
    }

    ModelMaterial* Mesh::GetMaterial()
    {
        return mMaterial;
    }

    const string& Mesh::Name() const
    {
        return mName;
    }

    const vector<glm::vec3>& Mesh::Vertices() const
    {
        return mVertices;
    }

    const vector<glm::vec3>& Mesh::Normals() const
    {
        return mNormals;
    }

    const vector<glm::vec3>& Mesh::Tangents() const
    {
        return mTangents;
    }

    const vector<glm::vec3>& Mesh::BiNormals() const
    {
        return mBiNormals;
    }

    const vector<vector<glm::vec3>*>& Mesh::TextureCoordinates() const
    {
        return mTextureCoordinates;
    }

    const vector<vector<glm::vec4>*>& Mesh::VertexColors() const
    {
        return mVertexColors;
    }

    uint32_t Mesh::FaceCount() const
    {
        return mFaceCount;
    }

    const vector<uint32_t>& Mesh::Indices() const
    {
        return mIndices;
    }

    void Mesh::CreateIndexBuffer(GLuint& indexBuffer)
    {
		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * mIndices.size(), &mIndices[0], GL_STATIC_DRAW);
    }
}