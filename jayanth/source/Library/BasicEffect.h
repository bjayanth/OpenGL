#pragma once

#include "ShaderProgram.h"
#include "VertexDeclarations.h"

namespace Library
{
	class Mesh;

	class BasicEffect final : public ShaderProgram
    {
		RTTI_DECLARATIONS(BasicEffect, ShaderProgram)

        SHADER_VARIABLE_DECLARATION(WorldViewProjection)

    public:
        BasicEffect();
		BasicEffect(const BasicEffect&) = delete;
		BasicEffect& operator=(const BasicEffect&) = delete;
		BasicEffect(BasicEffect&&) = delete;
		BasicEffect& operator=(BasicEffect&&) = delete;
		~BasicEffect() = default;

		virtual void Initialize(GLuint vertexArrayObject) override;
		virtual void CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer) const override;
		void CreateVertexBuffer(VertexPositionColor* vertices, std::uint32_t vertexCount, GLuint& vertexBuffer) const;
		virtual std::uint32_t VertexSize() const override;

	private:
		enum class VertexAttribute
		{
			Position = 0,
			Color = 1
		};
    };
}