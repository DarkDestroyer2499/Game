#ifndef HIERARCHY_H
#define HIERARCHY_H

#include "IEditorComponent.hpp"
#include "Editor/Editor.hpp"

namespace Oblivion
{
	class HierarchyComponent : public IEditorComponent
	{
	public:
		HierarchyComponent(Editor*);
		~HierarchyComponent() = default;

		void Update() override;

	private:
		bool IsNeedToSelect(Entity&);

	private:
		Editor* mEditor;
	};
}
#endif // !HIERARCHY_H
