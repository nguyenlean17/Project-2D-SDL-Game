// menu.cpp
#include "menu.h"
#include "game.h" // Include game.h so MenuRenderer knows about GameState enum
#include "ECS/component.h"
#include "ECS/ecs.h"
#include <SDL_ttf.h>

MenuRenderer::MenuRenderer(SDL_Renderer* renderer, TTF_Font* font, int width, int height, std::vector<Entity*>& banners)
    : renderer(renderer), font(font), width(width), height(height), banners(banners)
{
}

void MenuRenderer::renderMenu(int selectedMenuItem, GameState currentGameState)
{
    // Only render if in MainMenu state
    TTF_Font* localFont = TTF_OpenFont("assets/Silver.ttf", 40); // **Load font LOCALLY**
    if (!localFont) { // **Error check for local font loading**
        cout << "ERROR: Failed to load local font in MenuRenderer::renderMenu()! TTF_Error: " << TTF_GetError() << endl;
        return; // Exit renderMenu if local font loading fails
    }

    for (auto b : banners)
    {
        b->draw();
    }
    if (currentGameState == GameState::MainMenu) {
        // **BUTTON STYLE VARIABLES (from your game.cpp)**
        SDL_Color buttonColorNormal = { 100, 100, 100, 255 };
        SDL_Color buttonColorSelected = { 150, 150, 150, 255 };
        SDL_Color buttonBorderColor = { 50, 50, 50, 255 };
        int buttonWidth = 200;
        int buttonHeight = 50;
        int buttonSpacing = 60;

        // **RENDER BUTTON RECTANGLES (from your game.cpp)**
        SDL_Rect rectButtonPlay;
        rectButtonPlay.w = buttonWidth;
        rectButtonPlay.h = buttonHeight;
        rectButtonPlay.x = width / 2 - buttonWidth / 2;
        rectButtonPlay.y = height / 2 - buttonSpacing / 2 - buttonHeight;

        SDL_Rect rectButtonQuit;
        rectButtonQuit.w = buttonWidth;
        rectButtonQuit.h = buttonHeight;
        rectButtonQuit.x = width / 2 - buttonWidth / 2;
        rectButtonQuit.y = height / 2 + buttonSpacing / 2;

        // **"Play Game" Button Rectangle:**
        SDL_SetRenderDrawColor(renderer, (selectedMenuItem == 0) ? buttonColorSelected.r : buttonColorNormal.r,
            (selectedMenuItem == 0) ? buttonColorSelected.g : buttonColorNormal.g,
            (selectedMenuItem == 0) ? buttonColorSelected.b : buttonColorNormal.b,
            buttonColorNormal.a);
        SDL_RenderFillRect(renderer, &rectButtonPlay);
        SDL_SetRenderDrawColor(renderer, buttonBorderColor.r, buttonBorderColor.g, buttonBorderColor.b, buttonBorderColor.a);
        SDL_RenderDrawRect(renderer, &rectButtonPlay);

        // **"Quit" Button Rectangle:**
        SDL_SetRenderDrawColor(renderer, (selectedMenuItem == 1) ? buttonColorSelected.r : buttonColorNormal.r,
            (selectedMenuItem == 1) ? buttonColorSelected.g : buttonColorNormal.g,
            (selectedMenuItem == 1) ? buttonColorSelected.g : buttonColorNormal.g,
            buttonColorNormal.a);
        SDL_RenderFillRect(renderer, &rectButtonQuit);
        SDL_SetRenderDrawColor(renderer, buttonBorderColor.r, buttonBorderColor.g, buttonBorderColor.b, buttonBorderColor.a);
        SDL_RenderDrawRect(renderer, &rectButtonQuit);


        SDL_Color textColorNormal = { 0, 0, 0, 255 };
        SDL_Color textColorSelected = { 255, 255, 255, 255 };
        SDL_Color playTextColor = (selectedMenuItem == 0) ? textColorSelected : textColorNormal;
        SDL_Color quitTextColor = (selectedMenuItem == 1) ? textColorSelected : textColorNormal;
        // **"Play Game" Text Rendering - USE localFont HERE:**
        SDL_Surface* textSurfacePlay = TTF_RenderText_Blended(localFont, "Play Game", playTextColor); // **Use localFont here!**
        if (!textSurfacePlay) { /* Error check - keep it */ }
        SDL_Texture* textTexturePlay = SDL_CreateTextureFromSurface(renderer, textSurfacePlay);
        if (!textTexturePlay) { /* Error check - keep it */ }
        SDL_Rect rectTextPlay;
        SDL_QueryTexture(textTexturePlay, NULL, NULL, &rectTextPlay.w, &rectTextPlay.h);
        rectTextPlay.x = rectButtonPlay.x + (buttonWidth - rectTextPlay.w) / 2;
        rectTextPlay.y = rectButtonPlay.y + (buttonHeight - rectTextPlay.h) / 2;
        SDL_RenderCopy(renderer, textTexturePlay, NULL, &rectTextPlay);
        SDL_FreeSurface(textSurfacePlay);
        SDL_DestroyTexture(textTexturePlay);


        SDL_Surface* textSurfaceQuit = TTF_RenderText_Blended(localFont, "Quit", quitTextColor); // **Use localFont here!**
        if (!textSurfaceQuit) { /* Error check - keep it */ }
        SDL_Texture* textTextureQuit = SDL_CreateTextureFromSurface(renderer, textSurfaceQuit);
        if (!textTextureQuit) { /* Error check - keep it */ }
        SDL_Rect rectTextQuit;
        SDL_QueryTexture(textTextureQuit, NULL, NULL, &rectTextQuit.w, &rectTextQuit.h);
        rectTextQuit.x = rectButtonQuit.x + (buttonWidth - rectTextQuit.w) / 2;
        rectTextQuit.y = rectButtonQuit.y + (buttonHeight - rectTextQuit.h) / 2;
        SDL_RenderCopy(renderer, textTextureQuit, NULL, &rectTextQuit);
        SDL_FreeSurface(textSurfaceQuit);
        SDL_DestroyTexture(textTextureQuit);
    }
    else if (currentGameState == GameState::GameOver) {
        // **BUTTON STYLE VARIABLES (from your game.cpp)**
        SDL_Color buttonColorNormal = { 100, 100, 100, 255 };
        SDL_Color buttonColorSelected = { 150, 150, 150, 255 };
        SDL_Color buttonBorderColor = { 50, 50, 50, 255 };
        int buttonWidth = 200;
        int buttonHeight = 50;
        int buttonSpacing = 60;

        // **RENDER BUTTON RECTANGLES (from your game.cpp)**
        SDL_Rect rectButtonPlay;
        rectButtonPlay.w = buttonWidth;
        rectButtonPlay.h = buttonHeight;
        rectButtonPlay.x = width / 2 - buttonWidth / 2;
        rectButtonPlay.y = height / 2 - buttonSpacing / 2 - buttonHeight;

        SDL_Rect rectButtonQuit;
        rectButtonQuit.w = buttonWidth;
        rectButtonQuit.h = buttonHeight;
        rectButtonQuit.x = width / 2 - buttonWidth / 2;
        rectButtonQuit.y = height / 2 + buttonSpacing / 2;

        // **"Play Game" Button Rectangle:**
        SDL_SetRenderDrawColor(renderer, (selectedMenuItem == 0) ? buttonColorSelected.r : buttonColorNormal.r,
            (selectedMenuItem == 0) ? buttonColorSelected.g : buttonColorNormal.g,
            (selectedMenuItem == 0) ? buttonColorSelected.b : buttonColorNormal.b,
            buttonColorNormal.a);
        SDL_RenderFillRect(renderer, &rectButtonPlay);
        SDL_SetRenderDrawColor(renderer, buttonBorderColor.r, buttonBorderColor.g, buttonBorderColor.b, buttonBorderColor.a);
        SDL_RenderDrawRect(renderer, &rectButtonPlay);

        // **"Quit" Button Rectangle:**
        SDL_SetRenderDrawColor(renderer, (selectedMenuItem == 1) ? buttonColorSelected.r : buttonColorNormal.r,
            (selectedMenuItem == 1) ? buttonColorSelected.g : buttonColorNormal.g,
            (selectedMenuItem == 1) ? buttonColorSelected.g : buttonColorNormal.g,
            buttonColorNormal.a);
        SDL_RenderFillRect(renderer, &rectButtonQuit);
        SDL_SetRenderDrawColor(renderer, buttonBorderColor.r, buttonBorderColor.g, buttonBorderColor.b, buttonBorderColor.a);
        SDL_RenderDrawRect(renderer, &rectButtonQuit);


        SDL_Color textColorNormal = { 0, 0, 0, 255 };
        SDL_Color textColorSelected = { 255, 255, 255, 255 };
        SDL_Color playTextColor = (selectedMenuItem == 0) ? textColorSelected : textColorNormal;
        SDL_Color quitTextColor = (selectedMenuItem == 1) ? textColorSelected : textColorNormal;
        // **"Play Game" Text Rendering - USE localFont HERE:**
        SDL_Surface* textSurfacePlay = TTF_RenderText_Blended(localFont, "Try Again", playTextColor); // **Use localFont here!**
        if (!textSurfacePlay) { /* Error check - keep it */ }
        SDL_Texture* textTexturePlay = SDL_CreateTextureFromSurface(renderer, textSurfacePlay);
        if (!textTexturePlay) { /* Error check - keep it */ }
        SDL_Rect rectTextPlay;
        SDL_QueryTexture(textTexturePlay, NULL, NULL, &rectTextPlay.w, &rectTextPlay.h);
        rectTextPlay.x = rectButtonPlay.x + (buttonWidth - rectTextPlay.w) / 2;
        rectTextPlay.y = rectButtonPlay.y + (buttonHeight - rectTextPlay.h) / 2;
        SDL_RenderCopy(renderer, textTexturePlay, NULL, &rectTextPlay);
        SDL_FreeSurface(textSurfacePlay);
        SDL_DestroyTexture(textTexturePlay);


        SDL_Surface* textSurfaceQuit = TTF_RenderText_Blended(localFont, "Quit", quitTextColor); // **Use localFont here!**
        if (!textSurfaceQuit) { /* Error check - keep it */ }
        SDL_Texture* textTextureQuit = SDL_CreateTextureFromSurface(renderer, textSurfaceQuit);
        if (!textTextureQuit) { /* Error check - keep it */ }
        SDL_Rect rectTextQuit;
        SDL_QueryTexture(textTextureQuit, NULL, NULL, &rectTextQuit.w, &rectTextQuit.h);
        rectTextQuit.x = rectButtonQuit.x + (buttonWidth - rectTextQuit.w) / 2;
        rectTextQuit.y = rectButtonQuit.y + (buttonHeight - rectTextQuit.h) / 2;
        SDL_RenderCopy(renderer, textTextureQuit, NULL, &rectTextQuit);
        SDL_FreeSurface(textSurfaceQuit);
        SDL_DestroyTexture(textTextureQuit);
    }
    else if (currentGameState == GameState::GameWin) {
        // **BUTTON STYLE VARIABLES (from your game.cpp)**
        SDL_Color buttonColorNormal = { 100, 100, 100, 255 };
        SDL_Color buttonColorSelected = { 150, 150, 150, 255 };
        SDL_Color buttonBorderColor = { 50, 50, 50, 255 };
        int buttonWidth = 200;
        int buttonHeight = 50;
        int buttonSpacing = 60;

        // **RENDER BUTTON RECTANGLES (from your game.cpp)**
        SDL_Rect rectButtonPlay;
        rectButtonPlay.w = buttonWidth;
        rectButtonPlay.h = buttonHeight;
        rectButtonPlay.x = width / 2 - buttonWidth / 2;
        rectButtonPlay.y = height / 2 - buttonSpacing / 2 - buttonHeight;

        SDL_Rect rectButtonQuit;
        rectButtonQuit.w = buttonWidth;
        rectButtonQuit.h = buttonHeight;
        rectButtonQuit.x = width / 2 - buttonWidth / 2;
        rectButtonQuit.y = height / 2 + buttonSpacing / 2;

        // **"Play Game" Button Rectangle:**
        SDL_SetRenderDrawColor(renderer, (selectedMenuItem == 0) ? buttonColorSelected.r : buttonColorNormal.r,
            (selectedMenuItem == 0) ? buttonColorSelected.g : buttonColorNormal.g,
            (selectedMenuItem == 0) ? buttonColorSelected.b : buttonColorNormal.b,
            buttonColorNormal.a);
        SDL_RenderFillRect(renderer, &rectButtonPlay);
        SDL_SetRenderDrawColor(renderer, buttonBorderColor.r, buttonBorderColor.g, buttonBorderColor.b, buttonBorderColor.a);
        SDL_RenderDrawRect(renderer, &rectButtonPlay);

        // **"Quit" Button Rectangle:**
        SDL_SetRenderDrawColor(renderer, (selectedMenuItem == 1) ? buttonColorSelected.r : buttonColorNormal.r,
            (selectedMenuItem == 1) ? buttonColorSelected.g : buttonColorNormal.g,
            (selectedMenuItem == 1) ? buttonColorSelected.g : buttonColorNormal.g,
            buttonColorNormal.a);
        SDL_RenderFillRect(renderer, &rectButtonQuit);
        SDL_SetRenderDrawColor(renderer, buttonBorderColor.r, buttonBorderColor.g, buttonBorderColor.b, buttonBorderColor.a);
        SDL_RenderDrawRect(renderer, &rectButtonQuit);


        SDL_Color textColorNormal = { 0, 0, 0, 255 };
        SDL_Color textColorSelected = { 255, 255, 255, 255 };
        SDL_Color playTextColor = (selectedMenuItem == 0) ? textColorSelected : textColorNormal;
        SDL_Color quitTextColor = (selectedMenuItem == 1) ? textColorSelected : textColorNormal;
        // **"Play Game" Text Rendering - USE localFont HERE:**
        SDL_Surface* textSurfacePlay = TTF_RenderText_Blended(localFont, "Try Again", playTextColor); // **Use localFont here!**
        if (!textSurfacePlay) { /* Error check - keep it */ }
        SDL_Texture* textTexturePlay = SDL_CreateTextureFromSurface(renderer, textSurfacePlay);
        if (!textTexturePlay) { /* Error check - keep it */ }
        SDL_Rect rectTextPlay;
        SDL_QueryTexture(textTexturePlay, NULL, NULL, &rectTextPlay.w, &rectTextPlay.h);
        rectTextPlay.x = rectButtonPlay.x + (buttonWidth - rectTextPlay.w) / 2;
        rectTextPlay.y = rectButtonPlay.y + (buttonHeight - rectTextPlay.h) / 2;
        SDL_RenderCopy(renderer, textTexturePlay, NULL, &rectTextPlay);
        SDL_FreeSurface(textSurfacePlay);
        SDL_DestroyTexture(textTexturePlay);


        SDL_Surface* textSurfaceQuit = TTF_RenderText_Blended(localFont, "Quit", quitTextColor); // **Use localFont here!**
        if (!textSurfaceQuit) { /* Error check - keep it */ }
        SDL_Texture* textTextureQuit = SDL_CreateTextureFromSurface(renderer, textSurfaceQuit);
        if (!textTextureQuit) { /* Error check - keep it */ }
        SDL_Rect rectTextQuit;
        SDL_QueryTexture(textTextureQuit, NULL, NULL, &rectTextQuit.w, &rectTextQuit.h);
        rectTextQuit.x = rectButtonQuit.x + (buttonWidth - rectTextQuit.w) / 2;
        rectTextQuit.y = rectButtonQuit.y + (buttonHeight - rectTextQuit.h) / 2;
        SDL_RenderCopy(renderer, textTextureQuit, NULL, &rectTextQuit);
        SDL_FreeSurface(textSurfaceQuit);
        SDL_DestroyTexture(textTextureQuit);
        }
    else if (currentGameState == GameState::LevelSelect)
    {
        SDL_Color buttonColorNormal = { 100, 100, 100, 255 };
        SDL_Color buttonColorSelected = { 150, 150, 150, 255 };
        SDL_Color buttonBorderColor = { 50, 50, 50, 255 };
        int buttonWidth = 200;
        int buttonHeight = 50;
        int buttonSpacing = 60;

        // **RENDER BUTTON RECTANGLES (from your game.cpp)**
        SDL_Rect rectButtonPlay;
        rectButtonPlay.w = buttonWidth;
        rectButtonPlay.h = buttonHeight;
        rectButtonPlay.x = width / 2 - buttonWidth / 2;
        rectButtonPlay.y = height / 2 - buttonSpacing / 2 - buttonHeight;

        SDL_Rect rectButtonQuit;
        rectButtonQuit.w = buttonWidth;
        rectButtonQuit.h = buttonHeight;
        rectButtonQuit.x = width / 2 - buttonWidth / 2;
        rectButtonQuit.y = height / 2 + buttonSpacing / 2;

        SDL_Rect rectButtonLevel3;
        rectButtonLevel3.w = buttonWidth;
        rectButtonLevel3.h = buttonHeight;
        rectButtonLevel3.x = width / 2 - buttonWidth / 2;
        rectButtonLevel3.y = height / 2 + buttonSpacing + buttonHeight * 2 - 10;
        // **"Play Game" Button Rectangle:**
        SDL_SetRenderDrawColor(renderer, (selectedMenuItem == 0) ? buttonColorSelected.r : buttonColorNormal.r,
            (selectedMenuItem == 0) ? buttonColorSelected.g : buttonColorNormal.g,
            (selectedMenuItem == 0) ? buttonColorSelected.b : buttonColorNormal.b,
            buttonColorNormal.a);
        SDL_RenderFillRect(renderer, &rectButtonPlay);
        SDL_SetRenderDrawColor(renderer, buttonBorderColor.r, buttonBorderColor.g, buttonBorderColor.b, buttonBorderColor.a);
        SDL_RenderDrawRect(renderer, &rectButtonPlay);

        // **"Quit" Button Rectangle:**
        SDL_SetRenderDrawColor(renderer, (selectedMenuItem == 1) ? buttonColorSelected.r : buttonColorNormal.r,
            (selectedMenuItem == 1) ? buttonColorSelected.g : buttonColorNormal.g,
            (selectedMenuItem == 1) ? buttonColorSelected.g : buttonColorNormal.g,
            buttonColorNormal.a);
        SDL_RenderFillRect(renderer, &rectButtonQuit);
        SDL_SetRenderDrawColor(renderer, buttonBorderColor.r, buttonBorderColor.g, buttonBorderColor.b, buttonBorderColor.a);
        SDL_RenderDrawRect(renderer, &rectButtonQuit);

		// **"Level 3" Button Rectangle:**
		SDL_SetRenderDrawColor(renderer, (selectedMenuItem == 2) ? buttonColorSelected.r : buttonColorNormal.r,
			(selectedMenuItem == 2) ? buttonColorSelected.g : buttonColorNormal.g,
			(selectedMenuItem == 2) ? buttonColorSelected.g : buttonColorNormal.g,
			buttonColorNormal.a);
		SDL_RenderFillRect(renderer, &rectButtonLevel3);
		SDL_SetRenderDrawColor(renderer, buttonBorderColor.r, buttonBorderColor.g, buttonBorderColor.b, buttonBorderColor.a);
        SDL_RenderDrawRect(renderer, &rectButtonLevel3);

        SDL_Color textColorNormal = { 0, 0, 0, 255 };
        SDL_Color textColorSelected = { 255, 255, 255, 255 };
        SDL_Color playTextColor = (selectedMenuItem == 0) ? textColorSelected : textColorNormal;
        SDL_Color quitTextColor = (selectedMenuItem == 1) ? textColorSelected : textColorNormal;
		SDL_Color level3TextColor = (selectedMenuItem == 2) ? textColorSelected : textColorNormal;
        // **"Play Game" Text Rendering - USE localFont HERE:**
        SDL_Surface* textSurfacePlay = TTF_RenderText_Blended(localFont, "Level 1", playTextColor); // **Use localFont here!**
        if (!textSurfacePlay) { /* Error check - keep it */ }
        SDL_Texture* textTexturePlay = SDL_CreateTextureFromSurface(renderer, textSurfacePlay);
        if (!textTexturePlay) { /* Error check - keep it */ }
        SDL_Rect rectTextPlay;
        SDL_QueryTexture(textTexturePlay, NULL, NULL, &rectTextPlay.w, &rectTextPlay.h);
        rectTextPlay.x = rectButtonPlay.x + (buttonWidth - rectTextPlay.w) / 2;
        rectTextPlay.y = rectButtonPlay.y + (buttonHeight - rectTextPlay.h) / 2;
        SDL_RenderCopy(renderer, textTexturePlay, NULL, &rectTextPlay);
        SDL_FreeSurface(textSurfacePlay);
        SDL_DestroyTexture(textTexturePlay);


        SDL_Surface* textSurfaceQuit = TTF_RenderText_Blended(localFont, "Level 2", quitTextColor); // **Use localFont here!**
        if (!textSurfaceQuit) { /* Error check - keep it */ }
        SDL_Texture* textTextureQuit = SDL_CreateTextureFromSurface(renderer, textSurfaceQuit);
        if (!textTextureQuit) { /* Error check - keep it */ }
        SDL_Rect rectTextQuit;
        SDL_QueryTexture(textTextureQuit, NULL, NULL, &rectTextQuit.w, &rectTextQuit.h);
        rectTextQuit.x = rectButtonQuit.x + (buttonWidth - rectTextQuit.w) / 2;
        rectTextQuit.y = rectButtonQuit.y + (buttonHeight - rectTextQuit.h) / 2;
        SDL_RenderCopy(renderer, textTextureQuit, NULL, &rectTextQuit);
        SDL_FreeSurface(textSurfaceQuit);
        SDL_DestroyTexture(textTextureQuit);

        SDL_Surface* textSurfaceLevel3 = TTF_RenderText_Blended(localFont, "Level 3", level3TextColor); // **Use localFont here!**
        if (!textSurfaceLevel3) { /* Error check - keep it */ }
        SDL_Texture* textTextureLevel3 = SDL_CreateTextureFromSurface(renderer, textSurfaceLevel3);
        if (!textSurfaceLevel3) { /* Error check - keep it */ }
        SDL_Rect rectTextLevel3;
        SDL_QueryTexture(textTextureLevel3, NULL, NULL, &rectTextLevel3.w, &rectTextLevel3.h);
        rectTextLevel3.x = rectButtonLevel3.x + (buttonWidth - rectTextLevel3.w) /2;
        rectTextLevel3.y = rectButtonLevel3.y + (buttonHeight - rectTextLevel3.h) / 2;
        SDL_RenderCopy(renderer, textTextureLevel3, NULL, &rectTextLevel3);
        SDL_FreeSurface(textSurfaceLevel3);
        SDL_DestroyTexture(textTextureLevel3);



    }
        
    TTF_CloseFont(localFont); // **CLOSE the locally loaded font - IMPORTANT!**
    
}