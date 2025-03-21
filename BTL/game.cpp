#include "game.h"
#include "TextureManager.h"
#include "map.h"
#include "ECS/component.h"
#include "Vector2D.h";
using namespace std;



Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
auto& player(manager.addEntity());
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
			cout << "renderer" << endl;

		}
		isRunning = true;

	}
	
	map = new Map();
	//

	player.addComponent<TransformComponent>(10,100);
	player.addComponent<SpriteComponent>("assets/char.png");

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
	player.getComponent<TransformComponent>().position.Add(Vector2D(5, 0));
	if (player.getComponent<TransformComponent>().position.x > 100)
	{
		player.getComponent<SpriteComponent>().setTex("assets/enemy.png");
	}
}
void Game::render()
{
	SDL_RenderClear(renderer);
	//render cac thu o day
	map->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "cleaned" << endl;
}