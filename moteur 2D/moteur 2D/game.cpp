#include "game.h"
#include "character.h"
#include "block.h"
#include "background.h"
#include "menu.h"
#include "button.h"

void Game::Collisions(float now, SDL_Renderer* renderer, std::vector<Block*>& blocks, Character& ch) {
    for (Block* bl : blocks) {
        float bx = bl->GetPosX(); 
        float by = bl->GetBottomY();
        float cx = ch.GetPosX();          
        float cy = ch.GetPosY();

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

void Game::GameRenderer(bool gameStart, int winWidth, SDL_Renderer* renderer, Character& ch, 
    std::vector<Block*>& blocks, Background& bg, Menu& menu, Button* exit, Button* start, Button* gameOver, 
    std::vector<SDL_Texture*>& gridTextures) {
    menu.Render(renderer, exit, start, gameOver);
    if (gameStart) {
        elder_scrolls = 344;
        float y_camera = std::max(0.f, elder_scrolls - ch.GetPosY());
        bg.Render(renderer, winWidth, y_camera, gridTextures[1]);
        /*if (y_camera > 0) {
            bg.Render(renderer, winWidth, y_camera, gridTextures[2]);
        }//y_camera - hauteur*/
        ch.Render(renderer);
        for (Block* bl : blocks) {
            bl->Render(renderer, y_camera);
        }
    }
}

void Game::Update(float dt, float gameTime, bool& gameStart, Character& ch, 
    std::vector<SDL_Event> events, std::vector<Block*>& blocks, Menu& menu) {
    menu.Update(dt, gameStart);
    ch.Update(dt, gameTime, events, blocks, menu);
    for (Block* bl : blocks) {
        bl->Update(gameTime);
    }
}