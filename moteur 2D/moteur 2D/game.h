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
public:
	void Collisions(float now, bool& isGameOver, SDL_Renderer* renderer, std::vector<Block*>& blocks, Character& ch);
	void GameRenderer(bool gameStart, float winWidth, SDL_Renderer* renderer, Character& ch,
		std::vector<Block*>& blocks, Background& bg, Menu& menu, Button* exit, Button* start, Button* gameOver);
	void Update(float dt, float gameTime, bool& gameStart, bool& gameOver, Character& ch, 
		std::vector<SDL_Event> events, std::vector<Block*>& blocks, Menu& menu);
};
