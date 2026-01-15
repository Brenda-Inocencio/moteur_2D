#pragma once
#include "button.h"

class Start : public Button {
public:

    Start(SDL_Renderer* renderer);
    ~Start();
    void Render(SDL_Renderer* _renderer) override;
    void Press(SDL_Renderer* _renderer) override;
};