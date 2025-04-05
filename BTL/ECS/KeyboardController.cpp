
#include "KeyboardController.h" 
#include "../game.h" 
#include "TransformComponent.h" 
#include "SpriteComponent.h"  
#include "../Vector2D.h"     
#include "../AssetManager.h"  


void KeyboardController::init()
{
    transform = &entity->getComponent<TransformComponent>();
    sprite = &entity->getComponent<SpriteComponent>();
}

void KeyboardController::update()
{
    GameState currentGameState;
    // KEYBOARD CONTROLLED MOVEMENTs
    if (Game::event.type == SDL_KEYDOWN)
    {
        switch (Game::event.key.keysym.sym)
        {
        case SDLK_w:
            transform->velocity.y = -1.2;
            sprite->Play("Walk");
            break;
        case SDLK_s:
            transform->velocity.y = 1.2;
            sprite->Play("Idle");
            break;
        case SDLK_a:
            transform->velocity.x = -1.2;
            sprite->Play("WalkDown");
            sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
            break;
        case SDLK_d:
            transform->velocity.x = 1.2;
            sprite->spriteFlip = SDL_FLIP_NONE;
            sprite->Play("WalkDown");
            break;

        default:
            break;
        }
    }
    else if (Game::event.type == SDL_KEYUP)
    {
        switch (Game::event.key.keysym.sym)
        {
        case SDLK_w:
            transform->velocity.y = 0;
            sprite->Play("Idle");
            break;
        case SDLK_s:
            transform->velocity.y = 0;
            sprite->Play("Idle");
            sprite->spriteFlip = SDL_FLIP_NONE;
            break;
        case SDLK_a:
            transform->velocity.x = 0;
            sprite->Play("Idle");
            sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
            break;
        case SDLK_d:
            transform->velocity.x = 0;
            sprite->Play("Idle");
            sprite->spriteFlip = SDL_FLIP_NONE;
            break;
        case SDLK_ESCAPE:
        {
			currentGameState = GameState::MainMenu;
            break;
        }
        default:
            break;
        }
    }
   if (Game::event.type == SDL_MOUSEBUTTONDOWN) 
    {
        if (Game::event.button.button == SDL_BUTTON_LEFT) 
        {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            Vector2D playerPos = this->transform->position;
            Vector2D mousePos = { (float)mouseX, (float)mouseY };

            Vector2D direction = mousePos - playerPos;
            direction.Normalize();

            float projectileSpeed = 3.0f;
            float projectileRange = 500.0f;
            float spawnOffsetX = direction.x * (this->transform->scale * this->transform->width / 1.0f);
            float spawnOffsetY = direction.y * (this->transform->scale * this->transform->height / 1.0f);

            Vector2D projectileSpawnPos = playerPos + Vector2D(spawnOffsetX, spawnOffsetY);

            this->assets->CreateProjectile(projectileSpawnPos, direction * projectileSpeed, projectileRange, projectileSpeed, Game::groupPlayerProjectiles, "fire");
        }
    }
}