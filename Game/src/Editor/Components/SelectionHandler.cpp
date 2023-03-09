#include "SelectionHandler.hpp"

namespace Oblivion
{
	SelectionHandlerComponent::SelectionHandlerComponent(Editor* editor, Engine* engine)
		: mEditor{editor}, mEngine{engine}
	{
	}

	void SelectionHandlerComponent::Update()
	{
		sf::RenderTarget* renderWindow = mEngine->GetRenderWindow();

		for (auto&[entity, selector] : mSelectedObjects)
		{
			selector.Update(&entity);
			selector.Draw(renderWindow);
		}
	}

	void SelectionHandlerComponent::SelectObject(Entity& entity)
	{
		mSelectedObjects.emplace_back(entity, UIVisualSelector());
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


	bool SelectionHandlerComponent::IsAlreadySelected(Entity& entity)
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

		for (auto& entity : mEngine->GetEntityList())
		{
			auto graphicsComponent = entity.ecs.GetComponent<GraphicsComponent>();
			if (!graphicsComponent)
				continue;

			if (graphicsComponent->GetSprite().getGlobalBounds().contains({ mousePosition.x, mousePosition.y}))
			{
				//Entity selected
				isEmptySpaceClicked = false;

				if (!IsAlreadySelected(entity))
				{
					mSelectedObjects.clear();
					mSelectedObjects.emplace_back(entity);
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
