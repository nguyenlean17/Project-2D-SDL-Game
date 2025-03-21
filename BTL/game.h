#ifndef Game_h
#define Game_h
#define SDL_MAIN_HANDLED 
#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <iostream>
class Game
{
public: 
	Game();
	~Game();
	
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	

	bool running()
	{
		return isRunning;	
	}
	static SDL_Renderer* renderer;
private:
	int count=0;
	bool isRunning;
	SDL_Window *window;

};
#endif // !Game_h
