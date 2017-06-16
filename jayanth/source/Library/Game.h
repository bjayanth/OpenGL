#pragma once

#include "RTTI.h"
#include "GameClock.h"
#include "GameTime.h"
#include "GameComponent.h"
#include "ServiceContainer.h"
#include <vector>
#include <map>
#include <functional>
#include <memory>

namespace Library
{
	class Game : public RTTI
	{
		RTTI_DECLARATIONS(Game, RTTI)

	public:
		typedef std::function<void(int, int, int, int)> KeyboardHandler;
		
		Game(HINSTANCE instance, const std::wstring& windowTitle);
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
		Game(Game&&) = delete;
		Game& operator=(Game&&) = delete;
		virtual ~Game() = default;

		HINSTANCE Instance() const;
		GLFWwindow* Window() const;
		HWND Game::WindowHandle() const;
		bool DepthStencilBufferEnabled() const;
		const std::wstring& WindowTitle() const;
		int ScreenWidth() const;
		int ScreenHeight() const;
		float AspectRatio() const;
		bool IsFullScreen() const;
		const std::vector<std::shared_ptr<GameComponent>>& Components() const;
		const ServiceContainer& Services() const;

		virtual void Run();
		virtual void Exit();
		virtual void Initialize();
		virtual void Update(const GameTime& gameTime);
		virtual void Draw(const GameTime& gameTime);

		void AddKeyboardHandler(KeyboardHandler handler);
		void RemoveKeyboardHandler(KeyboardHandler handler);

	protected:
		virtual void InitializeWindow();
		virtual void InitializeOpenGL();
		virtual void Shutdown();

		static const std::uint32_t DefaultScreenWidth;
		static const std::uint32_t DefaultScreenHeight;
		static const std::uint32_t DefaultFrameRate;
		
		HINSTANCE mInstance;
		std::wstring mWindowTitle;		
		GLFWwindow* mWindow;
		std::uint32_t mScreenWidth;
		std::uint32_t mScreenHeight;
		bool mIsFullScreen;

		GLint mMajorVersion;
		GLint mMinorVersion;

		bool mDepthStencilBufferEnabled;

		GameClock mGameClock;
		GameTime mGameTime;

		std::vector<std::shared_ptr<GameComponent>> mComponents;
		ServiceContainer mServices;

		std::map<KeyboardHandler*, KeyboardHandler> mKeyboardHandlers;

	private:
		static Game* sInternalInstance;

		static void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods);

		POINT CenterWindow(int windowWidth, int windowHeight);
	};
}