#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "IEditorComponent.hpp"
#include "Editor/Editor.hpp"
#include "Core/EventSystem/EventBroadcaster.hpp"

namespace Oblivion
{
	class PropertiesComponent : public IEditorComponent
	{
	public:
		COMPONENT_TYPE_IMPL(PropertiesComponent)
		PropertiesComponent(Editor*);
		~PropertiesComponent() = default;

		void Update() override;
	private:
		Editor* mEditor;
		Vec2 mPosition, mSize;
	};
}
#endif // !PROPERTIES_H
