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

bool Editor::IsAlreadySelected(Entity& entity)
{
	for (auto& selectedEntity : mSelectedObjects)
	{
		if (&entity == selectedEntity)
		{
			return true;
		}
	}
	return false;
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
		std::cout << "Position: (" << mMousePosition.x << " : " << mMousePosition.y << ")\n";
		for (auto& entity : mEngine.mObjectList)
		{
			auto tmp = entity.GetComponent<GraphicsComponent>();
			if (tmp)
			{
				auto translated_pos = mWindow.mapPixelToCoords(mMousePosition); // Mouse position translated into world coordinates
				if (tmp->GetSprite().getGlobalBounds().contains(translated_pos))
				{
					if (!IsAlreadySelected(entity))
						mSelectedObjects.push_back(&entity);
				}
			}
		}
		break;
	}
	}
}

void Editor::Run()
{
	while (mWindow.isOpen()) {
		while (mWindow.pollEvent(mEvent)) {
			ImGui::SFML::ProcessEvent(mWindow, mEvent);

			EventHandler();
		}

		ImGui::SFML::Update(mWindow, mClock.restart());

		mUI->Update();

		mWindow.clear();

		mEngine.Update(mTexture);

		ImGui::SFML::Render(mWindow);
		mWindow.display();
	}
}
