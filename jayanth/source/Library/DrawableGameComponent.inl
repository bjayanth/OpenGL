namespace Library
{
	inline bool DrawableGameComponent::Visible() const
	{
		return mVisible;
	}

	inline void DrawableGameComponent::SetVisible(bool visible)
	{
		mVisible = visible;
	}

	inline Camera* DrawableGameComponent::GetCamera()
	{
		return mCamera;
	}

	inline void DrawableGameComponent::SetCamera(Camera* camera)
	{
		mCamera = camera;
	}
}