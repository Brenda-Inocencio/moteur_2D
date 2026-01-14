#pragma once
#include "SDL3/SDL.h"

struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;
struct TTF_Font;
struct SDL_FRect;

class Button {
protected:
	TTF_Font* font;
	SDL_Surface* textSurface;
	SDL_Texture* textTexture;
public:
	bool isPressed;
	SDL_FRect buttonRect;
	virtual void Render(SDL_Renderer* _renderer) = 0;
	virtual void Press(SDL_Renderer* _renderer) = 0;
};

