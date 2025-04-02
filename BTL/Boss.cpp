#include "Boss.h"
#include "TransformComponent.h"
#include "../game.h" // For Game::assets, Game::renderer (if needed)
#include "../AssetManager.h" // For AssetManager

void BossAIComponent::init()
{
    transform = &entity->getComponent<TransformComponent>();
    lastShotTime = SDL_GetTicks(); // Initialize last shot time to current time
    fireRate = 0.5f; // Example: 0.5 shots per second (adjust as needed)
}

void BossAIComponent::update()
{
    Uint32 currentTime = SDL_GetTicks();
    float timeSinceLastShot = (currentTime - lastShotTime) / 1000.0f; // Time in seconds

    if (timeSinceLastShot >= (1.0f / fireRate)) // Check if enough time has passed for next shot
    {
        // **BOSS SHOOTING LOGIC - CALL PROJECTILE CREATION FUNCTIONS HERE:**

        // Example: Boss shoots a straight projectile every fireRate seconds
        assets->CreateStraightProjectile(transform->position, Vector2D(-3, 0), 500, 3, "projectile"); // Shoot straight left

        // You can add more shooting logic here, like:
        // - Randomly choose between different projectile types (straight, spread, ring).
        // - Implement shooting patterns (e.g., shoot a burst, then wait, then shoot a ring).
        // - Aim at the player (using player's position).


        lastShotTime = currentTime; // Update last shot time
    }
}