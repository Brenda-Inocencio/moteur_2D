#include "exit.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

Exit::Exit(SDL_Renderer* renderer) {
    isPressed = false;
    font = TTF_OpenFont("OpenSans-VariableFont_wdth,wght.ttf", 24);
    if (!font) {
        SDL_Log("Erreur chargement police: %s", SDL_GetError());
    }

    SDL_Color textColor = {255, 255, 255, 255};
    textSurface = TTF_RenderText_Solid(font, "Exit", 4, textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);
    if (!textTexture) {
        SDL_Log("Erreur rendu texte: %s", SDL_GetError());
    }
}

void Exit::Render(SDL_Renderer* _renderer) {
    buttonRect = {475, 600 , 100, 40};
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(_renderer, &buttonRect);
    if (textTexture) {
        float tw, th;
        SDL_GetTextureSize(textTexture, &tw, &th);
        SDL_FRect textRect = {buttonRect.x + 30, buttonRect.y + 5, (float)tw, (float)th};
        SDL_RenderTexture(_renderer, textTexture, nullptr, &textRect);
    }
}

void Exit::Press(SDL_Renderer* _renderer) {
    isPressed = true;
    buttonRect = {475, 600 , 100, 40};
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(_renderer, &buttonRect);
    if (textTexture) {
        float tw, th;
        SDL_GetTextureSize(textTexture, &tw, &th);
        SDL_FRect textRect = {buttonRect.x + 30, buttonRect.y + 5, (float)tw, (float)th};
        SDL_RenderTexture(_renderer, textTexture, nullptr, &textRect);
    }
}

Exit::~Exit() {
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
    }
    if (font) {
        TTF_CloseFont(font);
    }
}