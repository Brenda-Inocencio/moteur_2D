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
#include "win.h"

#define WORLD_WIDTH 10
#define WORLD_HEIGHT 100
#define WINDOW_WIDTH 1024 
#define WINDOW_HEIGHT 768
#define BACKGROUND_MAX_IMAGE 4
#define CHARACTER_MAX_IMAGE 7

const char* characterImage[CHARACTER_MAX_IMAGE] {
     "character_static.png",
     "character_walking_left.png",
     "character_walking_right.png",
     "character_jumping_left.png",
     "character_jumping_right.png",
     "character_falling_left.png",
     "character_falling_right.png"
};

const char* backgroundImage[BACKGROUND_MAX_IMAGE]{
     "grid.png",
     "grid_for_scrolling.png",
     "pipes.png",
     "background.png"
};

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

    if (!TTF_Init()) {
        SDL_Log("Erreur TTF_Init: %s", SDL_GetError());
    }

    SDL_SetRenderLogicalPresentation(renderer, WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_LOGICAL_PRESENTATION_LETTERBOX);

    Game game;
    std::vector<SDL_Texture*> characterTextures = {nullptr};
    SDL_Texture* blockTexture = IMG_LoadTexture(renderer, "block.png");
    std::vector<Block*> blocks;
    std::vector<SDL_Texture*> backgroundTextures = {nullptr};
    std::vector<Background*> bgs;

    for (int i = 0; i < BACKGROUND_MAX_IMAGE; i++) {
        backgroundTextures.push_back(IMG_LoadTexture(renderer, backgroundImage[i]));
        bgs.push_back(new Background(backgroundTextures[i+1]));
    }

    for (int i = 0; i < CHARACTER_MAX_IMAGE; i++) {
        characterTextures.push_back(IMG_LoadTexture(renderer, characterImage[i]));
    }
    Character ch(characterTextures);

    Button* exit = new Exit(renderer);
    Button* start = new Start(renderer);
    Button* gameOver = new GameOver(renderer);
    Win* win = new Win(renderer);
    Menu menu;

    std::vector<SDL_Event> events;

    bool gameStart = false;
    bool keepGoing = true;

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
                else {
                    if (mx >= exit->buttonRect.x && mx <= exit->buttonRect.x + exit->buttonRect.w &&
                        my >= exit->buttonRect.y && my <= exit->buttonRect.y + exit->buttonRect.h) {
                        if (event.type != SDL_EVENT_MOUSE_BUTTON_UP) {
                            exit->Press(renderer);
                            SDL_RenderPresent(renderer);
                            keepGoing = false;
                        }
                    }
                }
            }
            events.push_back(event);
        }
            
        SDL_RenderClear(renderer);
        if (gameStart) {
            gameTime = now - timeStart;
            if (gameTime - cooldownSpawn >= 1){
                blocks.push_back(new Block(blockTexture));
                cooldownSpawn = gameTime;
            }
            game.Update(dt, gameTime, gameStart, ch, events, blocks, menu);
            game.Collisions(gameTime, renderer, blocks, ch);
            game.GameRenderer(gameStart, WINDOW_WIDTH, renderer, ch, blocks, bgs, menu, exit, start, gameOver, backgroundTextures, win);
        }
        else {
            menu.Render(renderer, exit, start, gameOver, win);
        }
        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    delete start; start = nullptr;
    delete exit; exit = nullptr;
    delete gameOver; gameOver = nullptr;

    for (int i = 0; i < backgroundTextures.size(); i++) {
        if (backgroundTextures[i]) {
            SDL_DestroyTexture(backgroundTextures[i]);
        }
    }
    backgroundTextures.clear();

    for (int i = 0; i < bgs.size(); i++) {
        if (bgs[i]) {
            delete bgs[i]; bgs[i] = nullptr;
        }
    }
    bgs.clear();

    for (int i = 0; i < characterTextures.size(); i++) {
        if (characterTextures[i]) {
            SDL_DestroyTexture(characterTextures[i]);
        }
    }
    characterTextures.clear();

    for (int i = 0; i < blocks.size(); i++) {
        delete blocks[i]; blocks[i] = nullptr;
    }
    blocks.clear();
    SDL_Quit();
    TTF_Quit();
    return 0;
}