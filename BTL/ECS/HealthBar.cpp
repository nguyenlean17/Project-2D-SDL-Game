
#include "HealthBar.h"
#include "../game.h" 
#include "SDL.h"

void HealthBarComponent::draw()
{
    if (health == nullptr || transform == nullptr) return; 

    float healthPercentage = static_cast<float>(health->health) / health->maxHealth; // Calculate health percentage (0.0 to 1.0)
    if (healthPercentage < 0.0f) healthPercentage = 0.0f; // Clamp to 0 if health is negative
    if (healthPercentage > 1.0f) healthPercentage = 1.0f; // Clamp to 1 if health exceeds max

    int barWidth = 200;  // Width of the health bar (pixels)
    int barHeight = 10;  // Height of the health bar (pixels)
    int barX = static_cast<int>(transform->position.x + transform->width / 2 - barWidth / 2+70); // Center health bar above entity
    int barY = static_cast<int>(transform->position.y - barHeight - 0); // Position health bar above entity, with spacing

    SDL_Rect backgroundRect = { barX, barY, barWidth, barHeight }; // Background rectangle (full bar)
    SDL_Rect healthRect = { barX, barY, static_cast<int>(barWidth * healthPercentage), barHeight }; // Health filled rectangle

    // Draw background (dark gray)
    SDL_SetRenderDrawColor(Game::renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(Game::renderer, &backgroundRect);
    SDL_RenderDrawRect(Game::renderer, &backgroundRect); // Optional border

    // Draw health bar (green for full, red for low health)
    SDL_Color healthColor;
    if (healthPercentage > 0.5f) healthColor = { 0, 255, 0, 255 }; // Green for > 50%
    else if (healthPercentage > 0.25f) healthColor = { 255, 255, 0, 255 }; // Yellow for > 25%
    else healthColor = { 255, 0, 0, 255 }; // Red for <= 25%
    SDL_SetRenderDrawColor(Game::renderer, healthColor.r, healthColor.g, healthColor.b, healthColor.a);
    SDL_RenderFillRect(Game::renderer, &healthRect);
    SDL_RenderDrawRect(Game::renderer, &healthRect); // Optional border for health bar
}