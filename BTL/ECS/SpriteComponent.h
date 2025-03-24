#pragma once


#include "component.h"
#include "SDL.h"
#include "../TextureManager.h"

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
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}
	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
		

	}
	void update() override
	{
		desRect.x = (int)transform->position.x;
		desRect.y = (int)transform->position.y;
		desRect.w = transform->width * transform->scale;
		desRect.h = transform->height * transform->scale;

	}
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, desRect);
	}



};