#pragma once

#include "component.h"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, desRect;
public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTex(path);
	}
	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		desRect.w = desRect.h = 64;

	}
	void update() override
	{
		desRect.x = (int)transform->position.x;
		desRect.y = (int)transform->position.y;


	}
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, desRect);
	}



};