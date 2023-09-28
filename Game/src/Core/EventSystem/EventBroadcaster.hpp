#ifndef EVENT_BROADCASTER_HPP
#define EVENT_BROADCASTER_HPP

#include <map>
#include <list>
#include "IEvent.hpp"
#include "SystemEvent.hpp"
#include "OblivionEvent.hpp"

namespace Oblivion
{
	class EventSubscriber : public SystemEvent, public OblivionEvent {
	public:
		virtual ~EventSubscriber() = default;
	};

	class IBroadcaster {
	public:
		virtual ~IBroadcaster() = default;
		virtual void Attach(EventType, EventSubscriber* observer) = 0;
		virtual void Detach(EventType, EventSubscriber* observer) = 0;
		virtual void Notify(const sf::Event& event) = 0;
		virtual void Notify(const EventType event, void* data = nullptr) = 0;
	};

	class EventBroadcaster : public IBroadcaster
	{
	public:
		void Attach(EventType eventType, EventSubscriber* observer) override;
		void Detach(EventType, EventSubscriber* observer) override;
		void Notify(const sf::Event& event) override;
		void Notify(const EventType event, void* data = nullptr) override;

	private:
		std::map<EventType, std::list<EventSubscriber*>> mObserverList;
	};
}
#endif // !EVENT_BROADCASTER_HPP
