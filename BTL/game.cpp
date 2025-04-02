#include "game.h"
#include "TextureManager.h"
#include "map.h"
#include "ECS/component.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "menu.h"
#include "ECS/Boss.h"
#include <SDL_mixer.h>
#include <iostream>
using namespace std;

Map* map2;
Manager manager;


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;


AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;
auto& arenaColliderA(manager.addEntity());
auto& arenaColliderB(manager.addEntity());
auto& arenaColliderC(manager.addEntity());
auto& arenaColliderD(manager.addEntity());
auto& player(manager.addEntity());
auto& map3(manager.addEntity());
auto& banner(manager.addEntity());
auto& boss(manager.addEntity());
auto& spawnpoint(manager.addEntity());
auto& gameover(manager.addEntity());;
auto& gameovers(manager.getGroup(Game::groupLost));
auto& banners(manager.getGroup(Game::groupBanners));
auto& map3s(manager.getGroup(Game::groupMaps));
Game::Game()
{}
Game::~Game()
{}
void Game::init(const char* title, int width, int height, bool fullscreen) //hàm khởi tạo
{

	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "initialized" << endl;

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
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


		cout << "Initializing SDL_mixer..." << endl;
		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0) { 
			cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
			isRunning = false;
			SDL_Quit(); 
			return;
		}
		cout << "SDL_mixer initialized successfully." << endl;

		cout << "Opening audio..." << endl;
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			cout << "SDL_mixer could not open audio! SDL_mixer Error: " << Mix_GetError() << endl;
			Mix_Quit();
			SDL_Quit();
			isRunning = false;
			return;
		}
		cout << "Audio opened successfully." << endl;

		currentGameState = GameState::MainMenu;
		currentDifficulty = GameDifficulty::Normal;
		selectedMenuItem = 0;
		this->width = width;  
		this->height = height;
		menuRenderer = new MenuRenderer(renderer, font, width, height, banners);
		cout << "Initializing SDL_ttf..." << endl;
		if (TTF_Init() == -1) {
			cout << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << endl;
			isRunning = false;
			return; 
		}
		cout << "SDL_ttf initialized successfully." << endl; 

		cout << "Loading font..." << endl; 
		font = TTF_OpenFont("assets/Silver.ttf", 40);
		if (!font) {
			cout << "Failed to load font! TTF_Error: " << TTF_GetError() << endl;
			isRunning = false;
			TTF_Quit();
			return;     
		}
		cout << "Font loaded successfully." << endl; 
		menuRenderer = new MenuRenderer(renderer, font, width, height, banners);

	}
	//Khai bao cac asset game.
	assets->AddMusic("menu_music", "assets/menu_music.mp3"); 
	assets->AddMusic("game_music", "assets/map1_music.mp3");
	assets->AddSound("death_sound", "assets/death_sound.wav");
	assets->AddSound("game_win", "assets/game_win.wav");
	assets->AddMusic("map1_music", "assets/map2_music.mp3");	
	assets->AddMusic("map2_music", "assets/map3_music.mp3");
	assets->AddTexture("terrain", "assets/terrain_sses.png");
	assets->AddTexture("player", "assets/char_walking2.png");
	assets->AddTexture("map", "assets/61.png");
	assets->AddTexture("boss", "assets/squishy2.png");
	assets->AddTexture("boss1", "assets/squishy1.png");
	assets->AddTexture("boss2", "assets/darksoul.png");
	assets->AddTexture("fire", "assets/fire.png");
	assets->AddTexture("bosstraight", "assets/bossstraight.png");
	assets->AddTexture("bossring", "assets/bossring.png");
	assets->AddTexture("bossspread", "assets/bossspread.png");
	assets->AddTexture("banner", "assets/btl.png");
	assets->AddTexture("straightbig", "assets/straightbig.png");
	assets->AddTexture("bossbig", "assets/bossbig.png");
	assets->AddTexture("gameover", "assets/gameover.png");
	assets->AddTexture("gamewon", "assets/gamewin.png");
	assets->AddTexture("maptroll", "assets/map1.png");
	assets->AddTexture("map1", "assets/71.png");
	assets->AddTexture("map3", "assets/81.png");
	map2 = new Map("assets/terrain_sse.png",3,32);
	//ecs
	

	map2->LoadMap("assets/map.map", 25, 20);

	arenaColliderA.addComponent<TransformComponent>(75,1, 1080, 1, 1);
	arenaColliderA.addComponent<ColliderComponent>("arena");
	arenaColliderA.addGroup(groupColliders);

	arenaColliderB.addComponent<TransformComponent>(1,75,1,1920, 1);
	arenaColliderB.addComponent<ColliderComponent>("arena");
	arenaColliderB.addGroup(groupColliders);

	arenaColliderC.addComponent<TransformComponent>(1920-70,0, 1080, 1, 1);
	arenaColliderC.addComponent<ColliderComponent>("arena");
	arenaColliderC.addGroup(groupColliders);

	arenaColliderD.addComponent<TransformComponent>(0,1080-70, 1, 1920, 1);
	arenaColliderD.addComponent<ColliderComponent>("arena");
	arenaColliderD.addGroup(groupColliders);

	spawnpoint.addComponent<TransformComponent>(300, 300, 0, 0, 1);

	player.addComponent<TransformComponent>(300,300,16,16,3);
	player.addComponent<SpriteComponent>("player",true);
	player.addComponent<KeyboardController>(Game::assets);
	player.addComponent<ColliderComponent>("player",0,0,1);
	player.addGroup(groupPlayers);
	
	gameover.addComponent<TransformComponent>(0, 0, 1080, 1920, 1);
	gameover.addComponent<SpriteComponent>("gameover", false);
	gameover.addGroup(groupLost);

	banner.addComponent<TransformComponent>(0, 0, 1080, 1920, 1);
	banner.addComponent<SpriteComponent>("banner", false);
	banner.addGroup(groupBanners);

	boss.addComponent<TransformComponent>(900, 450,56,80,3);
	boss.addComponent<SpriteComponent>("boss", true);
	boss.addGroup(groupEnemies);
	boss.addComponent<ColliderComponent>("boss");
	boss.addComponent<BossAIComponent>(assets);
	boss.addComponent<HealthComponent>(200, 200);
	boss.addComponent<HealthBarComponent>();

	map3.addComponent<TransformComponent>(0, 0, 1080, 1920, 1);
	map3.addComponent<SpriteComponent>("map", false);
	map3.addGroup(groupMaps);

}	
auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& mapcol(manager.getGroup(Game::groupColliders));
auto& colliders(manager.getGroup(Game::groupBossProjectiles));
auto& projectiles(manager.getGroup(Game::groupPlayerProjectiles));
auto& bprojectiles(manager.getGroup(Game::groupBossProjectiles));
auto& bosses(manager.getGroup(Game::groupEnemies));
// game.cpp

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN: 
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE: 
			cout << "ESC key pressed in handleEvents - Quitting!" << endl;
			isRunning = false;
			break;
		case SDLK_w: 
			selectedMenuItem--;
			if (currentGameState == GameState::MainMenu || currentGameState == GameState::GameOver) {
				if (selectedMenuItem < 0) {
					selectedMenuItem = 1;
				}
			}
			else
			if (selectedMenuItem < 0) { 
				selectedMenuItem = 2; 
			}
			cout << "Selected Menu Item: " << selectedMenuItem << endl; 
			break;
		case SDLK_s: 
			selectedMenuItem++;
			if (currentGameState == GameState::MainMenu || currentGameState == GameState::GameOver) {
				if (selectedMenuItem > 1) {
					selectedMenuItem = 0;
				}
			}
			else
			if (selectedMenuItem > 2) {
				selectedMenuItem = 0;
			}
			cout << "Selected Menu Item: " << selectedMenuItem << endl; 
			break;
		case SDLK_e:
			if (currentGameState == GameState::LevelSelect) {
				if (selectedMenuItem == 0) {
					cout << "Level 1" << endl;
					currentGameState = GameState::Playing;
					currentDifficulty = GameDifficulty::Easy;
				}
				else if (selectedMenuItem == 1) {
					cout << "Level 2" << endl;
					currentGameState = GameState::Playing;	
					currentDifficulty = GameDifficulty::Normal;
				}
				else if (selectedMenuItem == 2) {
					cout << "Level 3" << endl;
					currentGameState = GameState::Playing;
					currentDifficulty = GameDifficulty::Hard;
					
				}
			}
			if (currentGameState == GameState::MainMenu) {
				if (selectedMenuItem == 0) { 
					cout << "Play Game selected - Switching to Playing state!" << endl;
					currentGameState = GameState::LevelSelect; 
				}
				else if (selectedMenuItem == 1) { 
					cout << "Quit selected - Exiting game!" << endl;
					isRunning = false; 
				}
			}
			else if (currentGameState == GameState::GameOver) {
				if (selectedMenuItem == 0) {
					cout << "Play Again selected - Switching to Playing state!" << endl;
					currentGameState = GameState::MainMenu;
					banner.addComponent<SpriteComponent>("banner", false);
					boss.getComponent<HealthComponent>().health = 250;
				}
				else if (selectedMenuItem == 1) {
					cout << "Quit selected - Exiting game!" << endl;
					isRunning = false;
				}

			}
			break;
		}
		break;
	default:
		break;
	}
}
void Game::applyDifficulty()
{
	// Điều chỉnh game theo độ khó
	switch (currentDifficulty)
	{
	case GameDifficulty::Easy:
		// Make boss easier
		boss.getComponent<HealthComponent>().maxHealth = 150;
		boss.getComponent<HealthComponent>().health = 150;
		map3.addComponent<SpriteComponent>("map1");
		boss.addComponent<SpriteComponent>("boss1", true);
		boss.getComponent<BossAIComponent>().projSpeed = 2.0f;
		boss.getComponent<BossAIComponent>().fireRate = 1.3; // Longer cooldown
		break;
	case GameDifficulty::Normal:
		// Default settings
		boss.getComponent<HealthComponent>().maxHealth = 250;
		boss.getComponent<HealthComponent>().health = 250;
		map3.addComponent<SpriteComponent>("map");
		boss.addComponent<SpriteComponent>("boss", true);
		boss.getComponent<BossAIComponent>().projSpeed = 2.2f;
		boss.getComponent<BossAIComponent>().fireRate =2.3;
		break;
	case GameDifficulty::Hard:
		// Make boss harder
		boss.getComponent<HealthComponent>().maxHealth = 300;
		boss.getComponent<HealthComponent>().health = 300;
		//map3.addComponent<SpriteComponent>("maptroll");
		map3.addComponent<SpriteComponent>("map3");
		//boss.addComponent<TransformComponent>(500, 300,512,512, 1);
		boss.getComponent<BossAIComponent>().projSpeed = 2.0f;
		boss.getComponent<BossAIComponent>().fireRate = 3.1; // Shorter cooldown
		break;
	}
}

