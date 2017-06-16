#pragma once

#include "glm/glm.hpp"
#include "DrawableGameComponent.h"
#include "BasicEffect.h"

namespace Library
{
	class Mesh;

	class ProxyModel final : public DrawableGameComponent
	{
		RTTI_DECLARATIONS(ProxyModel, DrawableGameComponent)

	public:
		ProxyModel(Game& game, Camera& camera, const std::string& modelFileName, float scale = 1.0f);
		ProxyModel(const ProxyModel&) = delete;
		ProxyModel& operator=(const ProxyModel&) = delete;
		ProxyModel(ProxyModel&&) = delete;
		ProxyModel& operator=(ProxyModel&&) = delete;
		~ProxyModel();

		const glm::vec3& Position() const;
        const glm::vec3& Direction() const;
        const glm::vec3& Up() const;
        const glm::vec3& Right() const;

		bool& DisplayWireframe();

		void SetPosition(float x, float y, float z);
        void SetPosition(const glm::vec3& position);

        void ApplyRotation(const glm::mat4& transform);

		virtual void Initialize() override;
		virtual void Update(const GameTime& gameTime) override;		
		virtual void Draw(const GameTime& gameTime) override;

	private:
		glm::mat4 mWorldMatrix;
		glm::mat4 mScaleMatrix;
		glm::vec3 mPosition;
		glm::vec3 mDirection;
		glm::vec3 mUp;
		glm::vec3 mRight;				
		std::string mModelFileName;
		GLuint mVertexArrayObject;
		GLuint mVertexBuffer;
		GLuint mIndexBuffer;
		std::uint32_t mIndexCount;				
		bool mDisplayWireframe;
		BasicEffect mShaderProgram;
	};
}