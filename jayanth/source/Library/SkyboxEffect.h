#pragma once

#include "ShaderProgram.h"
#include "VertexDeclarations.h"

namespace Library
{
	class Mesh;

	class SkyboxEffect final : public ShaderProgram
    {
		RTTI_DECLARATIONS(SkyboxEffect, ShaderProgram)

        SHADER_VARIABLE_DECLARATION(WorldViewProjection)

    public:
        SkyboxEffect();
		SkyboxEffect(const SkyboxEffect&) = delete;
		SkyboxEffect& operator=(const SkyboxEffect&) = delete;
		SkyboxEffect(SkyboxEffect&&) = delete;
		SkyboxEffect& operator=(SkyboxEffect&&) = delete;
		~SkyboxEffect() = default;

		virtual void Initialize(GLuint vertexArrayObject) override;
		virtual void CreateVertexBuffer(const Mesh& mesh, GLuint& vertexBuffer) const override;
		void CreateVertexBuffer(VertexPosition* vertices, std::uint32_t vertexCount, GLuint& vertexBuffer) const;
		virtual std::uint32_t VertexSize() const override;

	private:
		enum VertexAttribute
		{
			VertexAttributePosition = 0,
		};
    };
}