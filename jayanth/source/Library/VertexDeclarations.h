#pragma once

#include "glm/glm.hpp"

namespace Library
{
	class VertexPosition final
    {
	public:
        glm::vec4 Position;

        VertexPosition() { }

		VertexPosition(const glm::vec4& position) :
			Position(position){ }
    };

	class VertexPositionColor final
    {
	public:
        glm::vec4 Position;
        glm::vec4 Color;

        VertexPositionColor() { }

		VertexPositionColor(const glm::vec4& position, const glm::vec4& color) :
			Position(position), Color(color) { }
    };

	class VertexPositionColorTexture final
	{
	public:
		glm::vec4 Position;
		glm::vec4 Color;
		glm::vec2 TextureCoordinates;

		VertexPositionColorTexture() { }

		VertexPositionColorTexture(const glm::vec4& position, const glm::vec4& color, const glm::vec2& textureCoordinates) :
			Position(position), Color(color), TextureCoordinates(textureCoordinates) { }
	};

	class VertexPositionTexture final
	{
	public:
		glm::vec4 Position;
		glm::vec2 TextureCoordinates;

		VertexPositionTexture() { }

		VertexPositionTexture(const glm::vec4& position, const glm::vec2& textureCoordinates) :
			Position(position), TextureCoordinates(textureCoordinates) { }
	};

	class VertexPositionSize final
	{
	public:
		glm::vec4 Position;
		glm::vec2 Size;

		VertexPositionSize() { }

		VertexPositionSize(const glm::vec4& position, const glm::vec2& size) :
			Position(position), Size(size) { }
	};

	class VertexPositionNormal final
    {
	public:
        glm::vec4 Position;
        glm::vec3 Normal;

        VertexPositionNormal() { }

		VertexPositionNormal(const glm::vec4& position, const glm::vec3& normal) :
			Position(position), Normal(normal) { }
    };

	class VertexPositionTextureNormal final
	{
	public:
		glm::vec4 Position;
		glm::vec2 TextureCoordinates;
		glm::vec3 Normal;

		VertexPositionTextureNormal() { }

		VertexPositionTextureNormal(const glm::vec4& position, const glm::vec2& textureCoordinates, const glm::vec3& normal) :
			Position(position), TextureCoordinates(textureCoordinates), Normal(normal) { }
	};

	class VertexPositionTextureNormalTangentBinormal final
	{
	public:
		glm::vec4 Position;
		glm::vec2 TextureCoordinates;
		glm::vec3 Normal;
		glm::vec3 Tangent;
		glm::vec3 Binormal;

		VertexPositionTextureNormalTangentBinormal() { }

		VertexPositionTextureNormalTangentBinormal(const glm::vec4& position, const glm::vec2& textureCoordinates, const glm::vec3& normal, const glm::vec3& tangent, const glm::vec3& binormal) :
			Position(position), TextureCoordinates(textureCoordinates), Normal(normal), Tangent(tangent), Binormal(binormal) { }
	};

	class VertexSkinnedPositionTextureNormal final
	{
	public:
		glm::vec4 Position;
		glm::vec2 TextureCoordinates;
		glm::vec3 Normal;
		glm::uvec4 BoneIndices;
		glm::vec4 BoneWeights;

		VertexSkinnedPositionTextureNormal() { }

		VertexSkinnedPositionTextureNormal(const glm::vec4& position, const glm::vec2& textureCoordinates, const glm::vec3& normal, const glm::uvec4& boneIndices, const glm::vec4& boneWeights) :
			Position(position), TextureCoordinates(textureCoordinates), Normal(normal), BoneIndices(boneIndices), BoneWeights(boneWeights) { }
	};
}
