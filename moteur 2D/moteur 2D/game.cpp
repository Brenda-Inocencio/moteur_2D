#include "game.h"
#include "character.h"
#include "block.h"

void Game::Collisions(SDL_Renderer* renderer, float now) {
}

void Game::GameRenderer(bool gameStart, SDL_Renderer* renderer, Character* ch, std::vector<Block*> blocks) {
    if (gameStart) {
        ch->Render(renderer);
        for (Block* bl : blocks) {
            bl->Render(renderer);
        }
    }
}

void Game::Update(float dt, float gameTime, Character* ch, std::vector<SDL_Event> events, std::vector<Block*> blocks) {
    ch->Update(dt, events);
    for (Block* bl : blocks) {
        bl->Update(gameTime);
    }
}