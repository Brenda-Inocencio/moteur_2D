#include "block.h"
#include <SDL3/SDL.h>
#include <random>

//hauteur = 38 
//largeur = 51.5
Block::Block(SDL_Texture* _texture) {
	cooldown = 0;
	pos_x = GetRandomNumber(0, 9);
	pos_y = 642 - (38 * 16);
	blockType = 0; // O = 1, I = 2, Z = 3, T = 4, L = 5
	direction = 0;
	texture = _texture;
}

Block::~Block() {

}

void Block::Render(SDL_Renderer* _renderer) {
	if (texture) {
		SDL_FRect rect = {225 + (pos_x * 51.5), pos_y, 110, 140};
		SDL_RenderTexture(_renderer, texture, nullptr, &rect);
	}
}

int Block::GetRandomNumber(int min, int max) {
	std::random_device m_rd;
	std::mt19937 m_gen(m_rd());

	std::uniform_int_distribution<int> dis(min, max);
	return dis(m_gen);
}

void Block::Update(float now) {
	if (now - cooldown >= 2) {
		pos_y += 38;
		cooldown = now;
	}
}