#include "background.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Background::Background(SDL_Renderer* _renderer) {
	texture = IMG_LoadTexture(_renderer, "grid.png");
	if (!texture) {
		SDL_Log("Erreur chargement image: %s", SDL_GetError());
	}
}

Background::~Background() {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
}

void Background::Render(SDL_Renderer* _renderer) {
	if (texture) {
		SDL_FRect rect = {162, 0, 700, 768};
		SDL_RenderTexture(_renderer, texture, nullptr, &rect);
	}
}