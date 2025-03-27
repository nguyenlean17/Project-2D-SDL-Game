#pragma once
#include "ecs.h"
#include "SDL.h"

class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;
	TileComponent() = default;
	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}
	TileComponent(int srcX, int srcY, int x, int y, const char* path)
	{
		texture = TextureManager::LoadTexture(path);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 32;
		desRect.x = x;
		desRect.y = y;
		desRect.w = desRect.h = 64;
	}
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, desRect, SDL_FLIP_NONE);
	}
};