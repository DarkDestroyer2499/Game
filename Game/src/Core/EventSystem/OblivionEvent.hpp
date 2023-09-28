#ifndef OBLIVION_EVENT_HPP
#define OBLIVION_EVENT_HPP

#include "IEvent.hpp"
#include "Core/Entity.hpp"

namespace Oblivion
{
	class OblivionEvent : public IEvent
	{
	public:
		virtual ~OblivionEvent() = default;

		virtual void OnAnyEntityCreated(Entity*) {}
		virtual void OnAnyEntityRemoved(Entity*) {}
	};
}
#endif // !OBLIVION_EVENT_HPP
