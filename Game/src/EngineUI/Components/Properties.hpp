#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "IUIComponent.hpp"
#include "../Editor.hpp"

class PropertiesComponent : public IUIComponent
{
public:
	PropertiesComponent(Editor*);
	~PropertiesComponent() = default;

	void Update() override;

private:
	Editor* mEditor;
	Vec2 mPosition, mSize;

	friend class Editor;
	friend class Engine;
};

#endif // !PROPERTIES_H
