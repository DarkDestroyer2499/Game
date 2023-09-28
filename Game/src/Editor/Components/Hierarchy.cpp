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
			ImGui::Text("Render time: %ius", mEditor->GetEngine()->GetRenderTime());
			ImGui::Text("Entity count: %i", mEditor->GetEngine()->GetCurrentScene()->GetEntityList().size());
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
						if (ImGui::Selectable("Clone"))
						{
							mEditor->GetEngine()->CloneObject(&(*entity));
							ImGui::CloseCurrentPopup();
							ImGui::EndPopup();
							continue;
						}

						if (ImGui::Selectable("Remove"))
						{
							mEditor->GetEngine()->RemoveObject(&(*entity++));
							ImGui::CloseCurrentPopup();
							ImGui::EndPopup();
							if (open)
							{
								ImGui::TreePop();
							}
							continue;
						}

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
