#include "Editor.hpp"
#include "../lib/imgui/imgui.h"
#include "../lib/imgui/imgui-SFML.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

//Editor::Editor(sf::RenderTexture* newTexture, ExternalRenderCallback callback):
//	mTexture(newTexture), mExCallback(callback)
//{
//	mWindow.create(sf::VideoMode(900, 800), "Engine", 1 << 2);
//	ImGui::SFML::Init(mWindow);
//	auto& io = ImGui::GetIO();
//	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
//
//	mTexture->create(0,0);
//	
//}

Editor::Editor(sf::RenderTexture* newTexture, Engine& engine) :
	mTexture{ newTexture }, mEngine{ engine }, mEvent{}
{
	mWindow.create(sf::VideoMode(900, 800), "Engine", 1 << 2);
	ImGui::SFML::Init(mWindow);
	auto& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

Editor::~Editor()
{
	ImGui::SFML::Shutdown();
}

void Editor::Run()
{
	while (mWindow.isOpen()) {
		while (mWindow.pollEvent(mEvent)) {
			ImGui::SFML::ProcessEvent(mWindow, mEvent);

			if (mEvent.type == sf::Event::Closed) {
				mWindow.close();
			}
		}

		ImGui::SFML::Update(mWindow, mClock.restart());

		ImGui::DockSpaceOverViewport();
		static ImVec2 viewportSize = ImGui::GetWindowSize();
		mTexture->create(viewportSize.x, viewportSize.y);

		ImGui::ShowDemoWindow();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));

		if (ImGui::Begin("Viewport")) {
			viewportSize = ImGui::GetWindowSize();
			ImGui::Image(*mTexture);
		}

		ImGui::End();
		ImGui::PopStyleVar();

		mWindow.clear();

		mEngine.Update(mTexture);

		ImGui::SFML::Render(mWindow);
		mWindow.display();
	}
}

