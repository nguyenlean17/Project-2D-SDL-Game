// menu.h
#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector> 

enum class GameState;
class Entity; 

class MenuRenderer
{
public:
    MenuRenderer(SDL_Renderer* renderer, TTF_Font* font, int width, int height, std::vector<Entity*>& banners); 
    void renderMenu(int selectedMenuItem, GameState currentGameState); 
    void renderGameOverMenu(int selectedMenuItem, GameState currentGameState);

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    int width;
    int height;
    std::vector<Entity*>& banners; 
};