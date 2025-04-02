#include "map.h"
#include "game.h"
#include <fstream>
#include <string>
#include "ECS/component.h"
#include "ECS/ecs.h"
using namespace std;

extern Manager manager;

Map::Map(string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts)
{
	scaledSize = ms * ts;
}
Map::~Map()
{
}
void Map::LoadMap(string path, int sizeX, int sizeY)
{
	char c;
	fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;
	

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;
			AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
		
			
				mapFile.ignore();
		
		
		}
	mapFile.close();
}
	for (int y = 0;y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			if (c == '3')
			{

				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
				
			}
			mapFile.ignore();
		}
	}

	mapFile.close();
}
void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos,tileSize,mapScale, texID);
	tile.addGroup(Game::groupMap);
}