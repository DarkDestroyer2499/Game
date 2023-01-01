#include "Editor.hpp"

Editor::Editor(sf::RenderTexture* newTexture, Engine& engine) :
	mTexture{ newTexture }, mEngine{ engine }, mEvent{}
{
	mUI = std::make_unique<UI>(this);
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

		mUI->Update();

		mWindow.clear();

		mEngine.Update(mTexture);

		ImGui::SFML::Render(mWindow);
		mWindow.display();
	}
}
