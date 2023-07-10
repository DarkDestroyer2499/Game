#include "EventBroadcaster.hpp"
#include <Util/Log.hpp>

namespace Oblivion
{
	void EventBroadcaster::Attach(EventType eventType, IObserver* observer)
	{
		mObserverList[eventType].push_back(observer);
	}

	void EventBroadcaster::Detach(EventType eventType, IObserver* observer)
	{
		mObserverList[eventType].remove(observer);
	}

	void EventBroadcaster::Notify(const sf::Event& event)
	{
		//TODO: Think about algo that will call virtual functions by their offset in vtable of base Event class
		for (const auto& observer : mObserverList[static_cast<EventType>(event.type)])
		{
			switch (event.type)
			{
			case sf::Event::Closed: {observer->OnWindowClosed(); break; }
			case sf::Event::Resized: {observer->OnResized(event); break; }
			case sf::Event::LostFocus: {observer->OnLostFocus(); break; }
			case sf::Event::GainedFocus: {observer->OnGainedFocus(); break; }
			case sf::Event::TextEntered: {observer->OnTextEntered(event); break; }
			case sf::Event::KeyPressed: {observer->OnKeyPressed(event); break; }
			case sf::Event::KeyReleased: {observer->OnKeyReleased(event); break; }
			case sf::Event::MouseWheelMoved: {observer->OnMouseWheelMoved(event); break; }
			case sf::Event::MouseWheelScrolled: {observer->OnMouseWheelScrolled(event); break; }
			case sf::Event::MouseButtonPressed: {observer->OnMouseButtonPressed(event); break; }
			case sf::Event::MouseButtonReleased: {observer->OnMouseButtonReleased(event); break; }
			case sf::Event::MouseMoved: {observer->OnMouseMoved(event); break; }
			case sf::Event::MouseEntered: {observer->OnMouseEntered(); break; }
			case sf::Event::MouseLeft: {observer->OnMouseLeft(); break; }
			case sf::Event::JoystickButtonPressed: {observer->OnJoystickButtonPressed(event); break; }
			case sf::Event::JoystickButtonReleased: {observer->OnJoystickButtonReleased(event); break; }
			case sf::Event::JoystickMoved: {observer->OnJoystickMoved(event); break; }
			case sf::Event::JoystickConnected: {observer->OnJoystickConnected(event); break; }
			case sf::Event::JoystickDisconnected: {observer->OnJoystickDisconnected(event); break; }
			case sf::Event::TouchBegan: {observer->OnTouchBegan(event); break; }
			case sf::Event::TouchMoved: {observer->OnTouchMoved(event); break; }
			case sf::Event::TouchEnded: {observer->OnTouchEnded(event); break; }
			case sf::Event::SensorChanged: {observer->OnSensorChanged(event); break; }
			}
		}
	}

	void EventBroadcaster::Notify(EventType event)
	{
		for (const auto& observer : mObserverList[event])
		{

		}
	}


}