#pragma once
#include "button.h"


class Exit : public Button {
public:
    Exit(SDL_Renderer* _renderer);
    ~Exit();
    void Render(SDL_Renderer* renderer) override;
    void Press(SDL_Renderer* renderer) override;
};