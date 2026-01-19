#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include "game.h"
#include "background.h"
#include "block.h"
#include "character.h"
#include "menu.h"
#include "button.h"
#include "exit.h"
#include "start.h"
#include "gameover.h"

#define WORLD_WIDTH 10
#define WORLD_HEIGHT 100
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

    Game game;
    Background* bg = new Background(renderer);
    Character ch(renderer);
    SDL_Texture* blockTexture = IMG_LoadTexture(renderer, "block.png");
    if (!blockTexture) {
        SDL_Log("Erreur de chargement %s", SDL_GetError());
    }
    std::vector<Block*> blocks;

    Button* exit = new Exit(renderer);
    Button* start = new Start(renderer);
    Button* gameOver = new GameOver(renderer);
    Menu menu;
    std::vector<SDL_Event> events;

    bool isWin = false;
    bool isPaused = false;

    bool gameStart = false;
    bool isGameOver = false;
    bool keepGoing = true;
    bool canSpawn = true;

    float gameTime = 0;
    float timePrev = 0;
    float timeStart = 0;
    float cooldownSpawn = 0;
    while (keepGoing) {
        float now = float(SDL_GetTicks()) / 1000.0f;
        float dt = now - timePrev;
        timePrev = now;

        SDL_Event event;
        events.clear();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                keepGoing = false;
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                float mx = event.button.x;
                float my = event.button.y;
                if (isGameOver) {
                    if (mx >= exit->buttonRect.x && mx <= exit->buttonRect.x + exit->buttonRect.w &&
                        my >= exit->buttonRect.y && my <= exit->buttonRect.y + exit->buttonRect.h) {
                        if (event.type != SDL_EVENT_MOUSE_BUTTON_UP) {
                            exit->Press(renderer);
                            SDL_RenderPresent(renderer);
                            keepGoing = false;
                        }
                    }
                }
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
            events.push_back(event);
        }
            
        SDL_RenderClear(renderer);

        menu.Update(dt, WINDOW_WIDTH, gameStart, isGameOver, bg, renderer, exit, start, gameOver);
        if (gameStart) {
            gameTime = now - timeStart;
            if (gameTime - cooldownSpawn >= 1){
                blocks.push_back(new Block(blockTexture));
                cooldownSpawn = gameTime;
            }
            game.Update(dt, gameTime, ch, events, blocks);
            game.Collisions(gameTime, isGameOver, renderer, blocks, ch, keepGoing);
            game.GameRenderer(gameStart, renderer, ch, blocks);
        }
        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    delete start; start = nullptr;
    delete exit; exit = nullptr;
    delete gameOver; gameOver = nullptr;
    delete bg; bg = nullptr;
    for (int i = 0; i < blocks.size(); i++) {
        delete blocks[i]; blocks[i] = nullptr;
    }
    blocks.clear();
    SDL_Quit();
    TTF_Quit();
    return 0;
}