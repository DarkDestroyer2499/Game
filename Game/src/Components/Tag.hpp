#pragma once

#ifndef TAG_H
#define TAG_H

#include "IComponent.hpp"

class TagComponent : public IComponent
{
public:
	TagComponent() = delete;
	TagComponent(const std::string& newTag);
	void Update() override;
	void SetTag(std::string& newTag);
	const std::string& GetTag() const;
	const char* GetName() override;
	~TagComponent();
private:
	std::string mTag;
};

#endif // !TAG_H
