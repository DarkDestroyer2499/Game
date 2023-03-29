#include "Editor.hpp"
#include "Util/Log.hpp"
#include <Core/Serializer.hpp>

namespace Oblivion
{
	Editor::Editor(sf::RenderTexture* newTexture, Engine& engine) :
		mTexture{ newTexture }, mEngine{ engine }, mEvent{}, ecs{ this }
	{
		mWindow.create(sf::VideoMode(1200, 900), "Oblivion Engine", ScreenMode::Resize | ScreenMode::Close);

		mView = mWindow.getDefaultView();

		ImGui::SFML::Init(mWindow, false);

		auto& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		io.Fonts->AddFontDefault();

		auto* fontComponent = ecs.AddComponent<FontComponent>(this);

		fontComponent->AddFont("../resources/fonts/Noto_Sans/NotoSans-Medium.ttf", "MAIN_FONT", 17, ImFontConfig(), nullptr);

		// Add character ranges and merge into main font
		ImWchar ranges[] = { 0xf000, 0xf3ff, 0 };
		ImFontConfig config;
		config.MergeMode = true;

		fontComponent->AddFont("../resources/fontAwersome/fa-regular-400.ttf", "ICON_FONT", 48, config, ranges);

		io.FontDefault = fontComponent->GetFont("MAIN_FONT");

		ImGui::SFML::UpdateFontTexture();
	}

	Editor::~Editor()
	{
		ImGui::SFML::Shutdown();
	}

	void Editor::EventHandler()
	{
		switch (mEvent.type)
		{
		case sf::Event::Closed:
		{
			mWindow.close();
			break;
		}
		case sf::Event::MouseButtonPressed:
		{
			mMousePosition = sf::Mouse::getPosition(mWindow);

			auto tmpCoords = WindowToViewportCoords(Vec2((float)mMousePosition.x, (float)mMousePosition.y));
			auto translatedPos = mWindow.mapPixelToCoords(sf::Vector2i((int)tmpCoords.x, (int)tmpCoords.y));
			if (!ecs.GetComponent<SelectionHandlerComponent>()->IsInsideWorkspace(tmpCoords))
				return;

			Serializer s(&mEngine, *mEngine.GetCurrentScene());

			s.Deserialize(*mEngine.GetCurrentScene(), mEngine.GetCurrentScene()->GetName() + ".yaml");

			ecs.GetComponent<SelectionHandlerComponent>()->TrySelectObject(translatedPos);
			break;
		}
		case sf::Event::Resized:
		{
			sf::FloatRect visibleArea(0, 0, (float)mEvent.size.width, (float)mEvent.size.height);
			mWindow.setView(sf::View(visibleArea));
			Log(INFO, "RESIZED!");			
			break;
		}
		}
	}

	void Editor::KeyboardHandler()
	{
	}

	Vec2 Editor::WindowToViewportCoords(const Vec2& windowCoords)
	{
		Vec2 viewPos = ecs.GetComponent<ViewportComponent>()->GetPosition();
		return Vec2(windowCoords.x - viewPos.x, windowCoords.y - viewPos.y);
	}

	void Editor::Run()
	{
		while (mWindow.isOpen()) {
			while (mWindow.pollEvent(mEvent)) {
				ImGui::SFML::ProcessEvent(mWindow, mEvent);
				EventHandler();
			}

			ImGui::SFML::Update(mWindow, mClock.restart());

			mWindow.clear();
			mTexture->clear(EDITOR_BG_COLOR);

			ImGui::DockSpaceOverViewport();
			
			
			for (auto& component : ecs.GetComponentList())
			{
				component->Update();
			}

			mEngine.Update(mTexture);
			
			ImGui::ShowDemoWindow();
			ImGui::SFML::Render(mWindow);

			mTexture->display();
			mWindow.display();
		}
	}
	Engine* Editor::GetEngine()
	{
		return &mEngine;
	}
	sf::RenderTexture* Editor::GetRenderTexture()
	{
		return mTexture;
	}
}