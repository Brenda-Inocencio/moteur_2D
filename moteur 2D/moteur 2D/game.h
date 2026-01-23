#pragma once

#include <SDL3/SDL.h>
#include <vector>

struct SDL_Renderer;
class Character;
class Block;
class Background;
class Menu;
class Button;

class Game {
	float elder_scrolls; //Euh actually c est une ref a la licence elder scrolls mais en vrai la variable c est pour le debut du scrolling.
public:
	void Collisions(float now, SDL_Renderer* renderer, std::vector<Block*>& blocks, Character& ch);
	void GameRenderer(bool gameStart, float winWidth, SDL_Renderer* renderer, Character& ch,
		std::vector<Block*>& blocks, Background& bg, Menu& menu, Button* exit, Button* start, Button* gameOver, 
		std::vector<SDL_Texture*>& gridTextures);
	void Update(float dt, float gameTime, bool& gameStart, Character& ch, 
		std::vector<SDL_Event> events, std::vector<Block*>& blocks, Menu& menu);
};
