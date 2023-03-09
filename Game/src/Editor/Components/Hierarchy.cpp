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
			static ImGuiTableFlags flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
			if (ImGui::BeginTable("EntityList", 1, flags))
			{
				for (auto& entity : mEditor->GetEngine()->GetEntityList())
				{
					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					bool open = ImGui::TreeNodeEx(entity.ecs.GetComponent<TagComponent>()->GetTag().c_str(),(IsNeedToSelect(entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_OpenOnArrow);

					//TODO: select multiple objects
					if (ImGui::IsItemClicked())
					{
						auto* component = mEditor->ecs.GetComponent<SelectionHandlerComponent>();
						if (!component->IsAlreadySelected(entity))
						{
							component->ClearSelected();
							component->SelectObject(entity);
						}
					}

					if (open)
					{
						for (auto Component : entity.ecs.GetComponentList())
						{
							ImGui::TreeNodeEx(Component->GetName(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth);
						}
						ImGui::TreePop();
					}
				}
				ImGui::EndTable();
			}
			ImGui::PopStyleVar();
			ImGui::End();
		}
	}

	bool HierarchyComponent::IsNeedToSelect(Entity& entity)
	{
		auto component = mEditor->ecs.GetComponent<SelectionHandlerComponent>();
		for (auto&[ent, selector] : component->GetSelectedObjectList())
		{
			if (ent.ecs.GetComponent<IDComponent>()->GetUUID() == entity.ecs.GetComponent<IDComponent>()->GetUUID())
			{
				return true;
			}
		}		
		return false;
	}
}
