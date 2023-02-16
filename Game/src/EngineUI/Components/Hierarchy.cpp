#ifndef UI_HIERARCHY_HPP
#define UI_HIERARCHY_HPP

#include "Hierarchy.hpp"

HierarchyComponent::HierarchyComponent(Editor* editor):
	mEditor{ editor }
{
}

void HierarchyComponent::Update()
{
	if (ImGui::Begin("Hierarchy1"))
	{
		ImGui::Text("Render time: %ius", mEditor->mEngine.GetRenderTime());
		static ImGuiTableFlags flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
		if (ImGui::BeginTable("EntityList", 1, flags))
		{
			for (auto& entity : mEditor->mEngine.GetEntityList())
			{
				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				bool open = ImGui::TreeNodeEx(entity.GetComponent<TagComponent>()->GetTag().c_str(), ImGuiTreeNodeFlags_SpanFullWidth);

				if (open)
				{
					for (auto Component : entity.mComponentList)
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

#endif // !UI_HIERARCHY_HPP
