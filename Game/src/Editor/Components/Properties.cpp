#include "Properties.hpp"
#include "Core/EntityComponents/ComponentLinker.hpp"

namespace Oblivion
{
	PropertiesComponent::PropertiesComponent(Editor* editor) :
		mEditor{ editor }
	{
		mEditor->GetEngine()->eventBroadcaster.Attach(EventType::OnAnyEntityRemoved, this);
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
				{//Render TransformComponent
					ImGui::TableNextRow();
					ImGui::TableNextColumn();

					auto transform = selectedObject.entity->transform.get();

					bool open = ImGui::TreeNodeEx((::std::string(transform->GetName()) + ::std::string(" component")).c_str(), TreeNodeFlags);

					if (open)
					{
						ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.f, 4.f));
						ImGui::Spacing();

						// Position
						Vec2 pos = transform->GetPosition();
						float position[2]{ pos.x, pos.y };

						ImGui::Columns(2, nullptr, false);
						ImGui::SetColumnWidth(0, 80.f);
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Position");
						ImGui::NextColumn();

						// X component
						ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2.f, 4.f));
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
						if (ImGui::Button("X", ImVec2(20.f, 0.f)))
						{
							position[0] = 0.f;
						}
						ImGui::PopStyleColor(3);
						ImGui::SameLine();
						ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.5f - 2.f);
						ImGui::DragFloat("##PositionX", &position[0], 0.1f, 0.f, 0.f, "%.2f");
						ImGui::SameLine();

						// Y component
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 0.9f, 0.4f, 1.0f));
						if (ImGui::Button("Y", ImVec2(20.f, 0.f)))
						{
							position[1] = 0.f;
						}
						ImGui::PopStyleColor(3);
						ImGui::SameLine();
						ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
						ImGui::DragFloat("##PositionY", &position[1], 0.1f, 0.f, 0.f, "%.2f");
						ImGui::PopStyleVar();

						ImGui::Columns(1);
						ImGui::Spacing();

						// Rotation
						float rotation = transform->GetRotation() * DEG_IN_RAD;

						ImGui::Columns(2, nullptr, false);
						ImGui::SetColumnWidth(0, 80.f);
						ImGui::AlignTextToFramePadding();
						ImGui::Text("Rotation");
						ImGui::NextColumn();

						ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2.f, 4.f));
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.4f, 0.8f, 1.0f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.5f, 0.9f, 1.0f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.6f, 1.0f, 1.0f));
						if (ImGui::Button("R", ImVec2(20.f, 0.f)))
						{
							rotation = 0.f;
						}
						ImGui::PopStyleColor(3);
						ImGui::SameLine();
						ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
						ImGui::DragFloat("##Rotation", &rotation, 0.5f, 0.f, 360.f, "%.1f°");
						ImGui::PopStyleVar();

						ImGui::Columns(1);
						ImGui::Spacing();
						ImGui::PopStyleVar();

						transform->SetRotation(rotation / DEG_IN_RAD);
						transform->SetPosition({ position[0], position[1] });
						ImGui::TreePop();
					}
				}
				for (auto& component : selectedObject.entity->GetComponentList())
				{
					if (dynamic_cast<TagComponent*>(component) != nullptr)
					{
						ImGui::TableNextRow();
						ImGui::TableNextColumn();
						auto tmp = dynamic_cast<TagComponent*>(component);

						bool open = ImGui::TreeNodeEx((::std::string(tmp->GetName()) + ::std::string(" Component")).c_str(), TreeNodeFlags);

						if (open)
						{
							ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.f, 6.f));
							ImGui::Spacing();

							char str0[50];
							strcpy_s(str0, tmp->GetTag().c_str());

							ImGui::Columns(2, nullptr, false);
							ImGui::SetColumnWidth(0, 80.f);
							ImGui::AlignTextToFramePadding();
							ImGui::Text("Name");
							ImGui::NextColumn();

							ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
							if (ImGui::InputText("##Name", str0, IM_ARRAYSIZE(str0)))
							{
								//TODO: add some length checks
								tmp->SetTag(str0);
							}
							ImGui::Columns(1);

							ImGui::Spacing();
							ImGui::PopStyleVar();
							ImGui::TreePop();
						}
					}
					else if (dynamic_cast<GraphicsComponent*>(component) != nullptr)
					{
						ImGui::TableNextRow();
						ImGui::TableNextColumn();
						auto tmp = dynamic_cast<GraphicsComponent*>(component);
						bool open = ImGui::TreeNodeEx((::std::string(tmp->GetName()) + ::std::string(" Component")).c_str(), TreeNodeFlags);

						if (open)
						{
							ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.f, 6.f));
							ImGui::Spacing();

							static Vec2 SpriteIconSize{ 100.f, 100.f };
							sf::Sprite tmpSprite = tmp->GetSprite();
							tmpSprite.setRotation(0);

							// Sprite preview section
							ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.14f, 0.14f, 0.15f, 1.00f));
							ImGui::BeginChild("SpritePreview", ImVec2(0, 140), true);

							ImGui::SetCursorPosX((ImGui::GetContentRegionAvail().x - SpriteIconSize.x) / 2.0f + 8.0f);
							ImGui::SetCursorPosY(8.0f);

							tmpSprite.setScale({ SpriteIconSize.x / tmpSprite.getTextureRect().width, SpriteIconSize.y / tmpSprite.getTextureRect().height });
							ImGui::Image(tmpSprite);

							ImGui::EndChild();
							ImGui::PopStyleColor();

							ImGui::Spacing();

							// Sprite info
							::std::string spriteSizeText = ::std::to_string(tmpSprite.getTextureRect().width) + " x " + ::std::to_string(tmpSprite.getTextureRect().height);
							ImGui::Text("Texture Size:");
							ImGui::SameLine(120);
							ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.26f, 0.59f, 0.98f, 1.0f));
							ImGui::Text("%s", spriteSizeText.c_str());
							ImGui::PopStyleColor();

							ImGui::Spacing();
							ImGui::PopStyleVar();
							ImGui::TreePop();
						}
					}
					else if (false)
					{
						//Template for other components
						ImGui::TableNextRow();
						ImGui::TableNextColumn();
						auto tmp = dynamic_cast<GraphicsComponent*>(component);
						bool open = ImGui::TreeNodeEx((::std::string(tmp->GetName()) + ::std::string(" component")).c_str(), TreeNodeFlags);

						if (open)
						{

							ImGui::TreePop();
						}

					}
					//TODO: Add more components features to UI
				}
			}
			ImGui::EndTable();
			ImGui::PopStyleVar();
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}
}
