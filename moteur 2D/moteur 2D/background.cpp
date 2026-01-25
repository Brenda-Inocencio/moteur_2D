#include "background.h"
#include <SDL3/SDL.h>

Background::Background(SDL_Texture* _texture) {
	texture = _texture;
	width = 700;
	height = 768;
}

Background::~Background() {}

void Background::Render(SDL_Renderer* _renderer, int windowWidth, float y_camera) {
	if (texture) {
		SDL_FRect rect = {(windowWidth - width) / 2, y_camera, width, height};
		SDL_RenderTexture(_renderer, texture, nullptr, &rect);
	}
}
