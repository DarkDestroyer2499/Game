#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "IEditorComponent.hpp"
#include "Editor/Editor.hpp"

namespace Oblivion
{
	class ViewportComponent : public IEditorComponent
	{
	public:
		ViewportComponent(Editor*);
		~ViewportComponent() = default;

		Vec2 GetPosition();
		Vec2 GetSize();
		void Update() override;		

	private:
		Editor* mEditor;
		Vec2 mPosition, mSize;
	};
}
#endif // !VIEWPORT_H
