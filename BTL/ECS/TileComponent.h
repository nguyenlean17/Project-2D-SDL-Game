#pragma once
#include "ecs.h"
#include "SDL.h"

class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;
	Vector2D position;
	TileComponent() = default;
	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}
	TileComponent(int srcX, int srcY, int x, int y,int tsize,int tscale, string id)
	{
		texture = Game::assets->GetTexture(id);
		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;
		position.x = static_cast<float>(x);
		position.y = static_cast<float>(y);
		desRect.w = desRect.h = tsize * tscale;
	}
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, desRect, SDL_FLIP_NONE);
	}
};