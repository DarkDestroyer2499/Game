#ifndef PATH_H
#define PATH_H

#include <filesystem>

namespace Oblivion
{
	static const std::filesystem::path ROOT_FOLDER_PATH{ "Assets" };

	static const std::filesystem::path TEMP_FOLDER_PATH{ ROOT_FOLDER_PATH / "Temp" };

	static const std::filesystem::path TEMP_SCENE_FOLDER_PATH{ TEMP_FOLDER_PATH / "Scene" };
}

#endif//!PATH_H
