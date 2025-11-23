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
		COMPONENT_TYPE_IMPL(FileExplorerComponent)

		FileExplorerComponent(Editor*);
		~FileExplorerComponent() = default;

		std::string OpenFile(const char*);
		std::string SaveFile(const char*);

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
