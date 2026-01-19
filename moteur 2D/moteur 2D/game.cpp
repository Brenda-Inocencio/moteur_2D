#include "game.h"
#include "character.h"
#include "block.h"

void Game::Collisions(float now, bool& isGameOver, SDL_Renderer* renderer, std::vector<Block*>& blocks) {
    for (Block* bl : blocks) {
        float bx = bl->pos_x;
        float by = bl->pos_y + 38;

        for (int i = 0; i < blocks.size(); i++) {
            if (bl != blocks[i]) {
                if (blocks[i]->pos_x == bx) {
                    if (by == blocks[i]->pos_y && blocks[i]->collision) {
                        if (!bl->collision) {
                            bl->collision = true;
                        }
                    }
                }
            }
        }
        if (bl->collision && bl->pos_y >= bl->pos_y - (38 * 16)) {
            isGameOver = true;
        }
    }
}

void Game::GameRenderer(bool gameStart, SDL_Renderer* renderer, Character* ch, std::vector<Block*>& blocks) {
    if (gameStart) {
        ch->Render(renderer);
        for (Block* bl : blocks) {
            bl->Render(renderer);
        }
    }
}

void Game::Update(float dt, float gameTime, Character* ch, std::vector<SDL_Event> events, std::vector<Block*>& blocks) {
    ch->Update(dt, events);
    for (Block* bl : blocks) {
        bl->Update(gameTime);
    }
}