#include "background.h"
#include <SDL3/SDL.h>

Background::Background(std::vector<SDL_Texture*> _textures) {
	textures = _textures;
	texture = _textures[1];
	width = 700;
	height = 768;
}

Background::~Background() {}

void Background::Render(SDL_Renderer* _renderer, int windowWidth, float y_camera, SDL_Texture* texture) {
	if (texture) {
		SDL_FRect rect = {(windowWidth - width) / 2, y_camera, width, height};
		SDL_RenderTexture(_renderer, texture, nullptr, &rect);
	}
}