void Game::update()
{

	static GameState previousState = GameState::Unknown; // khai báo Previous State
	if (previousState != currentGameState && currentGameState == GameState::Playing)
	{
		applyDifficulty();
	}
	if (previousState != currentGameState) //Kiểm tra xem trạng thái game có thay đổi không
	{
		Mix_HaltChannel(0);
		if (currentGameState == GameState::Playing)
		{
			Mix_HaltMusic();
			
			if (currentDifficulty == GameDifficulty::Easy) {
				Mix_HaltMusic();
				Mix_PlayMusic(Game::assets->GetMusic("map1_music"), -1);
			}
			else if (currentDifficulty == GameDifficulty::Normal) {
				Mix_HaltMusic();
				Mix_PlayMusic(Game::assets->GetMusic("game_music"), -1);
			}
			else if (currentDifficulty == GameDifficulty::Hard)
			{
				Mix_HaltMusic();
				Mix_PlayMusic(Game::assets->GetMusic("map2_music"), -1);
			}
		}
		else if (currentGameState == GameState::MainMenu)
		{
			Mix_HaltMusic();
			Mix_PlayMusic(Game::assets->GetMusic("menu_music"), -1);
		}
	}
	previousState = currentGameState;
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	Vector2D spawnPos = spawnpoint.getComponent<TransformComponent>().position;
	manager.refresh();
	manager.update();
	for (auto& p : bprojectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			
			banner.addComponent<SpriteComponent>("gameover", false);
			currentGameState = GameState::GameOver;
			if (currentGameState != GameState::GameOver)
			p->destroy();
			Mix_HaltMusic();
			Mix_PlayChannel(-1, Game::assets->GetSound("death_sound"), 0);
			
		}
	}
	for (auto& c : mapcol) // **Iterating through groupColliders**
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			player.getComponent<TransformComponent>().position = playerPos; //neu cham tuong, khoa vi tri nguoi choi (cho den khi khong cham tuong nua) // Cach nay chua hay, em chua nghi ra cach hay hon.
		}
	}

	for (auto& p : projectiles)
	{
		if (Collision::AABB(boss.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			p->destroy();
			boss.getComponent<HealthComponent>().health = boss.getComponent<HealthComponent>().health - 2;
		}
	}
	for (auto& p : bprojectiles)
	{
		if (currentGameState == GameState::GameOver || currentGameState == GameState::MainMenu || currentGameState == GameState::LevelSelect || currentGameState==GameState::GameWin)
		{
			p->destroy();
			player.getComponent<TransformComponent>().position = spawnPos;
		}
	}
	for (auto& p : projectiles)
	{
		if (boss.getComponent<HealthComponent>().health <=  0)
		{
			banner.addComponent<SpriteComponent>("gamewon", false);
			p->destroy();
			currentGameState = GameState::GameOver;
			Mix_HaltMusic();
			Mix_PlayChannel(-1, Game::assets->GetSound("game_win"), 0);
		}
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	//render cac thu o day
	if (currentGameState == GameState::MainMenu) {
		
		menuRenderer->renderMenu(selectedMenuItem, currentGameState); // Call the MenuRenderer to render the menu
	}
	else if (currentGameState == GameState::GameWin) {

		menuRenderer->renderMenu(selectedMenuItem, GameState::GameOver); // Call the MenuRenderer to render the menu
	}
	else if (currentGameState == GameState::LevelSelect) {

		menuRenderer->renderMenu(selectedMenuItem, currentGameState); // Call the MenuRenderer to render the menu
	}
	else if (currentGameState == GameState::Playing) {
     
        for (auto m : map3s)
        {
            m->draw();
        }
        for (auto& t : tiles)
        {
            t->draw();
        }
		for (auto& c : colliders)
		{
			c->draw();
		}
        for (auto& b : bosses)
        {
            b->draw();
        }
		for (auto& b : bprojectiles)
		{
			b->draw();
		}
        for (auto& p : players)
        {
            p->draw();
        }
        for (auto& p : projectiles)
        {
            p->draw();
        }
    }
	else if (currentGameState == GameState::GameOver) {
		for (auto m : banners)
		{
			m->draw();
		}
		menuRenderer->renderMenu(selectedMenuItem, currentGameState);
	}

	SDL_RenderPresent(renderer);
	
}
void Game::clean()
{
	Mix_HaltMusic();      // Stop any music that might be playing
	Mix_CloseAudio();     // Close the audio device
	Mix_Quit();
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	cout << "quitted out n cleaned" << endl;
	Game::assets = nullptr;

}
