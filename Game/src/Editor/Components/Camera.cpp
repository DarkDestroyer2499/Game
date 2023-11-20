#include "Camera.hpp"
#include <util/Util.hpp>

namespace Oblivion
{
	static float CAMERA_MOVEMENT_SPEED_MULTIPLIER = 1.5f;
	static float CAMERA_SCROLL_SPEED = 0.09f;
	static float CAMERA_ZOOM_IN_LIMIT = 0.1f;
	static float CAMERA_ZOOM_OUT_LIMIT = 3.f;

	

	CameraComponent::CameraComponent(Editor* editor) :
		mEditor{ editor }, mIsPrimary{ true }, mMiddleButtonHold{ false }
	{
		mTexture = mEditor->GetRenderTexture();
		mCurrentZoom = mZoomDefault;
		mView = mEditor->GetRenderTexture()->getView();
		mView.setCenter(0, 0);
		mEditor->GetEngine()->eventBroadcaster.Attach(EventType::MouseWheelScrolled, this);
		mEditor->GetEngine()->eventBroadcaster.Attach(EventType::MouseButtonPressed, this);
		mEditor->GetEngine()->eventBroadcaster.Attach(EventType::MouseButtonReleased, this);
	}

	void CameraComponent::Update()
	{
		mView = mTexture->getView();
		mView.setSize((float)mTexture->getSize().x, (float)mTexture->getSize().y);
		mView.zoom(mCurrentZoom);
		
		if (mMiddleButtonHold == true)
		{
			Vec2 currentMousePos = mEditor->GetMousePosition();
			
			Vec2 tmpPos = mTexture->mapPixelToCoords(currentMousePos.ToSFMLVec2i());
			Vec2 positionDelta = { mLastClickedPos.x - currentMousePos.x,
								   mLastClickedPos.y - currentMousePos.y };

			Vec2 positionDelta1 = { mPosition.x + positionDelta.x * CAMERA_MOVEMENT_SPEED_MULTIPLIER, mPosition.y + positionDelta.y * CAMERA_MOVEMENT_SPEED_MULTIPLIER };
			mPosition = positionDelta1;
			
			mLastClickedPos = currentMousePos;
		}
		mView.setCenter(mPosition.x, mPosition.y);
		mTexture->setView(mView);
	}

	Vec2 CameraComponent::GetCameraPos() const
	{
		return mView.getCenter();
	}

	void CameraComponent::OnMouseWheelScrolled(const sf::Event& event)
	{
		if (event.mouseWheelScroll.delta > 0)
			mCurrentZoom -= mCurrentZoom > CAMERA_ZOOM_IN_LIMIT ? CAMERA_SCROLL_SPEED : 0;
		else
			mCurrentZoom += mCurrentZoom < CAMERA_ZOOM_OUT_LIMIT ? CAMERA_SCROLL_SPEED : 0;

		mView.zoom(mCurrentZoom);
	}

	void CameraComponent::OnMouseButtonPressed(const sf::Event& event)
	{
		if (event.mouseButton.button == sf::Mouse::Button::Middle)
		{
			mLastClickedPos = { (float)event.mouseButton.x, (float)event.mouseButton.y };
			mMiddleButtonHold = true;
		}
	}

	void CameraComponent::OnMouseButtonReleased(const sf::Event& event)
	{
		//Log(SUCCESS, "Mouse has been pressed " << lastClickedPos << " MiddlePressed: " << mMiddleButtonHold);
		if (event.mouseButton.button == sf::Mouse::Button::Middle)
		{			
			mMiddleButtonHold = false;
		}
	}

}