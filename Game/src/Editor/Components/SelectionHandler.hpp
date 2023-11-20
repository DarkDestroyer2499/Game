#ifndef SELECTION_HANDLER_HPP
#define SELECTION_HANDLER_HPP

#include "IEditorComponent.hpp"
#include "Editor/Editor.hpp"

namespace Oblivion
{
	struct SelectedObject
	{
		Entity* entity;
		UIVisualSelector selector;
		SelectedObject() = default;
		SelectedObject(const SelectedObject& other)
			: entity{ other.entity }, selector{ UIVisualSelector() }
		{

		}
		SelectedObject(Entity* entity)
			:entity{ entity }, selector{ UIVisualSelector() }
		{
		}
	};


	class SelectionHandlerComponent : public IEditorComponent
	{
	public:
		SelectionHandlerComponent(Editor*, Engine*);
		~SelectionHandlerComponent() = default;

		void Update() override;
		bool TrySelectObject(Vec2);
		bool IsAlreadySelected(Entity* entity);
		::std::vector<SelectedObject>& GetSelectedObjectList();
		void ClearSelected();
		void SelectObject(Entity*);
		bool IsInsideWorkspace(Vec2);

	private:
		//Events
		void OnAnyEntityRemoved(Entity*) override;
		void OnMouseButtonPressed(const sf::Event&) override;
		void OnKeyPressed(const sf::Event&) override;
		void OnKeyReleased(const sf::Event&) override;
	private:
		::std::vector<SelectedObject> mSelectedObjects;
		Editor* mEditor;
		Engine* mEngine;
		bool mIsCtrlButtonPressed;
	};
}
#endif // !SELECTION_HANDLER_HPP
