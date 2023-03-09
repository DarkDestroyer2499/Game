#include "Viewport.hpp"

namespace Oblivion
{
	ViewportComponent::ViewportComponent(Editor* editor) :
		mEditor{ editor }
	{
	}

	Vec2 ViewportComponent::GetPosition()
	{
		return mPosition;
	}

	Vec2 ViewportComponent::GetSize()
	{
		return mSize;
	}

	void ViewportComponent::Update()
	{
		static ImVec2 viewportSize = ImGui::GetWindowSize();
		mEditor->GetRenderTexture()->create(static_cast<unsigned int>(viewportSize.x),
			static_cast<unsigned int>(viewportSize.y));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
		mSize = viewportSize;

		if (ImGui::Begin("Viewport")) {
			viewportSize = ImGui::GetWindowSize();
			mPosition = ImGui::GetWindowPos();
			ImGui::Image(*mEditor->GetRenderTexture());			
		}

		ImGui::End();

		ImGui::PopStyleVar();
	}
}