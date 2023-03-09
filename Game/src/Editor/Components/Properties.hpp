#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "IEditorComponent.hpp"
#include "Editor/Editor.hpp"

namespace Oblivion
{
	class PropertiesComponent : public IEditorComponent
	{
	public:
		PropertiesComponent(Editor*);
		~PropertiesComponent() = default;

		void Update() override;
	private:
		Editor* mEditor;
		Vec2 mPosition, mSize;
	};
}
#endif // !PROPERTIES_H
