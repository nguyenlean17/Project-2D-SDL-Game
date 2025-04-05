#include "AssetManager.h"
#include "ECS/component.h"
#include <time.h>
#include <iostream>
AssetManager::AssetManager(Manager* man) : manager(man)
{
}

AssetManager::~AssetManager()
{
}
void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, float range, float speed, Group projectileGroup, string textureID) 
{
    auto& projectile(manager->addEntity());
    projectile.addComponent<TransformComponent>(pos.x, pos.y, 16, 16,2 );
    projectile.addComponent<SpriteComponent>(textureID, true);
    projectile.addComponent<ColliderComponent>("projectile");
    projectile.addComponent<ProjectileComponent>(range, speed, vel);
    
    projectile.addGroup(projectileGroup);
}

void AssetManager::CreateSpreadProjectile(Vector2D pos, Vector2D vel, float range, float speed, Group projectileGroup, string textureID) 
{
    Vector2D playerPos;
    for (auto& p : manager->getGroup(Game::groupPlayers))
    {
        playerPos = p->getComponent<TransformComponent>().position;
        break;
    }

    
    Vector2D directionToPlayer = playerPos - pos;  
    directionToPlayer.Normalize(); 

    float numProjectiles = 6; 
    for (float i = -numProjectiles / 2; i <= numProjectiles / 2; ++i) 
    {
     
        Vector2D spreadVelocity = directionToPlayer.Rotate(i * 10 * M_PI / 180.0);

        auto& projectile(manager->addEntity());
        projectile.addComponent<TransformComponent>(pos.x, pos.y, 16, 16, 2);
        projectile.addComponent<SpriteComponent>(textureID, true);
        projectile.addComponent<ColliderComponent>("projectile");
        projectile.addComponent<ProjectileComponent>(range, speed, spreadVelocity);
        projectile.addGroup(projectileGroup);
    }
}
    

void AssetManager::CreateRingProjectile(Vector2D pos, Vector2D vel, float range, float speed, Group projectileGroup, string textureID)
{
    double randomAngleOffset = (double)(rand() % 360) * M_PI / 180.0;
    float numProjectiles = 16; 
    for (float i = 0; i < numProjectiles; ++i)
    {
        double angleRadians = (double)i / numProjectiles * 2.0 * M_PI + randomAngleOffset;
        Vector2D ringVelocity = vel.Rotate(angleRadians);

        auto& projectile(manager->addEntity());
        projectile.addComponent<TransformComponent>(pos.x, pos.y, 16, 16, 2);
        projectile.addComponent<SpriteComponent>(textureID, true);
        projectile.addComponent<ColliderComponent>("projectile");
        projectile.addComponent<ProjectileComponent>(range, speed, ringVelocity); 
        projectile.addGroup(projectileGroup);
    }
}



void AssetManager::CreatePlayerSeekingStraightProjectile(Vector2D pos, float range, float speed, Group projectileGroup, string textureID)
{
    //lay vi tri hien tai cua nguoi choi
        Vector2D playerPos;
        for (auto& p : manager->getGroup(Game::groupPlayers)) 
        {
            playerPos = p->getComponent<TransformComponent>().position; 
            break; 
        }

		// tính toán hướng từ vị trí của boss đến vị trí của người chơi
        Vector2D directionToPlayer = playerPos - pos; 
        directionToPlayer.Normalize();

      
        Vector2D seekingVelocity = directionToPlayer * speed; 

   

		// tạo một projectile với vị trí, tốc độ và hướng đã tính toán
        auto& projectile(manager->addEntity());
        projectile.addComponent<TransformComponent>(pos.x, pos.y, 16, 16, 2);
        projectile.addComponent<SpriteComponent>(textureID, true);
        projectile.addComponent<ColliderComponent>("projectile");
        projectile.addComponent<ProjectileComponent>(range, speed, seekingVelocity);
     
        projectile.addGroup(projectileGroup); 

        auto& projectile2(manager->addEntity());
        projectile2.addComponent<TransformComponent>(pos.x, pos.y - 150, 16, 16, 2);
        projectile2.addComponent<SpriteComponent>(textureID, true);
        projectile2.addComponent<ColliderComponent>("projectile");
        projectile2.addComponent<ProjectileComponent>(range, speed, seekingVelocity);
        
        projectile2.addGroup(projectileGroup);
       
      
}
void AssetManager::CreateBigStraightProjectile(Vector2D pos, float range, float speed, Group projectileGroup, string textureID)
{

    Vector2D playerPos;
    for (auto& p : manager->getGroup(Game::groupPlayers)) 
    {
        playerPos = p->getComponent<TransformComponent>().position; // láy vị trí người chơi
        break; 
    }

    Vector2D directionToPlayer = playerPos - pos; 
    directionToPlayer.Normalize(); 


    Vector2D seekingVelocity = directionToPlayer * speed; 



    auto& projectile(manager->addEntity());
    projectile.addComponent<TransformComponent>(pos.x, pos.y, 16,16,8);
    projectile.addComponent<SpriteComponent>(textureID, true);
    projectile.addComponent<ColliderComponent>("projectile");
    projectile.addComponent<ProjectileComponent>(range, speed, seekingVelocity);
    
    projectile.addGroup(projectileGroup);
   /* auto& projectile2(manager->addEntity());
    projectile2.addComponent<TransformComponent>(pos.x, pos.y-200, 16,16,7);
    projectile2.addComponent<SpriteComponent>(textureID, true);
    projectile2.addComponent<ColliderComponent>("projectile");
    projectile2.addComponent<ProjectileComponent>(range, speed, seekingVelocity);
    // **Add projectile to the specified projectileGroup:**
    projectile2.addGroup(projectileGroup); */
}
void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}


void AssetManager::AddMusic(std::string id, const char* path)
{
    Mix_Music* loadedMusic = Mix_LoadMUS(path);
    if (!loadedMusic) {
        std::cerr << "Mix_LoadMUS failed for " << path << ": " << Mix_GetError() << std::endl;
    }
    music[id] = loadedMusic;
}

Mix_Music* AssetManager:: GetMusic(std::string id)
{
    return music[id];
}

// **Sound effect management implementation**
void AssetManager::AddSound(std::string id, const char* path)
{
    Mix_Chunk* loadedSound = Mix_LoadWAV(path); 
    if (!loadedSound) {
        std::cerr << "Mix_LoadWAV failed for " << path << ": " << Mix_GetError() << std::endl;
    }
    sounds[id] = loadedSound;
}

Mix_Chunk* AssetManager::GetSound(std::string id)
{
    return sounds[id];
}

void AssetManager::CreateBossSeekingStraightProjectile(Vector2D pos, float range, float speed, Group projectileGroup, string textureID)
{
    //lay vi tri hien tai cua nguoi choi
    Vector2D playerPos;
    for (auto& p : manager->getGroup(Game::groupEnemies))
    {
        playerPos = p->getComponent<TransformComponent>().position;
        break;
    }

    // tính toán hướng từ vị trí của boss đến vị trí của người chơi
    Vector2D directionToPlayer = playerPos - pos;
    directionToPlayer.Normalize();


    Vector2D seekingVelocity = directionToPlayer * speed;



    // tạo một projectile với vị trí, tốc độ và hướng đã tính toán
    auto& projectile(manager->addEntity());
    projectile.addComponent<TransformComponent>(pos.x, pos.y, 16, 16, 2);
    projectile.addComponent<SpriteComponent>(textureID, true);
    projectile.addComponent<ColliderComponent>("projectile");
    projectile.addComponent<ProjectileComponent>(range, speed, seekingVelocity);

    projectile.addGroup(projectileGroup);
}