#include "character.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Character::Character(SDL_Renderer* _renderer) {
	texture = IMG_LoadTexture(_renderer, "character_grabing_object.png");
	if (!texture) {
		SDL_Log("L'image elle a pas trop marché: %s", SDL_GetError());
	}
}

Character::~Character() {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
}

void Character::Render(SDL_Renderer* _renderer) {
	if (texture) {
		SDL_FRect rect = {692, 610, 100, 145};
		SDL_RenderTexture(_renderer, texture, nullptr, &rect);
	}
}
