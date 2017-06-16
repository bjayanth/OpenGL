#pragma once

#include "Light.h"

namespace Library
{
	class DirectionalLight : public Light
	{
		RTTI_DECLARATIONS(DirectionalLight, Light)

	public:
		DirectionalLight(Game& game);
		DirectionalLight(const DirectionalLight&) = default;
		DirectionalLight& operator=(const DirectionalLight&) = default;
		DirectionalLight(DirectionalLight&&) = default;
		DirectionalLight& operator=(DirectionalLight&&) = default;
		virtual ~DirectionalLight() = default;

		const glm::vec3& Direction() const;
		const glm::vec3& Up() const;
		const glm::vec3& Right() const;

        void ApplyRotation(const glm::mat4& transform);

	protected:
		glm::vec3 mDirection;
		glm::vec3 mUp;
		glm::vec3 mRight;
	};
}

