#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

#include <filesystem>
#include "IEditorComponent.hpp"
#include "Editor/Editor.hpp"

namespace Oblivion
{
	class FileExplorerComponent : public IEditorComponent
	{
	public:
		FileExplorerComponent(Editor*);
		~FileExplorerComponent() = default;

		Vec2 GetPosition();
		void Update() override;
	private:
		void BuildFolderTree(::std::string path);
		inline ImGuiTreeNodeFlags_ IsNeedToPreopenTree(::std::filesystem::path path);
	private:
		Editor* mEditor;
		Vec2 mPosition, mSize;
		::std::filesystem::path mSelectedFolderPath;
	};
}

#endif // !FILE_EXPLORER_H
