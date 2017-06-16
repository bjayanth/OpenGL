namespace Library
{
	inline Game* GameComponent::GetGame()
	{
		return mGame;
	}

	inline void GameComponent::SetGame(Game& game)
	{
		mGame = &game;
	}

	inline bool GameComponent::Enabled() const
	{
		return mEnabled;
	}

	inline void GameComponent::SetEnabled(bool enabled)
	{
		mEnabled = enabled;
	}
}