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

		SetupStyles();

		GetEngine()->eventBroadcaster.Attach(EventType::Closed, this);
		GetEngine()->eventBroadcaster.Attach(EventType::Resized, this);
	}

	Editor::~Editor()
	{
		ImGui::SFML::Shutdown();
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
				GetEngine()->eventBroadcaster.Notify(mEvent);
			}

			ImGui::SFML::Update(mWindow, mClock.restart());

			mWindow.clear();

			ImGui::DockSpaceOverViewport();

			mEngine.Update(mTexture);

			for (auto& component : ecs.GetComponentList())
			{
				component->Update();
			}

			ImGui::ShowDemoWindow();
			ImGui::SFML::Render(mWindow);

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

	Vec2 Editor::GetMousePosition()
	{
		return sf::Mouse::getPosition(mWindow);
	}

	sf::RenderWindow& Editor::GetMainWindow()
	{
		return mWindow;
	}

	void Editor::OnWindowClosed()
	{
		mWindow.close();
	}

	void Editor::OnResized(const sf::Event&)
	{
		sf::FloatRect visibleArea(0, 0, (float)mEvent.size.width, (float)mEvent.size.height);
		mWindow.setView(sf::View(visibleArea));

		Log(INFO, "RESIZED!");
	}

	void Editor::SetupStyles()
	{
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

		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.55f, 0.55f, 0.65f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.30f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.30f, 0.30f, 0.35f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.35f, 0.35f, 0.40f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.45f, 0.45f, 0.50f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.60f, 0.60f, 0.65f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.30f, 0.30f, 0.35f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.40f, 0.40f, 0.45f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.50f, 0.50f, 0.55f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.30f, 0.30f, 0.35f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.40f, 0.40f, 0.45f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.50f, 0.50f, 0.55f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.65f, 0.65f, 0.65f, 0.60f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.80f, 0.80f, 0.80f, 0.80f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.46f, 0.69f, 0.99f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.46f, 0.69f, 0.99f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.46f, 0.69f, 0.99f, 0.95f);
		colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

		ImGui::SFML::UpdateFontTexture();
	}
}