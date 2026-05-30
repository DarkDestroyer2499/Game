#include "Properties.hpp"
#include "Core/EntityComponents/ComponentLinker.hpp"
#include "Core/ComponentRegistry.hpp"

namespace Oblivion
{
	PropertiesComponent::PropertiesComponent(Editor* editor) :
		mEditor{ editor }
	{
	}

	void PropertiesComponent::Update()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12.f, 12.f));
		if (ImGui::Begin("Properties")) {

			auto* selectionComponent = mEditor->ecs.GetComponent<SelectionHandlerComponent>();

			if (selectionComponent->GetSelectedObjectList().size() == 0)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
				ImGui::SetCursorPosY(ImGui::GetWindowHeight() / 2.0f - 20.0f);
				ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("No Object Selected").x) / 2.0f);
				ImGui::Text("No Object Selected");
				ImGui::PopStyleColor();
				ImGui::End();
				ImGui::PopStyleVar();
				return;
			}

			ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(8.0f, 6.0f));
			if (!ImGui::BeginTable("PropertiesComponentList", 1, ImGuiTableFlags_BordersInnerV))
			{
				ImGui::PopStyleVar();
				ImGui::End();
				ImGui::PopStyleVar();
				return;
			}

			static ImGuiTreeNodeFlags TreeNodeFlags = ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen;

			ImGui::TableNextRow();
			ImGui::TableNextColumn();

			for (auto &selectedObject : selectionComponent->GetSelectedObjectList())
			{
				for (auto& component : selectedObject.entity->GetComponentList())
				{
					const ComponentDescriptor* desc = GetComponentRegistry().FindByType(component->GetTypeID());
					if (desc && desc->drawInspector)
					{
						desc->drawInspector(component, *mEditor);
						continue;
					}

					//TODO: Add more components features to UI
				}

					ImGui::PushID(selectedObject.entity);
					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					if (ImGui::Button("Add Component"))
						ImGui::OpenPopup("AddComponentPopup");

					if (ImGui::BeginPopup("AddComponentPopup"))
					{
						for (const ComponentDescriptor& descriptor : GetComponentRegistry().All())
						{
							if (!descriptor.create)
								continue;

							bool present = false;
							for (auto* existing : selectedObject.entity->GetComponentList())
							{
								if (existing->GetTypeID() == descriptor.typeID)
								{
									present = true;
									break;
								}
							}
							if (present)
								continue;

							if (ImGui::MenuItem(descriptor.name.c_str()))
								descriptor.create(*selectedObject.entity);
						}
						ImGui::EndPopup();
					}
					ImGui::PopID();
			}
			ImGui::EndTable();
			ImGui::PopStyleVar();
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}
}
