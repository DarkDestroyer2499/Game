#ifndef HIERARCHY_H
#define HIERARCHY_H

#include "IUIComponent.hpp"
#include "../Editor.hpp"

class Editor;

class HierarchyComponent : public IUIComponent
{
public:
	HierarchyComponent(Editor*);
	~HierarchyComponent() = default;

	void Update() override;

private:
	friend class Editor;
	friend class Engine;
	Editor* mEditor;
};

#endif // !HIERARCHY_H
