#include "game.h"
#include "character.h"
#include "block.h"
#include "background.h"
#include "menu.h"
#include "button.h"

void Game::Collisions(float now, bool& isGameOver, SDL_Renderer* renderer, std::vector<Block*>& blocks, Character& ch) {
    for (Block* bl : blocks) {
        float bx = bl->GetPosX(); 
        float by = bl->GetBottomY();
        float cx = ch.GetPosX();          
        float cy = ch.GetPosY();

     

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

void Game::GameRenderer(bool gameStart, float winWidth, SDL_Renderer* renderer, Character& ch, 
    std::vector<Block*>& blocks, Background& bg, Menu& menu, Button* exit, Button* start, Button* gameOver) {
    menu.Render(renderer, exit, start, gameOver, bg, winWidth);
    if (gameStart) {
        ch.Render(renderer);
        for (Block* bl : blocks) {
            bl->Render(renderer);
        }
    }
}

void Game::Update(float dt, float gameTime, bool& gameStart, bool& gameOver, Character& ch, 
    std::vector<SDL_Event> events, std::vector<Block*>& blocks, Menu& menu) {
    menu.Update(dt, gameStart, gameOver);
    ch.Update(dt, gameTime, events, blocks, menu);
    for (Block* bl : blocks) {
        bl->Update(gameTime);
    }
}