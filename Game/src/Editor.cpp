#include "Editor.hpp"
#include "Log.hpp"

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
		Log(INFO, "Position: (" << mMousePosition.x << " : " << mMousePosition.y << ")\t" << mUI->GetViewportPosition() << "\t" << WindowToViewportCoords(Vec2(mMousePosition.x, mMousePosition.y)) << "\t" << mSelectedObjects.size());
		
		bool isEmptySpaceClicked = true;
		for (auto& entity : mEngine.mObjectList)
		{
			auto tmp = entity.GetComponent<GraphicsComponent>();
			if (tmp)
			{
				auto tmpCoords = WindowToViewportCoords(Vec2(mMousePosition.x, mMousePosition.y));
				auto translated_pos = mWindow.mapPixelToCoords(sf::Vector2i(tmpCoords.x, tmpCoords.y));
				if (tmp->GetSprite().getGlobalBounds().contains(translated_pos))
				{
					isEmptySpaceClicked = false;
					if (!IsAlreadySelected(entity))
						mSelectedObjects.push_back(&entity);
					else
						Log(WARNING, "Already selected!");
				}
			}
		}

		if (isEmptySpaceClicked)
		{
			mSelectedObjects.clear();
		}
		break;
	}
	}
}

Vec2 Editor::WindowToViewportCoords(const Vec2 &windowCoords)
{
	Vec2 viewPos = mUI->GetViewportPosition();
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

		//Log(INFO, mEngine.mObjectList[0].GetPosition());

		mUI->Update();

		mEngine.Update(mTexture);

		ImGui::SFML::Render(mWindow);
		mTexture->display();
		mWindow.display();
	}
}
