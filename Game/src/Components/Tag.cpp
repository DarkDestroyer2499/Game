#include "Tag.hpp"

TagComponent::TagComponent(const std::string& newTag)
{
	mName = COMPONENT_NAME;
	mTag = newTag;
}

TagComponent::~TagComponent()
{
}

void TagComponent::Update(const float& ts)
{
}

void TagComponent::SetTag(std::string& newTag)
{
	mTag = newTag;
}

const std::string& TagComponent::GetTag() const
{
	return mTag;
}
