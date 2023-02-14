#ifndef MENU_BAR_H
#define MENU_BAR_H

#include "IUIComponent.hpp"
#include "../Editor.hpp"

class Editor;

class MenuBarComponent : public IUIComponent
{
public:
	MenuBarComponent(Editor*);
	~MenuBarComponent() = default;

	void Update() override;

private:
	friend class Editor;
	friend class Engine;
	Editor* mEditor;
};

#endif // !MENU_BAR_H
