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

			//ImGui::ShowDemoWindow();
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

		fontComponent->AddFont("../resources/fonts/Noto_Sans/NotoSans-Medium.ttf", "MAIN_FONT", 16, ImFontConfig(), nullptr);

		// Add character ranges and merge into main font
		ImWchar ranges[] = { 0xf000, 0xf3ff, 0 };
		ImFontConfig config;
		config.MergeMode = true;

		fontComponent->AddFont("../resources/fontAwersome/fa-regular-400.ttf", "ICON_FONT", 48, config, ranges);

		io.FontDefault = fontComponent->GetFont("MAIN_FONT");

		// Modern ImGui Style
		ImGuiStyle& style = ImGui::GetStyle();

		// Rounding
		style.WindowRounding = 6.0f;
		style.ChildRounding = 6.0f;
		style.FrameRounding = 4.0f;
		style.PopupRounding = 4.0f;
		style.ScrollbarRounding = 9.0f;
		style.GrabRounding = 3.0f;
		style.TabRounding = 4.0f;

		// Spacing
		style.WindowPadding = ImVec2(10.0f, 10.0f);
		style.FramePadding = ImVec2(6.0f, 4.0f);
		style.ItemSpacing = ImVec2(8.0f, 6.0f);
		style.ItemInnerSpacing = ImVec2(6.0f, 4.0f);
		style.IndentSpacing = 22.0f;
		style.ScrollbarSize = 14.0f;
		style.GrabMinSize = 10.0f;

		// Borders
		style.WindowBorderSize = 1.0f;
		style.ChildBorderSize = 1.0f;
		style.PopupBorderSize = 1.0f;
		style.FrameBorderSize = 0.0f;
		style.TabBorderSize = 0.0f;

		// Modern color scheme - Dark theme with blue accent
		ImVec4* colors = style.Colors;

		// Main background colors
		colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.11f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.12f, 0.13f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.11f, 0.11f, 0.12f, 0.98f);

		// Text
		colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);

		// Borders
		colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

		// Frame backgrounds (input fields, etc)
		colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.17f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.24f, 0.24f, 0.26f, 1.00f);

		// Title bar
		colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.10f, 0.10f, 0.11f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.08f, 0.08f, 0.09f, 0.75f);

		// Menu bar
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.12f, 0.12f, 0.13f, 1.00f);

		// Scrollbar
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.10f, 0.11f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.30f, 0.30f, 0.32f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.42f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.50f, 0.50f, 0.52f, 1.00f);

		// Checkmark
		colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

		// Slider
		colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

		// Button
		colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.30f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

		// Header (collapsing header, tree nodes)
		colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.30f, 0.55f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

		// Separator
		colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

		// Resize grip
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4(0.14f, 0.14f, 0.15f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.30f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.14f, 0.14f, 0.15f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.18f, 0.18f, 0.20f, 1.00f);

		// Docking
		colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);

		// Plot
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);

		// Table
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.16f, 0.16f, 0.17f, 1.00f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.18f, 0.18f, 0.20f, 1.00f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.03f);

		// Drag and drop
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);

		// Navigation
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

		// Modal
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.60f);

		ImGui::SFML::UpdateFontTexture();
	}
}