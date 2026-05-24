#include <span>
#include <string_view>

#include "Core/Engine.hpp" 
#include "Editor/Editor.hpp"

int main(int argc, char** argv)
{
	auto args = std::span(argv, argc).subspan(1);

	bool isEditorMode = std::ranges::any_of(args, 
		[](std::string_view s) 
		{
			return s == "--editor" || s == "-e"; 
		}
	);

	isEditorMode = true;

	if (isEditorMode)
	{
		Oblivion::Editor editor;
		editor.Run();
	}
	else
	{
		Oblivion::Engine engine;
		engine.RunStandalone();
	}

	return 0;
}
