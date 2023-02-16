#include "Editor.hpp"
#include "../Util/Log.hpp"

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

bool Editor::IsAlreadySelected(Entity& entity)
{
	for (auto& selectedEntity : mSelectedObjects)
	{
		if (&entity == &selectedEntity.entity)
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
		
		auto tmpCoords = WindowToViewportCoords(Vec2((float)mMousePosition.x, (float)mMousePosition.y));

		if (!IsInsideWorkspace(tmpCoords))
			return;

		Log(INFO, "Position: (" << mMousePosition.x << " : " << mMousePosition.y << ")\t" << GetComponent<ViewportComponent>()->GetPosition() << "\t" << WindowToViewportCoords(Vec2((float)mMousePosition.x, (float)mMousePosition.y)) << "\t" << mSelectedObjects.size());
		auto translated_pos = mWindow.mapPixelToCoords(sf::Vector2i((int)tmpCoords.x, (int)tmpCoords.y));
		bool isEmptySpaceClicked = true;
		
		for (auto& entity : mEngine.mObjectList)
		{
			auto tmp = entity.GetComponent<GraphicsComponent>();
			if (!tmp)
				continue;

			if (tmp->GetSprite().getGlobalBounds().contains(translated_pos))
			{
				isEmptySpaceClicked = false;
				if (!IsAlreadySelected(entity))
					mSelectedObjects.push_back(SelectedObject(entity, UIVisualSelector()));
				else
					Log(WARNING, "Already selected!");
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
	Vec2 viewPos = GetComponent<ViewportComponent>()->GetPosition();
	return Vec2(windowCoords.x - viewPos.x, windowCoords.y - viewPos.y);
}

bool Editor::IsInsideWorkspace(Vec2 translatedMousePos)
{
	Vec2 viewSize = GetComponent<ViewportComponent>()->mSize;
	if (translatedMousePos.x >= 0 && translatedMousePos.x <= viewSize.x &&
		translatedMousePos.y >= 0 && translatedMousePos.y <= viewSize.y)
		return true;
	else
		return false;
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
		mEngine.Update(mTexture);
		//TODO: create other panel components
		for (auto& component : mComponentList)
		{
			component->Update();
		}
		
		for (int i = 0; i < mSelectedObjects.size(); ++i)
		{
			mSelectedObjects[i].selector.Update(&mSelectedObjects[i].entity);
			mSelectedObjects[i].selector.Draw(mTexture);
		}

		ImGui::ShowDemoWindow();
		ImGui::SFML::Render(mWindow);
		
		mTexture->display();
		mWindow.display();
	}
}
