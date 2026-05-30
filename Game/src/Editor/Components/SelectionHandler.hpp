#ifndef SELECTION_HANDLER_HPP
#define SELECTION_HANDLER_HPP

#include "IEditorComponent.hpp"
#include "Editor/Editor.hpp"
#include "../../Core/EventSystem/Events.hpp"

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
		COMPONENT_TYPE_IMPL(SelectionHandlerComponent)
		SelectionHandlerComponent(Editor*);
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
		void OnAnyEntityRemoved(const EntityRemovedEvent&);
		void OnMouseButtonPressed(const MouseButtonPressedEvent&);
		void OnKeyPressed(const KeyPressedEvent&);
		void OnKeyReleased(const KeyReleasedEvent&);
	private:
		::std::vector<SelectedObject> mSelectedObjects;
		Editor* mEditor;
		Engine* mEngine;
		bool mIsCtrlButtonPressed;

	private:
		Subscription mEntityRemovedEvent;
		Subscription mMouseButtonPressedEvent;
		Subscription mKeyPressedEvent;
		Subscription mKeyReleasedEvent;
	};
}
#endif // !SELECTION_HANDLER_HPP
