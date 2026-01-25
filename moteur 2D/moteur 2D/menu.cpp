#include "menu.h"
#include <SDL3/SDL.h>
#include "button.h"
#include "win.h"

Menu::Menu() {
    state = CHSTATE_MENU;
}

void Menu::Update(float dt, bool& gameStart) {
    State newState = state;
    switch (state) {
    case CHSTATE_MENU:
        if (gameStart) {
            newState = CHSTATE_START;
        }
        break;
    case CHSTATE_START:
        break;
    case CHSTATE_PAUSE:
        break;
    case CHSTATE_WIN:
        break;
    case CHSTATE_GAME_OVER:
        gameStart = false;
        break;
    }
    
    if (state != newState) {
        state = newState;
    }
}

void Menu::Render(SDL_Renderer* renderer, Button* exit, Button* start, Button* gameOver, Win* win) {
    switch (state) {
    case CHSTATE_MENU:
        MenuRenderer(renderer, exit, start);
        break;
    case CHSTATE_START:
        break;
    case CHSTATE_PAUSE:
        break;
    case CHSTATE_WIN:
        MenuWinRenderer(renderer, win, exit);
        break;
    case CHSTATE_GAME_OVER:
        MenuGameOverRenderer(renderer, gameOver);
        break;
    }
}

void Menu::MenuRenderer(SDL_Renderer* renderer, Button* exit, Button* start) {
    exit->Render(renderer);
    start->Render(renderer);
}

void Menu::MenuGameOverRenderer(SDL_Renderer* renderer, Button* gameOver) {
    gameOver->Render(renderer);
}

void Menu::MenuWinRenderer(SDL_Renderer* renderer, Win* win, Button* exit) {
    win->Render(renderer);
    win->End(renderer);
    exit->Render(renderer);
}

void Menu::SetGameOver() {
    state = CHSTATE_GAME_OVER;
}

void Menu::SetWin() {
    state = CHSTATE_WIN;
}

