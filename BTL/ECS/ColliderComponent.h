#pragma once
#include <string>
#include <SDL.h>
#include "../TextureManager.h"
#include "component.h"
using namespace std;

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	string tag;
	SDL_Texture* tex;
	SDL_Rect srcR, desR;
	TransformComponent* transform;
	
	ColliderComponent(string t)
	{
		tag = t;
	}
	
	ColliderComponent(string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;

	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		tex = TextureManager::LoadTexture("assets/grass.png");
		srcR = { 0,0,32,32 };
		desR = { collider.x,collider.y,collider.w,collider.h };
	;
	}
	void update() override
	{
		if (tag != "arena")
		{
			collider.x = static_cast<int> (transform->position.x)+10;
			collider.y = static_cast<int> (transform->position.y)+10;
			collider.w = (transform->width * transform->scale)-20;
			collider.h = (transform->height * transform->scale)-20;
		}
		else if(tag == "arena")
		{
			collider.x = static_cast<int> (transform->position.x);
			collider.y = static_cast<int> (transform->position.y);
			collider.w = (transform->width * transform->scale);
			collider.h = (transform->height * transform->scale);
		}

	}
	void draw() override
	{
		//SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255); 
		//SDL_RenderDrawRect(Game::renderer, &collider); 
		TextureManager::Draw(tex, srcR, desR, SDL_FLIP_NONE);
	}
private:

};