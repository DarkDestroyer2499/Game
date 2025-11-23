#include <Core/Serializer.hpp>
#include <Core/Path.h>
#include <Windows.h>
#include "Toolbar.hpp"

namespace Oblivion
{
	ToolbarComponent::ToolbarComponent(Editor* editor) :
		mEditor{ editor }, mScenePaused{ false }
	{
		if (!std::filesystem::is_directory(TEMP_FOLDER_PATH) || !std::filesystem::exists(TEMP_FOLDER_PATH)) {
			std::filesystem::create_directory(TEMP_FOLDER_PATH);
		}
		if (!std::filesystem::is_directory(TEMP_SCENE_FOLDER_PATH) || !std::filesystem::exists(TEMP_SCENE_FOLDER_PATH)) {
			std::filesystem::create_directory(TEMP_SCENE_FOLDER_PATH);
		}
	}

	void ToolbarComponent::Update()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 8.0f));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.12f, 0.12f, 0.13f, 1.00f));
		ImGui::Begin("Toolbar", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

		ImVec2 availableSpace = ImGui::GetContentRegionAvail();
		float buttonWidth = 60.0f;
		float buttonHeight = 30.0f;
		float spacing = (availableSpace.x - (2 * buttonWidth) - 8.0f) / 2.0f;

		auto engine = mEditor->GetEngine();
		bool isPlaying = engine->GetCurrentSceneState();

		// Center the buttons
		ImGui::SetCursorPosX(spacing);
		ImGui::SetCursorPosY((availableSpace.y - buttonHeight) / 2.0f + 8.0f);

		// Play/Stop button
		if (isPlaying)
		{
			// Stop button (red theme)
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.2f, 0.2f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.3f, 0.3f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.4f, 0.4f, 1.0f));
		}
		else
		{
			// Play button (green theme)
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.6f, 0.2f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.7f, 0.3f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 0.8f, 0.4f, 1.0f));
		}

		if (ImGui::Button(!isPlaying ? "Play" : "Stop", ImVec2(buttonWidth, buttonHeight)))
		{
			Serializer serializer(engine);
			if (!engine->GetCurrentSceneState())
			{
				//On Play
				if (mScenePaused)
					mScenePaused = false;
				else
				{
					mBufferedSceneName = std::filesystem::absolute(TEMP_SCENE_FOLDER_PATH / engine->GetCurrentScene()->GetName());
					serializer.Serialize(*engine->GetCurrentScene(), mBufferedSceneName);
				}
			}
			else
			{
				//On Stop
				std::unique_ptr<Scene> scene = std::make_unique<Scene>(mEditor->GetEngine());
				serializer.Deserialize(*scene.get(), mBufferedSceneName.string() + ".yaml");
				mEditor->ecs.GetComponent<SelectionHandlerComponent>()->ClearSelected();
				engine->SetCurrentScene(std::move(scene));
			}
			engine->SetCurrentSceneState(!engine->GetCurrentSceneState());
		}
		ImGui::PopStyleColor(3);

		// Pause button
		ImGui::SameLine();
		bool isPauseEnabled = engine->GetCurrentSceneState();

		if (!isPauseEnabled)
		{
			// Disabled state
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.15f, 0.15f, 0.16f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.15f, 0.15f, 0.16f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.15f, 0.15f, 0.16f, 1.0f));
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
		}
		else
		{
			// Active state (blue theme)
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.26f, 0.59f, 0.98f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.26f, 0.59f, 0.98f, 0.8f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.26f, 0.59f, 0.98f, 1.0f));
		}

		if (ImGui::Button("Pause", ImVec2(buttonWidth, buttonHeight)) && isPauseEnabled && !mScenePaused)
		{
			mScenePaused = true;
			engine->SetCurrentSceneState(false);
		}

		if (!isPauseEnabled)
			ImGui::PopStyleColor(4);
		else
			ImGui::PopStyleColor(3);

		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
	}
}