#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS\ecs.h"
#include "game.h"

using namespace std;

class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();

	//gameobjects
	//các hàm tạo các loại đạn của boss
	void CreateProjectile(Vector2D pos, Vector2D vel, float range, float speed, Group projectileGroup, string textureID); 
	void CreateBossSeekingStraightProjectile(Vector2D pos, float range, float speed, Group projectileGroup, string textureID);
	void CreateSpreadProjectile(Vector2D pos, Vector2D vel, float range, float speed, Group projectileGroup, string textureID);
	void CreateRingProjectile(Vector2D pos, Vector2D vel, float range, float speed, Group projectileGroup, string textureID);
	void CreatePlayerSeekingStraightProjectile(Vector2D pos, float range, float speed, Group projectileGroup, string textureID);
	void CreateBigStraightProjectile(Vector2D pos, float range, float speed, Group projectileGroup, string textureID);
	//texture management
	void AddTexture(string id, const char* path);
	SDL_Texture* GetTexture(string id);

	void AddMusic(string id, const char* path);
	Mix_Music* GetMusic(string id);         

	void AddSound(string id, const char* path); 
	Mix_Chunk* GetSound(string id);




private:
	Manager* manager;
	map<string, SDL_Texture*> textures;
	map<string, Mix_Music*> music;     
	map<string, Mix_Chunk*> sounds;
};