#pragma once

#include "PointLight.h"

namespace Library
{
	class SpotLight : public PointLight
	{
		RTTI_DECLARATIONS(SpotLight, PointLight)

	public:
		SpotLight(Game& game);
		SpotLight(const SpotLight&) = default;
		SpotLight& operator=(const SpotLight&) = default;
		SpotLight(SpotLight&&) = default;
		SpotLight& operator=(SpotLight&&) = default;
		virtual ~SpotLight() = default;
	
		const glm::vec3& Direction() const;
		const glm::vec3& Up() const;
		const glm::vec3& Right() const;

		float InnerAngle();
		void SetInnerAngle(float value);
		
		float OuterAngle();
		void SetOuterAngle(float value);

        void ApplyRotation(const glm::mat4& transform);

		static const float DefaultInnerAngle;
		static const float DefaultOuterAngle;

	protected:
		glm::vec3 mDirection;
		glm::vec3 mUp;
		glm::vec3 mRight;
		float mInnerAngle;
		float mOuterAngle;
	};
}