#include "Hierarchy.hpp"

namespace Oblivion
{
	HierarchyComponent::HierarchyComponent(Editor* editor) :
		mEditor{ editor }
	{
	}

	void HierarchyComponent::Update()
	{
		if (ImGui::Begin("Hierarchy"))
		{
			// Stats section with modern styling
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.14f, 0.14f, 0.15f, 1.00f));
			ImGui::BeginChild("HierarchyStats", ImVec2(0, 60), true, ImGuiWindowFlags_NoScrollbar);

			ImGui::Spacing();
			ImGui::Indent(8.0f);

			// Render time
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
			ImGui::Text("Render Time:");
			ImGui::PopStyleColor();
			ImGui::SameLine(120);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.26f, 0.59f, 0.98f, 1.0f));
			ImGui::Text("%ius", mEditor->GetEngine()->GetRenderTime());
			ImGui::PopStyleColor();

			// Entity count
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
			ImGui::Text("Entity Count:");
			ImGui::PopStyleColor();
			ImGui::SameLine(120);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.26f, 0.59f, 0.98f, 1.0f));
			ImGui::Text("%i", mEditor->GetEngine()->GetCurrentScene()->GetEntityList().size());
			ImGui::PopStyleColor();

			ImGui::Unindent(8.0f);
			ImGui::EndChild();
			ImGui::PopStyleColor();

			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();

			static ImGuiTableFlags flags = ImGuiTableFlags_Resizable
				| ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));

			if (ImGui::BeginTable("EntityList", 1, flags | ImGuiTableFlags_SizingStretchSame))
			{
				auto& entityList = mEditor->GetEngine()->GetCurrentScene()->GetEntityList();
				auto entity = entityList.begin();
				while (entity != entityList.end())
				{
					ImGui::TableNextRow();
					ImGui::TableNextColumn();

					std::string entityStringId = std::to_string(entity->GetUUID());

					bool open = ImGui::TreeNodeEx((entity->GetComponent<TagComponent>()->GetTag() + "##" + entityStringId).c_str(), (IsNeedToSelect(*entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_OpenOnArrow);

					if (ImGui::BeginPopupContextItem(std::string("##EntityPopup" + entityStringId).c_str()))
					{
						ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8.0f, 8.0f));

						if (ImGui::Selectable("Clone", false, 0, ImVec2(150, 0)))
						{
							mEditor->GetEngine()->CloneObject(&(*entity));
							ImGui::CloseCurrentPopup();
							ImGui::EndPopup();
							ImGui::PopStyleVar();
							continue;
						}

						ImGui::Separator();

						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));
						if (ImGui::Selectable("Remove", false, 0, ImVec2(150, 0)))
						{
							mEditor->GetEngine()->RemoveObject(&(*entity++));
							ImGui::CloseCurrentPopup();
							ImGui::EndPopup();
							ImGui::PopStyleColor();
							ImGui::PopStyleVar();
							if (open)
							{
								ImGui::TreePop();
							}
							continue;
						}
						ImGui::PopStyleColor();

						ImGui::PopStyleVar();
						ImGui::EndPopup();
					}

					//TODO: select multiple objects
					if (ImGui::IsItemClicked())
					{
						auto* component = mEditor->GetComponent<SelectionHandlerComponent>();
						if (!component->IsAlreadySelected(&(*entity)))
						{
							component->ClearSelected();
							component->SelectObject(&(*entity));
						}
					}

					if (open)
					{
						for (auto Component : entity->GetComponentList())
						{
							ImGui::TreeNodeEx((std::string(Component->GetName()) + "##" + entityStringId).c_str(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth);
							
						}
						ImGui::TreePop();
					}
					entity++;
				}
				ImGui::EndTable();				
			}
			ImGui::PopStyleVar();

			ImGui::End();
		}
		
	}

	bool HierarchyComponent::IsNeedToSelect(Entity& entity)
	{
		auto component = mEditor->GetComponent<SelectionHandlerComponent>();
		for (auto& [ent, selector] : component->GetSelectedObjectList())
		{
			if (ent->GetUUID() == entity.GetUUID())
			{
				return true;
			}
		}
		return false;
	}
}
