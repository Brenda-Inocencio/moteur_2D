#pragma once
#include "button.h"

class GameOver : public Button {
    SDL_Surface* gameOverSurface;
    SDL_Texture* gameOverTexture;
public:
    GameOver(SDL_Renderer* _renderer);
    ~GameOver();
    void Render(SDL_Renderer* renderer) override;
    void Press(SDL_Renderer* renderer) override;
};