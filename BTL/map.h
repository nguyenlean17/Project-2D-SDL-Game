#pragma once
#include "game.h"

class Map
{
public:

	Map();
	~Map();

	void LoadMap(int arr[34][60]);
	void DrawMap();

private:

	SDL_Rect src, des;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int map[34][60];


};