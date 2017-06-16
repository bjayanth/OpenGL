#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(GameComponent)

	GameComponent::GameComponent() :
		mGame(nullptr), mEnabled(true)
	{
	}

	GameComponent::GameComponent(Game& game) :
		mGame(&game), mEnabled(true)
	{
	}

	void GameComponent::Initialize()
	{
	}

	void GameComponent::Update(const GameTime& gameTime)
	{
		UNREFERENCED_PARAMETER(gameTime);
	}
}
