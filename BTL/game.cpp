#include "game.h"
#include "TextureManager.h"
#include "map.h"
#include "ECS/component.h"
#include "Vector2D.h"
#include "Collision.h"
using namespace std;

Map* map;
Manager manager;


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;


vector<ColliderComponent*> Game::colliders;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLabels : size_t
{
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
	
	map = new Map();
	//ecs
	

	Map::LoadMap("assets/p16x16.map", 16, 16);

	player.addComponent<TransformComponent>(10,100);
	player.addComponent<SpriteComponent>("assets/char.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	
	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/water.png");
	wall.addComponent<ColliderComponent>("wall");
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
void Game::render()
{
	SDL_RenderClear(renderer);
	//render cac thu o day
	manager.draw();
	SDL_RenderPresent(renderer);
}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "quitted out n cleaned" << endl;
}
void Game::AddTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
}