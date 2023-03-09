#include "Properties.hpp"
#include "Core/Components/ComponentLinker.hpp"

namespace Oblivion
{
	PropertiesComponent::PropertiesComponent(Editor* editor) :
		mEditor{ editor }
	{
	}

	void PropertiesComponent::Update()
	{
		if (ImGui::Begin("Properties")) {

			auto* selectionComponent = mEditor->ecs.GetComponent<SelectionHandlerComponent>();
			
			if (selectionComponent->GetSelectedObjectList().size() == 0)
			{
				ImGui::End();
				return;
			}

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
			if (!ImGui::BeginTable("PropertiesComponentList", 1))
			{
				return;
			}

			ImGuiTreeNodeFlags TreeNodeFlags = ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_Framed;

			for (auto& selectedObject : selectionComponent->GetSelectedObjectList())
			{
				for (auto& component : selectedObject.entity.ecs.GetComponentList())
				{
					if (dynamic_cast<TagComponent*>(component) != nullptr)
					{
						ImGui::TableNextRow();
						ImGui::TableNextColumn();
						auto tmp = dynamic_cast<TagComponent*>(component);

						bool open = ImGui::TreeNodeEx((::std::string(tmp->GetName()) + ::std::string(" component")).c_str(), TreeNodeFlags);

						if (open)
						{
							char str0[50];
							strcpy_s(str0, tmp->GetTag().c_str());
							ImGui::AlignTextToFramePadding();
							ImGui::Text("Name: ");
							ImGui::SameLine();
							if (ImGui::InputText("##Name", str0, IM_ARRAYSIZE(str0)))
							{
								//TODO: add some length checks
								tmp->SetTag(str0);
							}
							ImGui::TreePop();
						}
						//ImGui::Separator();
					}
					else if (dynamic_cast<TransformComponent*>(component) != nullptr)
					{
						ImGui::TableNextRow();
						ImGui::TableNextColumn();
						auto tmp = dynamic_cast<TransformComponent*>(component);
						bool open = ImGui::TreeNodeEx((::std::string(tmp->GetName()) + ::std::string(" component")).c_str(), TreeNodeFlags);

						if (open)
						{
							Vec2 pos = tmp->GetPosition();
							float position[2]{ pos.x, pos.y };
							ImGui::AlignTextToFramePadding();
							ImGui::Text("Position: ");

							ImGui::SameLine();

							ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
							ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(255, 0, 0, 255.0f));
							ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(255, 0, 0, 0.9f));
							ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(255, 0, 0, 1.f));
							if (ImGui::Button("X"))
							{
								position[0] = 0.f;
							}
							ImGui::PopStyleColor(3);
							ImGui::SameLine();
							ImGui::PushItemWidth(50);
							ImGui::DragFloat("##Position DraggerX", &position[0], 1.f, 0, 0, "%.2f");;
							ImGui::PopItemWidth();
							ImGui::PopStyleVar();
							ImGui::SameLine();

							ImGui::NextColumn();

							ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
							ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 100, 0, 0.7f));
							ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 100, 0, 0.9f));
							ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 100, 0, 1.f));
							if (ImGui::Button("Y"))
							{
								position[1] = 0.f;
							}
							ImGui::PopStyleColor(3);
							ImGui::SameLine();
							ImGui::PushItemWidth(50);
							ImGui::DragFloat("##Position DraggerY", &position[1], 1.f, 0, 0, "%.2f");
							ImGui::PopItemWidth();
							ImGui::PopStyleVar();


							//Rotation
							float rotation = tmp->GetRotation() * DEG_IN_RAD;

							ImGui::Text("Rotation: ");
							ImGui::SameLine();
							ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
							ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 255, 255.0f));
							ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 255, 0.9f));
							ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 255, 1.f));
							if (ImGui::Button("R"))
							{
								rotation = 0.f;
							}
							ImGui::PopStyleColor(3);
							ImGui::SameLine();
							ImGui::PushItemWidth(50);
							ImGui::DragFloat("##Rotation DraggerX", &rotation, 1.0f, 0.f, 360.f, "%.0f");
							ImGui::PopItemWidth();
							ImGui::PopStyleVar();
							ImGui::SameLine();



							tmp->SetRotation(rotation / DEG_IN_RAD);
							tmp->SetPosition({ position[0], position[1] });
							ImGui::TreePop();
						}
					}
					else if (dynamic_cast<GraphicsComponent*>(component) != nullptr)
					{
						ImGui::TableNextRow();
						ImGui::TableNextColumn();
						auto tmp = dynamic_cast<GraphicsComponent*>(component);
						bool open = ImGui::TreeNodeEx((::std::string(tmp->GetName()) + ::std::string(" component")).c_str(), TreeNodeFlags);

						if (open)
						{
							static Vec2 SpriteIconSize{ 90.f, 90.f };
							sf::Sprite tmpSprite = tmp->GetSprite();
							tmpSprite.setRotation(0);
							::std::string spriteSizeText("Size: " + ::std::to_string(tmpSprite.getTextureRect().width) + ::std::string(" : ") + ::std::to_string(tmpSprite.getTextureRect().height));
							ImGui::Text(spriteSizeText.c_str());
							tmpSprite.setScale({ SpriteIconSize.x / tmpSprite.getTextureRect().width, SpriteIconSize.y / tmpSprite.getTextureRect().height });
							ImGui::Image(tmpSprite);
							ImGui::SameLine();

							if (ImGui::Button("Edit sprite parameters"))
							{
								ImGui::OpenPopup("Sprite settings window");
							}

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
		}
		ImGui::PopStyleVar();
		ImGui::End();
	}
}
