#pragma once

#include "glm/glm.hpp"
#include "DrawableGameComponent.h"
#include "BasicEffect.h"

namespace Library
{
	class Game;
	class Camera;

	class Grid final : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(Grid, DrawableGameComponent)

	public:
		Grid(Game& game, Camera& camera, GLuint size = DefaultSize, GLuint scale = DefaultScale, const glm::vec4& color = DefaultColor);
		Grid(const Grid&) = delete;
		Grid& operator=(const Grid&) = delete;
		Grid(Grid&&) = delete;
		Grid& operator=(Grid&&) = delete;
		~Grid();

		const glm::vec3& Position() const;
		const glm::vec4& Color() const;
		const GLuint Size() const;
		const GLuint Scale() const;

		void SetPosition(const glm::vec3& position);
		void SetPosition(float x, float y, float z);
		void SetColor(const glm::vec4& color);
		void SetSize(GLuint size);
		void SetScale(GLuint scale);

		virtual void Initialize() override;
		virtual void Draw(const GameTime& gameTime) override;

	private:
		void InitializeGrid();

		static const GLuint DefaultSize;
		static const GLuint DefaultScale;
		static const glm::vec4 DefaultColor;

		glm::mat4 mWorldMatrix;
		glm::vec4 mColor;
		glm::vec3 mPosition;
		BasicEffect mShaderProgram;
		GLuint mVertexArrayObject;
		GLuint mVertexBuffer;		
		GLuint mSize;
		GLuint mScale;
		std::uint32_t mVertexCount;
	};
}