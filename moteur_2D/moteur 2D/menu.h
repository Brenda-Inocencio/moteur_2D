#pragma once

struct SDL_Renderer;
class Background;
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
	void Update(float dt, int winWidth, Background bg, SDL_Renderer* renderer, Button* exit, Button* start);
	void MenuRenderer(SDL_Renderer* renderer, Button* exit, Button* start);
};