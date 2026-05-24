#ifndef HIERARCHY_H
#define HIERARCHY_H

#include "IEditorComponent.hpp"
#include "Editor/Editor.hpp"

#include "../../Core/EventSystem/EventBus.hpp"

namespace Oblivion
{
	class HierarchyComponent : public IEditorComponent
	{
	public:
		COMPONENT_TYPE_IMPL(HierarchyComponent)
		HierarchyComponent(Editor*);
		~HierarchyComponent() = default;

		void Update() override;

	private:
		bool IsNeedToSelect(Entity&);

	private:
		Editor* mEditor;
		Subscription mEntityCreatedSubscription;
		Subscription mEntityRemovedSubscription;

	};
}
#endif // !HIERARCHY_H
