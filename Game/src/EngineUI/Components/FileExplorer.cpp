#include "FileExplorer.hpp"
#include "../../resources/IconFontCppHeaders/IconsFontAwesome5Pro.h"

constexpr const char* ROOT_FOLDER_PATH{ "Assets" };

FileExplorerComponent::FileExplorerComponent(Editor* editor) :
	mEditor{ editor }, mSelectedFolderPath{ ROOT_FOLDER_PATH }
{
	namespace fs = std::filesystem;
	const fs::path sandbox{ ROOT_FOLDER_PATH };

	fs::file_status p{};

	if (fs::status_known(p) ? fs::exists(p) : fs::exists(sandbox))
	{
		Log(SUCCESS, "Assets folder exists!");
	}
	else
	{
		Log(WARNING, "Assets folder does not exist, and will be created! Path: " << std::filesystem::current_path().string() + "/" + ROOT_FOLDER_PATH);
		std::string path = std::filesystem::current_path().string() + "/" + ROOT_FOLDER_PATH;
		const fs::path assetFolderPath{ path };
		fs::create_directory(assetFolderPath);
	}
}

Vec2 FileExplorerComponent::GetPosition()
{
	return mPosition;
}

static ImGuiTreeNodeFlags sFolderFlags = ImGuiTreeNodeFlags_OpenOnArrow;

void FileExplorerComponent::BuildFolderTree(std::string path)
{
	if (std::filesystem::is_empty(path))
	{
		return;
	}

	for (auto& p : std::filesystem::directory_iterator(path))
	{
		if (p.is_directory())
		{
			bool open = ImGui::TreeNodeEx(p.path().filename().string().c_str(), ((mSelectedFolderPath.string() == p.path()) ? ImGuiTreeNodeFlags_Selected : 0) | sFolderFlags | IsNeedToPreopenTree(p.path()));

			if (ImGui::IsItemClicked())
			{
				mSelectedFolderPath = p.path();
			}

			if (open)
			{
				BuildFolderTree(p.path().string().c_str());
				ImGui::TreePop();
			}
		}
	}
}

ImGuiTreeNodeFlags_ FileExplorerComponent::IsNeedToPreopenTree(std::filesystem::path pathToCheck)
{
	std::filesystem::path tmp = mSelectedFolderPath;
	while(tmp.has_parent_path())
	{
		if (tmp.string() == pathToCheck)
			return ImGuiTreeNodeFlags_DefaultOpen;

		tmp = tmp.parent_path();
	}
	return ImGuiTreeNodeFlags_OpenOnArrow;
}

inline static const char* GetIcon(std::string fileType)
{
	if (fileType == ".txt")
	{
		return ICON_FA_FILE;
	}
	else if (fileType == ".mp3")
	{
		return ICON_FA_FILE_AUDIO;
	}
	else if (fileType == ".lua")
	{
		return ICON_FA_FILE_CODE;
	}
	else
	{
		return ICON_FA_FILE_ALT;
	}
}

void FileExplorerComponent::Update()
{
	if (ImGui::Begin("File structure"))
	{
		bool isOpened = ImGui::TreeNodeEx(ROOT_FOLDER_PATH, ((mSelectedFolderPath.string() == ROOT_FOLDER_PATH) ? ImGuiTreeNodeFlags_Selected : 0) | sFolderFlags  | IsNeedToPreopenTree(mSelectedFolderPath));

		if (ImGui::IsItemClicked())
		{
			mSelectedFolderPath = ROOT_FOLDER_PATH;
		}

		if (isOpened)
		{
			BuildFolderTree(ROOT_FOLDER_PATH);

			ImGui::TreePop();
		}
		ImGui::End();
	}

	//--- File exprorer ---
	if (!ImGui::Begin("File explorer"))
	{
		return;
	}

	ImGuiStyle& style = ImGui::GetStyle();
	static ImVec2 FileContainer(100, 100);

	ImGui::PushFont(mEditor->GetLoadedFonts()["ICON_FONT"]);

	ImGui::Text(mSelectedFolderPath.string().c_str());

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(255, 255, 255, 0.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(255, 255, 255, 0.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(255, 255, 255, 0.f));

	static float sPadding = 16.f;
	static float sDesiredCellSize = 90.f;
	float cellSize = sDesiredCellSize + sPadding;

	float panelWidth = ImGui::GetContentRegionAvail().x;
	int columnCount = (int)(panelWidth / cellSize);
	if (columnCount < 1)
		columnCount = 1;

	ImGui::Columns(columnCount, 0, false);
	ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.5f, 0.8f });


	for (auto& p : std::filesystem::directory_iterator(mSelectedFolderPath))
	{
		if (p.is_directory())
		{
			ImGui::Button(ICON_FA_FOLDER, { sDesiredCellSize, sDesiredCellSize });

			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
			{
				mSelectedFolderPath = p.path().string();
			}
		}
		else
		{
			ImGui::Button(GetIcon(p.path().filename().extension().string()), { sDesiredCellSize, sDesiredCellSize });
			if (ImGui::IsItemClicked())
			{
				// TODO: handle double click on file
			}
		}


		std::string fileName = p.path().filename().string();

		if (fileName.length() > 10)
			fileName = fileName.substr(0, 10) + "...";


		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + sDesiredCellSize / 2 - (ImGui::CalcTextSize(fileName.c_str()).x / 2) );
		if (ImGui::IsItemHovered())
		{
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 150));
			ImGui::Text(fileName.c_str());
			ImGui::PopStyleColor();
		}
		else
		{
			ImGui::Text(fileName.c_str());
		}

		ImGui::NextColumn();
	}

	ImGui::Columns(1);

	ImGui::PopStyleColor(3);
	ImGui::PopFont();
	ImGui::PopStyleVar();

	ImGui::End();
}
