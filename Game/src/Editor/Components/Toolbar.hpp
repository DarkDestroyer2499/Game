#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "IEditorComponent.hpp"
#include "Editor/Editor.hpp"

namespace Oblivion
{
	class ToolbarComponent : public IEditorComponent
	{
	public:
		COMPONENT_TYPE_IMPL(ToolbarComponent)
		ToolbarComponent(Editor*);
		~ToolbarComponent() = default;

		void Update() override;

	private:
		Editor* mEditor;
		std::filesystem::path mBufferedSceneName;
		bool mScenePaused;
	};
}
#endif // !TOOLBAR_H
