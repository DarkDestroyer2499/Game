#ifndef MENU_BAR_H
#define MENU_BAR_H

#include "IEditorComponent.hpp"
#include "Editor/Editor.hpp"

namespace Oblivion
{
	class MenuBarComponent : public IEditorComponent
	{
	public:
		MenuBarComponent(Editor*);
		~MenuBarComponent() = default;

		void Update() override;

	private:
		Editor* mEditor;
	};
}
#endif // !MENU_BAR_H
