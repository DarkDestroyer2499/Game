#include "Viewport.hpp"

namespace Oblivion
{
	ViewportComponent::ViewportComponent(Editor* editor) :
		mEditor{ editor }, mPosition{}, mSize{}
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

		auto* texture = mEditor->GetRenderTexture();
		unsigned int newWidth = static_cast<unsigned int>(viewportSize.x);
		unsigned int newHeight = static_cast<unsigned int>(viewportSize.y);
		if (newWidth > 0 && newHeight > 0 &&
			(texture->getSize().x != newWidth || texture->getSize().y != newHeight))
		{
			texture->create(newWidth, newHeight);
		}

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