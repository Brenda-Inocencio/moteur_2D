#pragma once

#include <SDL3/SDL.h>
#include <vector>

struct SDL_Renderer;
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
	void Update(float dt, int winWidth, bool gameStart, Background* bg, SDL_Renderer* renderer, Button* exit, Button* start);
	void MenuRenderer(SDL_Renderer* renderer, Button* exit, Button* start);
};