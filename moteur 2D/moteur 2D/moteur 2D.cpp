#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include "background.h"
#include "block.h"

int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int windowWidth = 1024;
    int windowHeight = 768;

    SDL_SetAppMetadata("SDL Test", "1.0", "com.platformer.test-sdl");
    if (!SDL_Init(SDL_INIT_VIDEO))
        return 1;

    if (!SDL_CreateWindowAndRenderer("platformer", windowWidth, windowHeight, 0,
        &window, &renderer))
        return 1;

    if (!SDL_SetRenderVSync(renderer, 1)) {
        SDL_Log("Impossible d'activer le VSync : %s", SDL_GetError());
    }

    if (TTF_Init() < 0) {
        SDL_Log("Erreur TTF_Init: %s", SDL_GetError());
    }

    SDL_SetRenderLogicalPresentation(renderer, windowWidth, windowHeight,
        SDL_LOGICAL_PRESENTATION_LETTERBOX);

    Background bg(renderer);
    std::vector<Block*> blocks;

    bool isGameOver = false;
    bool isWin = false;
    bool gameStart = false;
    bool isPaused = false;
    bool keepGoing = true;
    float gameTime = 0;
    float timePrev = 0;
    float timeStart = 0;
    float cooldown = 0;
    while (keepGoing) {
        float now = float(SDL_GetTicks()) / 1000.0f;
        float dt = now - timePrev;
        timePrev = now;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                keepGoing = false;
            
        }
        SDL_RenderClear(renderer);
        bg.Render(renderer, windowWidth);
        timeStart = now;
        gameStart = now - timeStart;
        if (cooldown >= 5) {
            Block* block = new Block(renderer);
            blocks.push_back(block);
        }
        while (true) {
            for (int i = 0; i < blocks.size(); i++) {
                blocks[i]->Render(renderer);
                blocks[i]->Update(gameStart, dt);
            }
        }

        /*if (isWin) {
        bg.Render(renderer, windowWidth);
            if (isLvl1) {
                menu.MenuNextLevelRenderer(renderer, win, play);
            }
            else {
                menu.MenuWinRenderer(renderer, win, exit);
            }
            score->Render(renderer);
        }
        else if (isGameOver) {
        bg.Render(renderer, windowWidth);
            menu.MenuGameOverRenderer(renderer, gameOver);
            score->Render(renderer);
            gameStart = false;
        }
        else if (isPaused) {
        bg.Render(renderer, windowWidth);+54
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
    blocks.clear();
    SDL_Quit();
    TTF_Quit();
    return 0;
}
