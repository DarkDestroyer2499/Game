#include "Tag.hpp"

namespace Oblivion
{
	TagComponent::TagComponent(const ::std::string& newTag)
	{
		mName = COMPONENT_NAME;
		mTag = newTag;
	}

	TagComponent::~TagComponent()
	{
	}

	::std::unique_ptr<IEntityComponent> TagComponent::Clone() const
	{
		return ::std::make_unique<TagComponent>(*this);
	}

	void TagComponent::Update(float ts)
	{
	}

	void TagComponent::Render(sf::RenderTarget* target)
	{
	}

	void TagComponent::SetTag(::std::string& newTag)
	{
		mTag = newTag;
	}

	void TagComponent::SetTag(::std::string newTag)
	{
		mTag = newTag;
	}

	void TagComponent::SetTag(char* newTag)
	{
		mTag = newTag;
	}

	const ::std::string& TagComponent::GetTag() const
	{
		return mTag;
	}

}