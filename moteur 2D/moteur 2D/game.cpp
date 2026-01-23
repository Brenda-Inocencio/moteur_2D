#include "game.h"
#include "character.h"
#include "block.h"

void Game::Collisions(float now, bool& isGameOver, SDL_Renderer* renderer, std::vector<Block*>& blocks, Character& ch) {
    for (Block* bl : blocks) {
        float bx = bl->GetPosX(); 
        float by = bl->GetBottomY();
        float cx = ch.GetPosX();            //TODO: faire fonctionner la collision
        float cy = ch.GetPosY();

        if (!(bx < cx || bl->GetRightX() > ch.GetRightX()) && !bl->collision) { // collision avec les blocs du haut
            if (by >= cy) {
                isGameOver = true;
            }
        }

        if (bl->collision && bl->GetPosY() <= bl->GetPosY() - (38 * 16)) {
            isGameOver = true;
        }

        for (int i = 0; i < blocks.size(); i++) {
            if (bl != blocks[i]) {
                if (blocks[i]->GetPosX() == bx) {
                    if (by == blocks[i]->GetPosY() && blocks[i]->collision) {
                        if (!bl->collision) {
                            bl->collision = true;
                        }
                    }
                }
            }
        }
    }
}

void Game::GameRenderer(bool gameStart, SDL_Renderer* renderer, Character& ch, std::vector<Block*>& blocks) {
    if (gameStart) {
        ch.Render(renderer);
        for (Block* bl : blocks) {
            bl->Render(renderer);
        }
    }
}

void Game::Update(float dt, float gameTime, Character& ch, std::vector<SDL_Event> events, std::vector<Block*>& blocks) {
    ch.Update(dt, gameTime, events, blocks);
    for (Block* bl : blocks) {
        bl->Update(gameTime);
    }
}