#include "block.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <random>

Block::Block(SDL_Renderer* _renderer) {
	pos_x = GetRandomNumber(225, 690);
	pos_y = 0;
	width = 100;
	height = 100;
	blockType = GetRandomNumber(1, 5); // O = 1, I = 2, Z = 3, T = 4, L = 5
	direction = GetRandomNumber(1, 4);
	switch (blockType) {
	case 1:
		texture = IMG_LoadTexture(_renderer, "O.png");
		if (!texture) {
			SDL_Log("Erreur chargement image: %s", SDL_GetError());
		}

	case 2:
		switch (direction) {
		case 1 | 3:
			texture = IMG_LoadTexture(_renderer, "I.png");
			if (!texture) {
				SDL_Log("Erreur chargement image: %s", SDL_GetError());
			}

		case 2 | 4:
			texture = IMG_LoadTexture(_renderer, "I_2.png");
			if (!texture) {
				SDL_Log("Erreur chargement image: %s", SDL_GetError());
			}
		}

	case 3:
		switch (direction) {
		case 1 | 3:
			texture = IMG_LoadTexture(_renderer, "Z.png");
			if (!texture) {
				SDL_Log("Erreur chargement image: %s", SDL_GetError());
			}

		case 2 | 4:
			texture = IMG_LoadTexture(_renderer, "Z_2.png");
			if (!texture) {
				SDL_Log("Erreur chargement image: %s", SDL_GetError());
			}
		}

	case 4:
		switch (direction) {
		case 1:
			texture = IMG_LoadTexture(_renderer, "T.png");
			if (!texture) {
				SDL_Log("Erreur chargement image: %s", SDL_GetError());
			}

		case 2:
			texture = IMG_LoadTexture(_renderer, "T_2.png");
			if (!texture) {
				SDL_Log("Erreur chargement image: %s", SDL_GetError());
			}

		case 3:
			texture = IMG_LoadTexture(_renderer, "T_3.png");
			if (!texture) {
				SDL_Log("Erreur chargement image: %s", SDL_GetError());
			}

		case 4:
			texture = IMG_LoadTexture(_renderer, "T_4.png");
			if (!texture) {
				SDL_Log("Erreur chargement image: %s", SDL_GetError());
			}
		}

	case 5:
		switch (direction) {
		case 1:
			texture = IMG_LoadTexture(_renderer, "L.png");
			if (!texture) {
				SDL_Log("Erreur chargement image: %s", SDL_GetError());
			}

		case 2:
			texture = IMG_LoadTexture(_renderer, "L_2.png");
			if (!texture) {
				SDL_Log("Erreur chargement image: %s", SDL_GetError());
			}

		case 3:
			texture = IMG_LoadTexture(_renderer, "L_3.png");
			if (!texture) {
				SDL_Log("Erreur chargement image: %s", SDL_GetError());
			}

		case 4:
			texture = IMG_LoadTexture(_renderer, "L_4.png");
			if (!texture) {
				SDL_Log("Erreur chargement image: %s", SDL_GetError());
			}
		}
	}
}

Block::~Block() {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
}

void Block::Render(SDL_Renderer* _renderer) {
	if (texture) {
		SDL_FRect rect = {pos_x, pos_y, width, height};
		SDL_RenderTexture(_renderer, texture, nullptr, &rect);
	}
}

int Block::GetRandomNumber(int min, int max) {
	std::random_device m_rd;
	std::mt19937 m_gen(m_rd());

	std::uniform_int_distribution<int> dis(min, max);
	return dis(m_gen);
}

void Block::Update(float now, float dt) {
	pos_y += 40 * dt;
}
