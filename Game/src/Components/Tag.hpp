#pragma once

#ifndef TAG_H
#define TAG_H

#include "IComponent.hpp"

class TagComponent : public IComponent
{
public:
	TagComponent() = delete;
	TagComponent(const std::string& newTag);
	void Update(const float&) override;
	void SetTag(std::string& newTag);
	void SetTag(std::string newTag);
	void SetTag(char* newTag);
	const std::string& GetTag() const;
	~TagComponent();
private:
	std::string mTag;
};

#endif // !TAG_H
