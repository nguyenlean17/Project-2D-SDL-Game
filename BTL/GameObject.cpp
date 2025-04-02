#include "GameObject.h"
#include "TextureManager.h"
GameObject::GameObject(const char* texturesheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
}

void GameObject::Update()
{
	xpos++;
	ypos++;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	desRect.h = srcRect.h * 2;
	desRect.w = srcRect.w * 2;
	desRect.x = xpos;
	desRect.y = ypos;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &desRect);
}