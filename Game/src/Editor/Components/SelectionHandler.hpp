#ifndef SELECTION_HANDLER_HPP
#define SELECTION_HANDLER_HPP

#include "IEditorComponent.hpp"
#include "Editor/Editor.hpp"

namespace Oblivion
{
	struct SelectedObject
	{
		Entity& entity;
		UIVisualSelector selector;
		SelectedObject() = default;
		SelectedObject(Entity& entity, UIVisualSelector selector)
			:entity{ entity }, selector{ selector }
		{
		}
		SelectedObject(Entity& entity)
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
		bool IsAlreadySelected(Entity& entity);
		::std::vector<SelectedObject>& GetSelectedObjectList();
		void ClearSelected();
		void SelectObject(Entity&);
		bool IsInsideWorkspace(Vec2);
	private:
		::std::vector<SelectedObject> mSelectedObjects;
		Editor* mEditor;
		Engine* mEngine;
	};
}
#endif // !SELECTION_HANDLER_HPP
