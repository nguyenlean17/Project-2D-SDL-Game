#pragma once


#include "component.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>
#include "../AssetManager.h"
using namespace std;

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, desRect;
	bool animated = false;
	int frames = 0;
	int speed = 100;


public:
	int animIndex = 0;

	std::map<const char*, Animation > animations;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;


	SpriteComponent() = default;
	SpriteComponent(string id)
	{
		setTex(id);
	}
	SpriteComponent(string id, bool isAnimated)
	{
	
		animated = isAnimated;
		Animation idle = Animation(0, 3, 100);
		Animation boss = Animation(0, 3, 100);
		Animation walk = Animation(1, 3, 100);
		Animation walkDown = Animation(2, 3, 100);
		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);
		animations.emplace("WalkDown", walkDown);
		Play("Idle");
	

		setTex(id);
	}
	~SpriteComponent()
	{

	}
	void setTex(string id)
	{
		texture = Game::assets->GetTexture(id);
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
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);

		}
		srcRect.y = animIndex * transform->height;

		desRect.x = static_cast<int>(transform->position.x);
		desRect.y = static_cast<int>(transform->position.y);
		desRect.w = transform->width * transform->scale;
		desRect.h = transform->height * transform->scale;

	}
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, desRect,spriteFlip);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;

	}

};