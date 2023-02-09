#include "UI.hpp"
#include <iostream>
#include "../Util/Log.hpp"

UI::UI(Editor* editor)
	: mEditor(editor)
{
}

UI::~UI()
{
}

void UI::Update()
{	
	DrawMenuBar();
	DrawViewport();	
	DrawSelected();
	ImGui::ShowDemoWindow();
	DrawHierarchy();
}

Vec2 UI::GetViewportPosition()
{
	return mViewportPos;
}

void UI::DrawMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New")) {}
			if (ImGui::MenuItem("Open")) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Exit")) {}
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

void UI::DrawViewport()
{
	
	ImGui::DockSpaceOverViewport();
	static ImVec2 viewportSize = ImGui::GetWindowSize();
	mEditor->mTexture->create(static_cast<unsigned int>(viewportSize.x),
		static_cast<unsigned int>(viewportSize.y));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));

	if (ImGui::Begin("Viewport")) {
		viewportSize = ImGui::GetWindowSize();
		mViewportPos = ImGui::GetWindowPos();
		ImGui::Image(*mEditor->mTexture);
	}
	
	ImGui::End();
	
	ImGui::PopStyleVar();
}

void HierarchyDrawComponents(const std::vector<IComponent*>& componentList)
{
	for (auto component : componentList)
	{

	}
}

void UI::HierarchyTableViewDraw(Entity& entity)
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

void UI::DrawSelected()
{
	for (int i = 0; i < mEditor->mSelectedObjects.size(); ++i)
	{
		mEditor->mSelectedObjects[i].selector.Update(&mEditor->mSelectedObjects[i].entity);
		mEditor->mSelectedObjects[i].selector.Draw(mEditor->mTexture);
	}
}

void UI::DrawHierarchy()
{
	
	if (ImGui::Begin("Hierarchy"))
	{
		ImGui::Text("Render time: %ius", mEditor->mEngine.GetRenderTime());
		static ImGuiTableFlags flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
		if (ImGui::BeginTable("EntityList", 1, flags))
		{
			for (auto& entity : mEditor->mEngine.mObjectList)
			{
				HierarchyTableViewDraw(entity);
			}
			
			ImGui::EndTable();
		}
		ImGui::PopStyleVar();
		ImGui::End();
	}
}
