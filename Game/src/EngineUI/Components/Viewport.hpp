#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "IUIComponent.hpp"
#include "../Editor.hpp"

class ViewportComponent : public IUIComponent
{
public:
	ViewportComponent(Editor*);
	~ViewportComponent() = default;

	Vec2 GetPosition();

	void Update() override;

private:
	Editor* mEditor;
	Vec2 mPosition, mSize;

	friend class Editor;
	friend class Engine;
};

#endif // !VIEWPORT_H
