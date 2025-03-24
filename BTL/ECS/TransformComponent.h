#pragma once

#include "component.h"
#include "../Vector2D.h"
class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;
	float speed = 3.3f;
	int height = 32;
	int width = 32;
	int scale = 1;

	TransformComponent()
	{
		position.x = 0.0f;
		position.y = 0.0f;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;

	}
	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}
	void init() override
	{
		velocity.x = 0;
		velocity.y = 0;
	}
	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};