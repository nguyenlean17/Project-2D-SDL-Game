#include "game.h"
#include "TextureManager.h"
#include "map.h"
#include "ECS/component.h"
#include "Vector2D.h"
#include "Collision.h"
using namespace std;

Map* map1;
Manager manager;


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;


vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& map3(manager.addEntity());

const char* mapfile = "assets/terrain_sses.png";

enum groupLabels : size_t
{
	groupMaps,
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};


Game::Game()
{}
Game::~Game()
{}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen)
{
	int flags = 0;
	if (fullScreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "initialized" << endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			cout << "window created" << endl;

		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "rendered stuffs need rendering" << endl;

		}
		isRunning = true;

	}
	
	map1 = new Map();
	//ecs
	

	Map::LoadMap("assets/map.map", 25, 20);

	player.addComponent<TransformComponent>(10,100,32,32,3);
	player.addComponent<SpriteComponent>("assets/char_walking.png",true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
	
	map3.addComponent<TransformComponent>(0, 0, 1080, 1920, 1);
	map3.addComponent<SpriteComponent>("assets/maptrom.png", false);
	map3.addGroup(groupMaps);
}	
void Game::handleEvents()
{

	
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();
	for (auto cc : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}
}
auto& map3s(manager.getGroup(groupMaps));
auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));
void Game::render()
{
	SDL_RenderClear(renderer);
	//render cac thu o day
	for (auto& m : map3s)
	{
		m->draw();
	}
	for (auto& p: players)
	{
		p->draw();
	}
	for (auto& e : enemies)
	{
		e->draw();
	}
	SDL_RenderPresent(renderer);
}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "quitted out n cleaned" << endl;
}
void Game::AddTile(int srcX,int srcY, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, x, y, mapfile);
	tile.addGroup(groupMap);
}