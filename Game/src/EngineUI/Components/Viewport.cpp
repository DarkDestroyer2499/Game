#include "Viewport.hpp"

ViewportComponent::ViewportComponent(Editor* editor):
	mEditor{ editor }
{
}

Vec2 ViewportComponent::GetPosition()
{
	return mPosition;
}

void ViewportComponent::Update()
{
	static ImVec2 viewportSize = ImGui::GetWindowSize();
	mEditor->mTexture->create(static_cast<unsigned int>(viewportSize.x),
		static_cast<unsigned int>(viewportSize.y));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));


	if (ImGui::Begin("Viewport")) {
		viewportSize = ImGui::GetWindowSize();
		mPosition = ImGui::GetWindowPos();
		ImGui::Image(*mEditor->mTexture);
	}

	ImGui::End();

	ImGui::PopStyleVar();
}
