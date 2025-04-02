#include "Boss.h"
#include "TransformComponent.h"
#include "../game.h" 
#include "../AssetManager.h" 
#include <cstdlib>
#include <ctime> 
void BossAIComponent::init()
{
    transform = &entity->getComponent<TransformComponent>();
    lastShotTime = SDL_GetTicks(); 
    fireRate = 3; 
    projSpeed = 3;
}


void BossAIComponent::update()
{
    

    Uint32 currentTime = SDL_GetTicks();
    float timeSinceLastShot = (currentTime - lastShotTime) / 1000.0f;

    if (timeSinceLastShot >= (1.0f / fireRate))
    {
        cout << "Boss is about to shoot projectile!" << endl;
        int randomProjectileType = rand() % 4;
        Vector2D projectileSpawnPos = transform->position;

        float spawnOffsetX = 100.0f;
        float spawnOffsetY = 100.0f;
        projectileSpawnPos = projectileSpawnPos + Vector2D(spawnOffsetX, spawnOffsetY);

        switch (randomProjectileType) {
        case 0:
            assets->CreateBigStraightProjectile(projectileSpawnPos, 500,projSpeed-1, Game::groupBossProjectiles, "bossbig");
            cout << "Boss shot: Straight" << endl;
            break;
        case 1:

            assets->CreateRingProjectile(projectileSpawnPos, Vector2D(1, 1), 1000, 1, Game::groupBossProjectiles, "bossring");
            cout << "Boss shot: Ring" << endl;
            break;
        case 2:

            assets->CreateSpreadProjectile(projectileSpawnPos, Vector2D(1, 1), 2800, 10, Game::groupBossProjectiles, "bossspread");
            break;
        default:
            assets->CreatePlayerSeekingStraightProjectile(projectileSpawnPos, 500, projSpeed, Game::groupBossProjectiles, "bosstraight");
            break;
    }
        lastShotTime = currentTime;
    }
}