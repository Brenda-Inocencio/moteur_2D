#include "win.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

Win::Win(SDL_Renderer* renderer) {
    TTF_Font* winFont = TTF_OpenFont("OpenSans-VariableFont_wdth,wght.ttf", 28);
    SDL_Color textColor = {255, 255, 255, 255};
    if (!winFont) {
        SDL_Log("Erreur chargement police: %s", SDL_GetError());
    }
    winSurface = TTF_RenderText_Solid(winFont, "You win", 8, textColor);
    winTexture = SDL_CreateTextureFromSurface(renderer, winSurface);
    SDL_DestroySurface(winSurface);
    if (!winTexture) {
        SDL_Log("Erreur rendu texte: %s", SDL_GetError());
    }
    surface = TTF_RenderText_Solid(winFont, "You move up to the next level", 30, textColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    if (!texture) {
        SDL_Log("Erreur rendu texte: %s", SDL_GetError());
    }
    endSurface = TTF_RenderText_Solid(winFont, "Congratulations", 16, textColor);
    endTexture = SDL_CreateTextureFromSurface(renderer, endSurface);
    SDL_DestroySurface(endSurface);
    if (!endTexture) {
        SDL_Log("Erreur rendu texte: %s", SDL_GetError());
    }
}

void Win::NextLevel(SDL_Renderer* _renderer) {
    if (texture) {
        float tw, th;
        SDL_GetTextureSize(texture, &tw, &th);
        SDL_FRect textRect = {400, 400, (float)tw, (float)th};
        SDL_RenderTexture(_renderer, texture, nullptr, &textRect);
    }
}
void Win::End(SDL_Renderer* _renderer) {
    if (endTexture) {
        float tw, th;
        SDL_GetTextureSize(endTexture, &tw, &th);
        SDL_FRect textRect = {400, 400, (float)tw, (float)th};
        SDL_RenderTexture(_renderer, endTexture, nullptr, &textRect);
    }
}

void Win::Render(SDL_Renderer* _renderer) {
    if (winTexture) {
        float tw, th;
        SDL_GetTextureSize(winTexture, &tw, &th);
        SDL_FRect textRect = {475, 300, (float)tw, (float)th};
        SDL_RenderTexture(_renderer, winTexture, nullptr, &textRect);
    }
}

void Win::Press(SDL_Renderer* _renderer) {
}

Win::~Win() {
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
    }
    if (font) {
        TTF_CloseFont(font);
    }
}