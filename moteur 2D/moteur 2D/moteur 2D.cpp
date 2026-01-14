#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include "background.h"
#include "block.h"
#include "menu.h"
#include "button.h"
#include "exit.h"
#include "start.h"

#define WINDOW_WIDTH 1024 
#define WINDOW_HEIGHT 768

int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_SetAppMetadata("SDL Test", "1.0", "com.platformer.test-sdl");
    if (!SDL_Init(SDL_INIT_VIDEO))
        return 1;

    if (!SDL_CreateWindowAndRenderer("platformer", WINDOW_WIDTH, WINDOW_HEIGHT, 0,
        &window, &renderer))
        return 1;

    if (!SDL_SetRenderVSync(renderer, 1)) {
        SDL_Log("Impossible d'activer le VSync : %s", SDL_GetError());
    }

    if (TTF_Init() < 0) {
        SDL_Log("Erreur TTF_Init: %s", SDL_GetError());
    }

    SDL_SetRenderLogicalPresentation(renderer, WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_LOGICAL_PRESENTATION_LETTERBOX);

    Background bg(renderer);
    Button* exit = new Exit(renderer);
    Button* start = new Start(renderer);
    Menu menu;

    std::vector<Block*> blocks;
    bool gameStart = false;
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
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                float mx = event.button.x;
                float my = event.button.y;
                if (!gameStart) {
                    if (mx >= exit->buttonRect.x && mx <= exit->buttonRect.x + exit->buttonRect.w &&
                        my >= exit->buttonRect.y && my <= exit->buttonRect.y + exit->buttonRect.h) {
                        if (event.type != SDL_EVENT_MOUSE_BUTTON_UP) {
                            exit->Press(renderer);
                            SDL_RenderPresent(renderer);
                            keepGoing = false;
                        }
                    }
                    if (mx >= start->buttonRect.x && mx <= start->buttonRect.x + start->buttonRect.w &&
                        my >= start->buttonRect.y && my <= start->buttonRect.y + start->buttonRect.h) {
                        if (event.type != SDL_EVENT_MOUSE_BUTTON_UP) {
                            start->Press(renderer);
                            SDL_RenderPresent(renderer);
                            gameStart = true;
                            timeStart = now;
                        }
                    }
                }
            }
        }
        SDL_RenderClear(renderer);
        //bg.Render(renderer, WINDOW_WIDTH);
        menu.Update(dt, WINDOW_WIDTH, bg, renderer, exit, start);
        
        //gameTime = now - timeStart;
        /*
        game.Update(dt, ship, shoots, level_2, up, right, left, down, isUp,
            isRight, isLeft, isDown, gameTime, shootCooldown, canShoot);
        game.Collisions(renderer, shoots, level_2->ennemies, ship, gameTime, score,
            isGameOver, isWin);
        game.GameRenderer(renderer, ship, shoots, *level_2);
        */

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    delete start; start = nullptr;
    delete exit; exit = nullptr;
    for (int i = 0; i < blocks.size(); i++) {
        delete blocks[i]; 
        blocks[i] = nullptr;
    }
    blocks.clear();
    SDL_Quit();
    TTF_Quit();
    return 0;
}
