#pragma once

#include <SDL3/SDL.h>
#include <vector>

struct SDL_Renderer;
class Character;
class Block;

class Game {
public:
	void Collisions(SDL_Renderer* renderer, float now);
	void GameRenderer(bool gameStart, SDL_Renderer* renderer, Character* ch, std::vector<Block*> blocks);
	void Update(float dt, float gameTime, Character* ch, std::vector<SDL_Event> events, std::vector<Block*> blocks);
};
