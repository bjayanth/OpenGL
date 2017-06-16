#pragma once

#include "RTTI.h"

namespace Library
{
	class Game;
	class GameTime;

	class GameComponent : public RTTI
	{
		RTTI_DECLARATIONS(GameComponent, RTTI)

	public:
		GameComponent();
		GameComponent(Game& game);
		GameComponent(const GameComponent&) = delete;
		GameComponent& operator=(const GameComponent&) = delete;
		GameComponent(GameComponent&&) = delete;
		GameComponent& operator=(GameComponent&&) = delete;
		virtual ~GameComponent() = default;

		Game* GetGame();
		void SetGame(Game& game);
		bool Enabled() const;
		void SetEnabled(bool enabled);

		virtual void Initialize();
		virtual void Update(const GameTime& gameTime);

	protected:
		Game* mGame;
		bool mEnabled;
	};
}

#include "GameComponent.inl"