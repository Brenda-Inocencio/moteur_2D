#pragma once

#include <SDL3/SDL.h>

class Background;
class Character;
class Block;
class Button;
class Win;

class Menu {
	enum State {
		CHSTATE_MENU,
		CHSTATE_START,
		CHSTATE_PAUSE,
		CHSTATE_WIN,
		CHSTATE_GAME_OVER
	} state;
public:
	Menu();
	void Update(float dt, bool& gameStart); //TODO: make render version 
	void Render(SDL_Renderer* renderer, Button* exit, Button* start, Button* gameOver, Background& bg, int winWidth);
	void MenuRenderer(SDL_Renderer* renderer, Button* exit, Button* start); // Render the start menu
	void MenuGameOverRenderer(SDL_Renderer* renderer, Button* gameOver); //Render the game over screen
	void SetGameOver(); //Change state to game over
};