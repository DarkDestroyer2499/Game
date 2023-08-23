#include "MenuBar.hpp"
#include "Core/Serializer.hpp"

namespace Oblivion
{
	MenuBarComponent::MenuBarComponent(Editor* editor) :
		mEditor{ editor }
	{
	}

	void MenuBarComponent::Update()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
				{
					std::unique_ptr<Scene> scene = std::make_unique<Scene>(mEditor->GetEngine());
					mEditor->GetEngine()->SetCurrentScene(std::move(scene));
				}

				if (ImGui::MenuItem("Open...", "Ctrl+O"))
				{
					Engine* engine = mEditor->GetEngine();
					auto* component = mEditor->ecs.GetComponent<FileExplorerComponent>();
					std::string scenePath = component->OpenFile("Oblivion Scene (*.yaml)\0*.yaml\0");

					if (scenePath != "")
					{
						Serializer serializer(engine);
						std::unique_ptr<Scene> scene = std::make_unique<Scene>(mEditor->GetEngine());
						serializer.Deserialize(*scene.get(), scenePath);
						mEditor->ecs.GetComponent<SelectionHandlerComponent>()->ClearSelected();
						engine->SetCurrentScene(std::move(scene));
					}
				}

				if (ImGui::MenuItem("Save as...", "Ctrl+Shift+S"))
				{
					Engine* engine = mEditor->GetEngine();
					auto* component = mEditor->ecs.GetComponent<FileExplorerComponent>();
					std::string scenePath = component->SaveFile("Oblivion Scene (*.yaml)\0*.yaml\0");

					Log(INFO, scenePath);

					if (scenePath != "")
					{
						Serializer serializer(engine);
						serializer.Serialize(*engine->GetCurrentScene(), scenePath);
					}
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Exit")) 
				{
					mEditor->GetMainWindow().close();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				if (ImGui::MenuItem("Redo", "CTRL+Y")) {}
				ImGui::Separator();
				if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				if (ImGui::MenuItem("Paste", "CTRL+V")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Help"))
			{
				if (ImGui::MenuItem("About")) {}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}
}
