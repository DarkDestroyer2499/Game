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
		ImGui::Begin("Toolbar", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

		ImVec2 availableSpace = ImGui::GetContentRegionAvail();
		float buttonWidth = 40.0f;
		float spacing = (availableSpace.x - (2 * buttonWidth)) / 2.0f;
		float maxButtonHeight = availableSpace.y > 20.f ? 20.f : availableSpace.y;

		auto engine = mEditor->GetEngine();

		// Play button
		ImGui::SetCursorPosX(spacing);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.349f, 0.349f, 0.349f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.298f, 0.298f, 0.298f, 1.0f));
		if (ImGui::Button(!engine->GetCurrentSceneState() ? "Play" : "Stop", ImVec2(buttonWidth, maxButtonHeight)))
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

		//Pause button
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.349f, 0.349f, 0.349f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.298f, 0.298f, 0.298f, 1.0f));
		if (ImGui::Button("Pause", ImVec2(buttonWidth, maxButtonHeight)) && mScenePaused == false) {
			if (engine->GetCurrentSceneState())
			{
				mScenePaused = true;
				engine->SetCurrentSceneState(false);
			}
		}
		ImGui::PopStyleColor(3);

		ImGui::End();
	}
}