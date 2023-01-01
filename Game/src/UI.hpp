#ifndef UI_HPP
#define UI_HPP

#include "../lib/imgui/imgui.h"
#include "../lib/imgui/imgui-SFML.h"
#include "Editor.hpp"

class UI
{
public:
	UI(Editor*);
	UI() = default;
	~UI();

	void Update();

private:
	void DrawMenuBar();
	void DrawViewport();

private:
	Editor* mEditor;
};

#endif // !UI_HPP
