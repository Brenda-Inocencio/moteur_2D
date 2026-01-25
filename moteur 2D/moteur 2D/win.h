#pragma once
#include "button.h"

class Win : public Button {
    SDL_Surface* winSurface;
    SDL_Texture* winTexture;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Surface* endSurface;
    SDL_Texture* endTexture;
public:
    Win(SDL_Renderer* _renderer);
    ~Win();
    void NextLevel(SDL_Renderer* _renderer);
    void End(SDL_Renderer* _renderer);
    void Render(SDL_Renderer* renderer) override;
    void Press(SDL_Renderer* renderer) override;
};