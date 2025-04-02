
#pragma once

#include "component.h"
#include "../Vector2D.h"
#include "../AssetManager.h" 

class BossAIComponent : public Component
{
public:
    TransformComponent* transform; 
    AssetManager* assets; 

    BossAIComponent(AssetManager* assetManager) : assets(assetManager) {}

    
    float fireRate;
    float projSpeed;
    void init() override;
    void update() override;
private:
    Uint32 lastShotTime; 
   
};