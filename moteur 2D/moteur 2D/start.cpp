#include "start.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

Start::Start(SDL_Renderer* renderer) {
    isPressed = false;
    font = TTF_OpenFont("OpenSans-VariableFont_wdth,wght.ttf", 24);
    if (!font) {
        SDL_Log("Erreur chargement police: %s", SDL_GetError());
    }

    SDL_Color textColor = {255, 255, 255, 255};
    textSurface = TTF_RenderText_Solid(font, "Start", 5, textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);
    if (!textTexture) {
        SDL_Log("Erreur rendu texte: %s", SDL_GetError());
    }
}

void Start::Render(SDL_Renderer* _renderer) {
    buttonRect = {475, 525, 100, 40};
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(_renderer, &buttonRect);
    if (textTexture) {
        float tw, th;
        SDL_GetTextureSize(textTexture, &tw, &th);
        SDL_FRect dst = {buttonRect.x + 25, buttonRect.y + 5, (float)tw, (float)th};
        SDL_RenderTexture(_renderer, textTexture, nullptr, &dst);
    }
}

void Start::Press(SDL_Renderer* _renderer) {
    isPressed = true;
    buttonRect = {475, 525, 100, 40};
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(_renderer, &buttonRect);
    if (textTexture) {
        float tw, th;
        SDL_GetTextureSize(textTexture, &tw, &th);
        SDL_FRect textRect = {buttonRect.x + 25, buttonRect.y + 5, (float)tw, (float)th};
        SDL_RenderTexture(_renderer, textTexture, nullptr, &textRect);
    }
}

Start::~Start() {
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
    }
    if (font) {
        TTF_CloseFont(font);
    }
}