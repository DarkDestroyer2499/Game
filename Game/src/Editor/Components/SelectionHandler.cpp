#include "SelectionHandler.hpp"

namespace Oblivion
{
	SelectionHandlerComponent::SelectionHandlerComponent(Editor* editor)
		: mEditor{ editor }, mEngine{ editor->GetEngine() }, mIsCtrlButtonPressed{ false }
	{
		mEntityRemovedEvent = mEngine->mEventBus.Subscribe<EntityRemovedEvent>([this](const EntityRemovedEvent& event)
			{
				OnAnyEntityRemoved(event);
			});

		mMouseButtonPressedEvent = mEngine->mEventBus.Subscribe<MouseButtonPressedEvent>([this](const MouseButtonPressedEvent& event)
			{
				OnMouseButtonPressed(event);
			});

		mKeyPressedEvent = mEngine->mEventBus.Subscribe<KeyPressedEvent>([this](const KeyPressedEvent& event)
			{
				OnKeyPressed(event);
			});

		mKeyReleasedEvent = mEngine->mEventBus.Subscribe<KeyReleasedEvent>([this](const KeyReleasedEvent& event)
			{
				OnKeyReleased(event);
			});
	}


	void SelectionHandlerComponent::Update()
	{
		for (auto& [entity, selector] : mSelectedObjects)
		{
			selector.Update(entity);
			selector.Draw(mEditor->GetRenderTexture());
		}
	}

	void SelectionHandlerComponent::OnMouseButtonPressed(const MouseButtonPressedEvent& event)
	{
		if (event.button != sf::Mouse::Button::Left)
			return;

		Vec2 MouseInViewportPos = mEditor->WindowToViewportCoords({ (float)event.x, (float)event.y });
		auto camera = mEditor->GetComponent<CameraComponent>();

		Vec2 ViewportSize = mEditor->GetComponent<ViewportComponent>()->GetSize();

		Vec2 center = camera->GetCameraPos() + (MouseInViewportPos - ViewportSize / 2);

		if (IsInsideWorkspace(MouseInViewportPos))
		{
			for (auto& entity : mEditor->GetEngine()->GetCurrentScene()->GetEntityList())
			{
				TrySelectObject(center);
			}
		}
	}

	void SelectionHandlerComponent::OnKeyPressed(const KeyPressedEvent& event)
	{
		if (event.code == sf::Keyboard::LControl)
		{
			mIsCtrlButtonPressed = true;
		}
	}

	void SelectionHandlerComponent::OnKeyReleased(const KeyReleasedEvent& event)
	{
		if (event.code == sf::Keyboard::LControl)
		{
			mIsCtrlButtonPressed = false;

		}
	}

	void SelectionHandlerComponent::SelectObject(Entity* entity)
	{
		mSelectedObjects.emplace_back(entity);
	}

	bool SelectionHandlerComponent::IsInsideWorkspace(Vec2 translatedMousePos)
	{
		Vec2 viewSize = mEditor->ecs.GetComponent<ViewportComponent>()->GetSize();
		if (translatedMousePos.x >= 0 && translatedMousePos.x <= viewSize.x &&
			translatedMousePos.y >= 0 && translatedMousePos.y <= viewSize.y)
			return true;
		else
			return false;
	}

	void SelectionHandlerComponent::OnAnyEntityRemoved(const EntityRemovedEvent& event)
	{
		auto it = mSelectedObjects.begin();
		while (it != mSelectedObjects.end())
		{
			if (it->entity->GetUUID() == event.entity->GetUUID())
			{
				mSelectedObjects.erase(it);
				break;
			}
			it++;
		}
	}

	bool SelectionHandlerComponent::IsAlreadySelected(Entity* entity)
	{
		for (auto& selectedEntity : mSelectedObjects)
		{
			if (entity == selectedEntity.entity)
			{
				return true;
			}
		}
		return false;
	}

	::std::vector<SelectedObject>& SelectionHandlerComponent::GetSelectedObjectList()
	{
		return mSelectedObjects;
	}

	void SelectionHandlerComponent::ClearSelected()
	{
		mSelectedObjects.clear();
	}

	bool SelectionHandlerComponent::TrySelectObject(Vec2 mousePosition)
	{
		bool isEmptySpaceClicked = true;

		for (auto& entity : mEngine->GetCurrentScene()->GetEntityList())
		{
			auto graphicsComponent = entity.GetComponent<GraphicsComponent>();
			if (!graphicsComponent)
				continue;

			if (graphicsComponent->GetSprite().getGlobalBounds().contains({ mousePosition.x, mousePosition.y }))
			{
				//Entity selected
				isEmptySpaceClicked = false;

				if (!IsAlreadySelected(&entity))
				{
					if (mIsCtrlButtonPressed == true)
					{
						mSelectedObjects.emplace_back(&entity);
					}
					else
					{
						mSelectedObjects.clear();
						mSelectedObjects.emplace_back(&entity);
					}
					return true;
				}
			}
		}

		if (isEmptySpaceClicked)
		{
			mSelectedObjects.clear();
		}

		return false;
	}
}
