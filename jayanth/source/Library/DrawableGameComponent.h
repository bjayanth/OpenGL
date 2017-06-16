#pragma once

#include "GameComponent.h"

namespace Library
{
	class Camera;

	class DrawableGameComponent : public GameComponent
	{
		RTTI_DECLARATIONS(DrawableGameComponent, GameComponent)

	public:
		DrawableGameComponent();
		DrawableGameComponent(Game& game);
		DrawableGameComponent(Game& game, Camera& camera);
		DrawableGameComponent(const DrawableGameComponent&) = delete;
		DrawableGameComponent& operator=(const DrawableGameComponent&) = delete;
		DrawableGameComponent(DrawableGameComponent&&) = delete;
		DrawableGameComponent& operator=(DrawableGameComponent&&) = delete;
		virtual ~DrawableGameComponent() = default;

		bool Visible() const;
		void SetVisible(bool visible);

		Camera* GetCamera();
		void SetCamera(Camera* camera);

		virtual void Draw(const GameTime& gameTime);

	protected:
		bool mVisible;
		Camera* mCamera;
	};
}

#include "DrawableGameComponent.inl"