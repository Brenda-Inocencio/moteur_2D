#include "menu.h"
#include <SDL3/SDL.h>
#include "button.h"
#include "background.h"

Menu::Menu() {
    state = CHSTATE_MENU;
}

void Menu::Update(float dt, int winWidth, bool gameStart, bool isGameOver, Background* bg, SDL_Renderer* renderer, Button* exit, Button* start) {
    State newState = state;
    switch (state) {
    case CHSTATE_MENU:
        MenuRenderer(renderer, exit, start);
        if (gameStart) {
            newState = CHSTATE_START;
        }
        break;
    case CHSTATE_START:
        bg->Render(renderer, winWidth);
        if (isGameOver)
        break;
    case CHSTATE_PAUSE:
    case CHSTATE_WIN:
    case CHSTATE_GAME_OVER:

        break;
    }
    
    if (state != newState) {
        state = newState;
    }
}

void Menu::MenuRenderer(SDL_Renderer* renderer, Button* exit, Button* start) {
    exit->Render(renderer);
    start->Render(renderer);
}

