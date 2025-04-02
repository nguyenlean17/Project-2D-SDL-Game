
#pragma once

#include "component.h"

class HealthComponent : public Component
{
public:
    int health;      // Current health
    int maxHealth;   // Maximum health

    HealthComponent(int health, int maxHealth) : health(health), maxHealth(maxHealth) {} // Constructor

    void init() override {} // No initialization needed yet
   // No update logic needed for health component
    void draw() override {}   // No draw logic in HealthComponent itself

    void decreaseHealth(int damage)
    {
        health -= damage;
        if (health < 0)
        {
            health = 0; // Ensure health doesn't go below zero
            // Handle entity death or other game over logic here if needed
        }
        cout << "HealthComponent: Health decreased to " << health << "/" << maxHealth << endl; // Debug output
    }

private:
    // You can add private members if needed later
};