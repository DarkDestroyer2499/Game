#include "SelectionHandler.hpp"

namespace Oblivion
{
	SelectionHandlerComponent::SelectionHandlerComponent(Editor* editor, Engine* engine)
		: mEditor{editor}, mEngine{engine}
	{
		mEditor->GetEngine()->eventBroadcaster.Attach(EventType::OnAnyEntityRemoved, this);
	}

	void SelectionHandlerComponent::Update()
	{
		for (auto&[entity, selector] : mSelectedObjects)
		{
			selector.Update(entity);
			selector.Draw(mEngine->GetRenderWindow());
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

	void SelectionHandlerComponent::OnAnyEntityRemoved(Entity* remEntity)
	{
		auto it = mSelectedObjects.begin();
		while(it != mSelectedObjects.end())
		{
			if (it->entity->GetUUID() == remEntity->GetUUID())
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

			if (graphicsComponent->GetSprite().getGlobalBounds().contains({ mousePosition.x, mousePosition.y}))
			{
				//Entity selected
				isEmptySpaceClicked = false;

				if (!IsAlreadySelected(&entity))
				{
					mSelectedObjects.clear();
					mSelectedObjects.emplace_back(&entity);
					return true;
				}
				else
				{
					Log(INFO, "Already selected!");
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
