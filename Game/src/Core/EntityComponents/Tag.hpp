#ifndef TAG_H
#define TAG_H

#include "IEntityComponent.hpp"

namespace Oblivion
{
	class TagComponent : public IEntityComponent
	{
	public:
		COMPONENT_TYPE_IMPL(TagComponent)

		TagComponent() = delete;
		TagComponent(const ::std::string& newTag);
		~TagComponent();

		::std::unique_ptr<IEntityComponent> Clone() const override;
		void Update(float) override;
		void Render(sf::RenderTarget* target) override;

		void SetTag(::std::string& newTag);
		void SetTag(::std::string newTag);
		void SetTag(char* newTag);
		const ::std::string& GetTag() const;
	private:
		::std::string mTag;
	};
}
#endif // !TAG_H
