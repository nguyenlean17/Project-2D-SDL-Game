
#pragma once

#include "component.h"
#include "HealthComponent.h" // Include HealthComponent header
#include "TransformComponent.h" // Include TransformComponent header
#include "../game.h" // For Game::renderer

class HealthBarComponent : public Component
{
public:
    HealthBarComponent() = default;
    ~HealthBarComponent() {}

    void init() override
    {
        health = &entity->getComponent<HealthComponent>(); // Get HealthComponent
        transform = &entity->getComponent<TransformComponent>(); // Get TransformComponent
    }
    void update() override {} // No update logic needed for health bar component
    void draw() override;     // Draw logic for health bar

private:
    HealthComponent* health;
    TransformComponent* transform;
};