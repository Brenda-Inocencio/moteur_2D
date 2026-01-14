#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include "background.h"
#include "block.h"
#include "character.h"

#define WORLD_WIDTH 10
#define WORLD_HEIGHT 50
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_SetAppMetadata("SDL Test", "1.0", "games.anakata.test-sdl");
    if (!SDL_Init(SDL_INIT_VIDEO))
        return 1;

    if (!SDL_CreateWindowAndRenderer("platformer", 1024, 768, 0,
        &window, &renderer))
        return 1;

    if (!SDL_SetRenderVSync(renderer, 1)) {
        SDL_Log("Impossible d'activer le VSync : %s", SDL_GetError());
    }

    if (TTF_Init() < 0) {
        SDL_Log("Erreur TTF_Init: %s", SDL_GetError());
    }

    SDL_SetRenderLogicalPresentation(renderer, 1024, 768,
        SDL_LOGICAL_PRESENTATION_LETTERBOX);

    
    Background bg(renderer);
    Character ch(renderer);
    SDL_Texture* blockTexture = IMG_LoadTexture(renderer, "block.png");
    if (!blockTexture) {
        SDL_Log("Erreur de chargement %s", SDL_GetError());
    }
    Block* bl = new Block(blockTexture);
//    std::vector<Block*> blocks;
    bool isGameOver = false;
    bool isWin = false;
    bool gameStart = false;
    bool isPaused = false;
    bool keepGoing = true;
    bool isLeft = false;
    bool isRight = false;
    bool isJump = false;
    bool isGrab = false;
    bool isSwapGrid = false;
    float cooldown = 0;
    float gameTime = 0;
    float timePrev = 0;
    float timeStart = 0;
    while (keepGoing) {
        float now = float(SDL_GetTicks()) / 1000.0f;
        float dt = now - timePrev;
        timePrev = now;
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                keepGoing = false;
            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_Z) {
                    isJump = true;
                }
                if (event.key.key == SDLK_Q) {
                    isLeft = true;
                }
                if (event.key.key == SDLK_D) {
                    isRight = true;
                }
                if (event.key.key == SDLK_S) {
                    isGrab = !isGrab;
                }
                if (event.key.key == SDLK_SPACE) {
                    isSwapGrid = true;
                }
            }
            if (event.type == SDL_EVENT_KEY_UP) {
                if (event.key.key == SDLK_Z) {
                    isJump = false;
                }
                if (event.key.key == SDLK_Q) {
                    isLeft = false;
                }
                if (event.key.key == SDLK_D) {
                    isRight = false;
                }
                if (event.key.key == SDLK_SPACE) {
                    isSwapGrid = false;
                }
            }
        }
        SDL_RenderClear(renderer);
        bg.Render(renderer);
        ch.Render(renderer);
        bl->Render(renderer);
        /*for (int i = 0; i < blocks.size(); i++) {
            blocks[i]->Render(renderer);
        }*/
        /*if (isWin) {
        bg.Render(renderer);
            if (isLvl1) {
                menu.MenuNextLevelRenderer(renderer, win, play);
            }
            else {
                menu.MenuWinRenderer(renderer, win, exit);
            }
            score->Render(renderer);
        }
        else if (isGameOver) {
        bg.Render(renderer);
            menu.MenuGameOverRenderer(renderer, gameOver);
            score->Render(renderer);
            gameStart = false;
        }
        else if (isPaused) {
        bg.Render(renderer);+54
            menu.MenuPauseRenderer(renderer, pause, play);
        }
        else if (gameStart) {
            gameTime = now - timeStart;
            if (isLvl1) {
                game.Update(dt, ship, shoots, level_1, up, right, left, down, isUp,
                    isRight, isLeft, isDown, gameTime, shootCooldown, canShoot);
                game.Collisions(renderer, shoots, level_1->ennemies, ship, gameTime, score,
                    isGameOver, isWin);
                game.GameRenderer(renderer, ship, shoots, *level_1);
            }
            else {
                game.Update(dt, ship, shoots, level_2, up, right, left, down, isUp,
                    isRight, isLeft, isDown, gameTime, shootCooldown, canShoot);
                game.Collisions(renderer, shoots, level_2->ennemies, ship, gameTime, score,
                    isGameOver, isWin);
                game.GameRenderer(renderer, ship, shoots, *level_2);
            }
        }
        else {
            menu.MenuRenderer(renderer, exit, start);
        }*/

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    //for (int i = 0; i < blocks.size(); i++) 
    {
        delete bl; bl = nullptr;
    }
    //blocks.clear();
    SDL_Quit();
    TTF_Quit();
    return 0;
}