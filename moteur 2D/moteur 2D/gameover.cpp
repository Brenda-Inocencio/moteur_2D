#include "gameover.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

GameOver::GameOver(SDL_Renderer* renderer) {
    TTF_Font* gameOverFont = TTF_OpenFont("OpenSans-VariableFont_wdth,wght.ttf", 28);
    SDL_Color textColor = {255, 255, 255, 255};
    if (!gameOverFont) {
        SDL_Log("Erreur chargement police: %s", SDL_GetError());
    }
    gameOverSurface = TTF_RenderText_Solid(gameOverFont, "You lose", 9, textColor);
    gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);
    SDL_DestroySurface(gameOverSurface);
    if (!gameOverTexture) {
        SDL_Log("Erreur rendu texte: %s", SDL_GetError());
    }

    font = TTF_OpenFont("OpenSans-VariableFont_wdth,wght.ttf", 24);
    if (!font) {
        SDL_Log("Erreur chargement police: %s", SDL_GetError());
    }
    textSurface = TTF_RenderText_Solid(font, "Exit", 4, textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);
    if (!textTexture) {
        SDL_Log("Erreur rendu texte: %s", SDL_GetError());
    }
}

void GameOver::Render(SDL_Renderer* _renderer) {
    buttonRect = {475, 600 , 100, 40};
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(_renderer, &buttonRect);
    if (gameOverTexture) {
        float tw, th;
        SDL_GetTextureSize(gameOverTexture, &tw, &th);
        SDL_FRect textRect = {475, 300, (float)tw, (float)th};
        SDL_RenderTexture(_renderer, gameOverTexture, nullptr, &textRect);
    }
    if (textTexture) {
        float tw, th;
        SDL_GetTextureSize(textTexture, &tw, &th);
        SDL_FRect textRect = {buttonRect.x + 20, buttonRect.y + 5, (float)tw, (float)th};
        SDL_RenderTexture(_renderer, textTexture, nullptr, &textRect);
    }
}

void GameOver::Press(SDL_Renderer* _renderer) {
    buttonRect = {475, 600 , 100, 40};
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(_renderer, &buttonRect);
    if (textTexture) {
        float tw, th;
        SDL_GetTextureSize(textTexture, &tw, &th);
        SDL_FRect textRect = {buttonRect.x + 20, buttonRect.y + 5, (float)tw, (float)th};
        SDL_RenderTexture(_renderer, textTexture, nullptr, &textRect);
    }
}

GameOver::~GameOver() {
    if (gameOverTexture) {
        SDL_DestroyTexture(gameOverTexture);
    }
    if (gameOverSurface) {
        SDL_DestroySurface(gameOverSurface);
    }
    if (textTexture) {
        SDL_DestroyTexture(textTexture);
    }
    if (font) {
        TTF_CloseFont(font);
    }
}