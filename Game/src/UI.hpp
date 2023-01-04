#ifndef UI_HPP
#define UI_HPP

#include "../lib/imgui/imgui.h"
#include "../lib/imgui/imgui-SFML.h"
#include "Editor.hpp"
#include "Util.hpp"
class UI
{
public:
	UI(Editor*);
	UI() = default;
	~UI();

	void Update();
	Vec2 GetViewportPosition();
	
private:
	void DrawMenuBar();
	void DrawViewport();
	void DrawHierarchy();
	void HierarchyTableViewDraw(Entity&);
private:
	Editor* mEditor;
	Vec2 mViewportPos;
	friend class Editor;
};

#endif // !UI_HPP
