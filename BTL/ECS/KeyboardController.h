
#pragma once

#include "../game.h"      
#include "ecs.h"        
#include "component.h"   
#include "../AssetManager.h"

class KeyboardController : public Component
{
public:
    AssetManager* assets; 
    TransformComponent* transform;
    SpriteComponent* sprite;    

    KeyboardController(AssetManager* assetManager) : assets(assetManager) {}


    void init() override;
    void update() override;
};