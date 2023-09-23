#ifndef IUI_COMPONENT_HPP
#define IUI_COMPONENT_HPP

#include <Core/EventBroadcaster.hpp>

namespace Oblivion
{
	class Editor;

	class IEditorComponent : public EventSubscriber
	{
	public:
		virtual ~IEditorComponent() = default;
		virtual void SetOwner(Editor* newOwner) { mOwner = newOwner; }
		virtual void Update() = 0;
	protected:
		Editor* mOwner;
	};
}
#endif // !IUI_COMPONENT_HPP
