#include "Properties.hpp"
#include "../../Components/ComponentLinker.hpp"

PropertiesComponent::PropertiesComponent(Editor* editor):
	mEditor{ editor }
{
}


void PropertiesComponent::Update()
{
	if (ImGui::Begin("Properties")) {
		
		if (mEditor->mSelectedObjects.size() == 0)
		{
			ImGui::End();
			return;
		}
		// search for components in first selected entity
		for (auto& component : mEditor->mSelectedObjects[0].entity.mComponentList)
		{
			if (dynamic_cast<TagComponent*>(component) != nullptr)
			{
				auto tmp = dynamic_cast<TagComponent*>(component);
				char str0[50];
				strcpy(str0, tmp->GetTag().c_str());
				if (ImGui::InputText("##Name", str0, IM_ARRAYSIZE(str0)))
				{
					//TODO: add some length checks
					tmp->SetTag(str0);
				}
				ImGui::Separator();
			}
			else if (dynamic_cast<GraphicsComponent*>(component) != nullptr)
			{		
			}
			//TODO: Add more components features to UI
		}
	}
	ImGui::End();
}

