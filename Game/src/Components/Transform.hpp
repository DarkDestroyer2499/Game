#pragma once

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "IComponent.hpp"
#include "../Util/Util.hpp"

class TransformComponent : public IComponent
{
public:
	TransformComponent();
	~TransformComponent();

	void Update(const float&) override;
	void SetPosition(Vec2 newPosition);
	Vec2 GetPosition();
	void SetRotation(float newRotation);
	float GetRotation();
};

#endif // !TRANSFORM_H
