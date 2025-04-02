#ifndef Game_h
#define Game_h
#define SDL_MAIN_HANDLED 
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <vector>
#include "menu.h"
#include "SDL_mixer.h"
using namespace std;
class AssetManager;
class ColliderComponent;
enum class GameDifficulty {
	Easy,
	Normal,
	Hard
};
enum class GameState {

	MainMenu,
	Playing,
	Paused,
	GameOver,    
	GameWin,
	TryAgainMenu,
	LevelSelect,
	Unknown
};
class Game
{
public: 
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	GameDifficulty currentDifficulty;
	void applyDifficulty();

	bool running()
	{
		return isRunning;	
	}

	
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static AssetManager* assets;
	static bool isRunning; 
	enum groupLabels : size_t
	{
		groupMaps,
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders,
		groupMapColliders,
		groupProjectiles,
		groupPlayerProjectiles,
		groupBossProjectiles,
		groupBanners,
		groupLost
	};

	GameState currentGameState;

private:
	void handleMenuInput();
	
	int cnt=0;
	SDL_Window *window;
	int selectedMenuItem;
	TTF_Font* font; // Add this line: Declare font as a member variable
	int width;      // Add this line: Declare width as a member variable
	int height;
	MenuRenderer* menuRenderer;
};
#endif // !Game_h
