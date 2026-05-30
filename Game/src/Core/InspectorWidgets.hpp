#ifndef INSPECTOR_WIDGETS_HPP
#define INSPECTOR_WIDGETS_HPP

#include <string>
#include "imgui.h"
#include "Util/Util.hpp"
#include "EntityComponents/IEntityComponent.hpp"

namespace Oblivion::Inspector
{
	inline constexpr float LabelColumnWidth = 90.0f;

	inline bool BeginComponent(IEntityComponent* component)
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen;
		std::string title = std::string(component->GetName()) + " Component";
		bool open = ImGui::TreeNodeEx(title.c_str(), flags);
		if (open)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.f, 6.f));
			ImGui::Spacing();
		}
		return open;
	}

	inline void EndComponent()
	{
		ImGui::Spacing();
		ImGui::PopStyleVar();
		ImGui::TreePop();
	}

	inline void BeginField(const char* label)
	{
		ImGui::Columns(2, nullptr, false);
		ImGui::SetColumnWidth(0, LabelColumnWidth);
		ImGui::AlignTextToFramePadding();
		ImGui::TextUnformatted(label);
		ImGui::NextColumn();
	}

	inline void EndField()
	{
		ImGui::Columns(1);
	}

	inline void ResetButtonColors(const ImVec4& base, const ImVec4& hovered, const ImVec4& active)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, base);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hovered);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, active);
	}

	inline bool DragVec2(const char* label, Vec2& value, float resetValue = 0.0f, float speed = 0.1f)
	{
		bool changed = false;
		ImGui::PushID(label);
		BeginField(label);

		float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };
		float fieldWidth = (ImGui::GetContentRegionAvail().x - buttonSize.x * 2.0f) * 0.5f - ImGui::GetStyle().ItemSpacing.x * 2.0f;

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2.f, 4.f));

		ResetButtonColors(ImVec4(0.8f, 0.1f, 0.15f, 1.0f), ImVec4(0.9f, 0.2f, 0.2f, 1.0f), ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
		if (ImGui::Button("X", buttonSize)) { value.x = resetValue; changed = true; }
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::SetNextItemWidth(fieldWidth);
		if (ImGui::DragFloat("##X", &value.x, speed, 0.f, 0.f, "%.2f")) changed = true;
		ImGui::SameLine();

		ResetButtonColors(ImVec4(0.2f, 0.7f, 0.2f, 1.0f), ImVec4(0.3f, 0.8f, 0.3f, 1.0f), ImVec4(0.4f, 0.9f, 0.4f, 1.0f));
		if (ImGui::Button("Y", buttonSize)) { value.y = resetValue; changed = true; }
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::SetNextItemWidth(fieldWidth);
		if (ImGui::DragFloat("##Y", &value.y, speed, 0.f, 0.f, "%.2f")) changed = true;

		ImGui::PopStyleVar();
		EndField();
		ImGui::PopID();
		return changed;
	}

	inline bool DragFloat(const char* label, float& value, float resetValue = 0.0f, float speed = 0.1f, const char* fmt = "%.2f")
	{
		bool changed = false;
		ImGui::PushID(label);
		BeginField(label);

		float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2.f, 4.f));
		ResetButtonColors(ImVec4(0.1f, 0.4f, 0.8f, 1.0f), ImVec4(0.2f, 0.5f, 0.9f, 1.0f), ImVec4(0.3f, 0.6f, 1.0f, 1.0f));
		if (ImGui::Button("R", buttonSize)) { value = resetValue; changed = true; }
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		if (ImGui::DragFloat("##v", &value, speed, 0.f, 0.f, fmt)) changed = true;
		ImGui::PopStyleVar();

		EndField();
		ImGui::PopID();
		return changed;
	}

	inline bool InputText(const char* label, char* buffer, size_t size)
	{
		ImGui::PushID(label);
		BeginField(label);
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		bool changed = ImGui::InputText("##input", buffer, size);
		EndField();
		ImGui::PopID();
		return changed;
	}

	inline void LabeledText(const char* label, const char* value)
	{
		BeginField(label);
		ImGui::AlignTextToFramePadding();
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.26f, 0.59f, 0.98f, 1.0f));
		ImGui::TextUnformatted(value);
		ImGui::PopStyleColor();
		EndField();
	}
}
#endif // !INSPECTOR_WIDGETS_HPP
