#include "pch.h"

using namespace std;

namespace Library
{
	RTTI_DEFINITIONS(Game)

	const uint32_t Game::DefaultScreenWidth = 800;
	const uint32_t Game::DefaultScreenHeight = 600;

	Game* Game::sInternalInstance = nullptr;

	Game::Game(HINSTANCE instance, const wstring& windowTitle) :
		mInstance(instance), mWindow(nullptr), mWindowTitle(windowTitle),
		mScreenWidth(DefaultScreenWidth), mScreenHeight(DefaultScreenHeight), mIsFullScreen(false),		  
		mMajorVersion(0), mMinorVersion(0),
		mDepthStencilBufferEnabled(false)
	{
		GlobalServices.AddService(TypeIdClass(), this);
	}

	HINSTANCE Game::Instance() const
	{
		return mInstance;
	}

	GLFWwindow* Game::Window() const
	{
		return mWindow;
	}

	HWND Game::WindowHandle() const
	{
		return glfwGetWin32Window(mWindow);
	}

	bool Game::DepthStencilBufferEnabled() const
	{
		return mDepthStencilBufferEnabled;
	}

	const wstring& Game::WindowTitle() const
	{
		return mWindowTitle;
	}

	int Game::ScreenWidth() const
	{
		return mScreenWidth;
	}

	int Game::ScreenHeight() const
	{
		return mScreenHeight;
	}

	float Game::AspectRatio() const
	{
		return static_cast<float>(mScreenWidth) / mScreenHeight;
	}
	
	bool Game::IsFullScreen() const
	{
		return mIsFullScreen;
	}

	const vector<shared_ptr<GameComponent>>& Game::Components() const
	{
		return mComponents;
	}

	const ServiceContainer& Game::Services() const
	{
		return mServices;
	}

	void Game::Run()
	{
		sInternalInstance = this;

		InitializeWindow();
		InitializeOpenGL();
		Initialize();

		mGameClock.Reset();

		while (!glfwWindowShouldClose(mWindow))
		{
			mGameClock.UpdateGameTime(mGameTime);
			Update(mGameTime);
			Draw(mGameTime);

			glfwPollEvents();
		}

		Shutdown();
	}

	void Game::Exit()
	{
		glfwSetWindowShouldClose(mWindow, GL_TRUE);
	}

	void Game::Initialize()
	{
		for (auto& component : mComponents)
		{
			component->Initialize();
		}
	}

	void Game::Update(const GameTime& gameTime)
	{
		for (auto& component : mComponents)
		{
			if (component->Enabled())
			{
				component->Update(gameTime);
			}
		}
	}

	void Game::Draw(const GameTime& gameTime)
	{
		for (auto& component : mComponents)
		{
			DrawableGameComponent* drawableGameComponent = component->As<DrawableGameComponent>();
			if (drawableGameComponent != nullptr && drawableGameComponent->Visible())
			{
				drawableGameComponent->Draw(gameTime);
			}
		}
	}

	void Game::AddKeyboardHandler(KeyboardHandler handler)
	{
		mKeyboardHandlers[&handler] = handler;
	}

	void Game::RemoveKeyboardHandler(KeyboardHandler handler)
	{
		mKeyboardHandlers.erase(&handler);
	}

	void Game::InitializeWindow()
	{
		if (!glfwInit())
		{
			throw GameException("glfwInit() failed.");
		}

		GLFWmonitor* monitor = (mIsFullScreen ? glfwGetPrimaryMonitor() : nullptr);
		mWindow = glfwCreateWindow(mScreenWidth, mScreenHeight, Utility::ToString(mWindowTitle).c_str(), monitor, nullptr);
		if (mWindow == nullptr)
		{
			Shutdown();
			throw GameException("glfwCreateWindow() failed.");
		}

		POINT center = CenterWindow(mScreenWidth, mScreenHeight);
		glfwSetWindowPos(mWindow, center.x, center.y);
	}

	void Game::InitializeOpenGL()
	{
		glfwMakeContextCurrent(mWindow);
		
		if (gl3wInit() != 0)
		{
			throw GameException("gl3wInit() failed.");
		}

		glGetIntegerv(GL_MAJOR_VERSION, &mMajorVersion);
		glGetIntegerv(GL_MINOR_VERSION, &mMinorVersion);

		if (mDepthStencilBufferEnabled)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
		}

		glViewport(0, 0, mScreenWidth, mScreenHeight);

		glfwSetKeyCallback(mWindow, Game::OnKey);
	}

	void Game::Shutdown()
	{
		mComponents.clear();
		mComponents.shrink_to_fit();
		mKeyboardHandlers.clear();
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	void Game::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		UNREFERENCED_PARAMETER(window);

		for (const auto& handler : sInternalInstance->mKeyboardHandlers)
		{
			handler.second(key, scancode, action, mods);
		}
	}
	
	POINT Game::CenterWindow(int windowWidth, int windowHeight)
	{
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		POINT center;
		center.x = (screenWidth - windowWidth) / 2;
		center.y = (screenHeight - windowHeight) / 2;

		return center;
	}	
}