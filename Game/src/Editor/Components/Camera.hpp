#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "IEditorComponent.hpp"
#include "Editor/Editor.hpp"

namespace Oblivion
{
	class CameraComponent : public IEditorComponent
	{
	public:
		CameraComponent(Editor*);
		~CameraComponent() = default;

		void Update() override;

		Vec2 GetCameraPos() const;

	private:
		void OnMouseWheelScrolled(const sf::Event&) override;
		void OnMouseButtonPressed(const sf::Event&) override;
		void OnMouseButtonReleased(const sf::Event&) override;

	private:
		bool mIsPrimary, mMiddleButtonHold;
		float mCurrentZoom, mZoomDefault = 1;
		Editor* mEditor;
		sf::View mView;
		sf::RenderTexture* mTexture;
		Vec2 mPosition, mLastClickedPos;
	};
}
#endif // !CAMERA_HPP
