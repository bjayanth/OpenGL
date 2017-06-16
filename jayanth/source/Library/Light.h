#pragma once

#include "GameComponent.h"
#include "glm/glm.hpp"

namespace Library
{
	class Light : public GameComponent
	{
		RTTI_DECLARATIONS(Light, GameComponent)

	public:
		Light(Game& game);
		Light(const Light&) = default;
		Light& operator=(const Light&) = default;
		Light(Light&&) = default;
		Light& operator=(Light&&) = default;		
		virtual ~Light() = default;

		const glm::vec4& Color() const;
		void SetColor(float r, float g, float b, float a);
		void SetColor(const glm::vec4& color);

	protected:
		glm::vec4 mColor;
	};
}

