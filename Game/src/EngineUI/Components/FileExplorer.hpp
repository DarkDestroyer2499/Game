#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

#include <filesystem>
#include "IUIComponent.hpp"
#include "../Editor.hpp"

class FileExplorerComponent : public IUIComponent
{
public:
	FileExplorerComponent(Editor*);
	~FileExplorerComponent() = default;

	Vec2 GetPosition();

	void Update() override;

private:

	void BuildFolderTree(std::string path);
	inline ImGuiTreeNodeFlags_ IsNeedToPreopenTree(std::filesystem::path path);

private:
	Editor* mEditor;
	Vec2 mPosition, mSize;
	std::filesystem::path mSelectedFolderPath;

	friend class Editor;
	friend class Engine;
};

#endif // !FILE_EXPLORER_H
