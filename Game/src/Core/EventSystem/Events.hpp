#ifndef EVENTS_HPP
#define EVENTS_HPP

namespace Oblivion
{
	class Entity;

	struct EntityCreatedEvent
	{
		Entity* entity;
	};

	struct EntityRemovedEvent
	{
		Entity* entity;
	};

}



#endif // !EVENTS_HPP