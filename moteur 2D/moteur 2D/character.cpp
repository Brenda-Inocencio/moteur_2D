#include "character.h"
#include <SDL3_image/SDL_image.h>

Character::Character(SDL_Renderer* _renderer) {
	pos_x = 692;
	pos_y = 610;
	state = CHSTATE_STATIC;
	width = 100;
	height = 145;
	speed = 0;
	collision = false;
	texture = IMG_LoadTexture(_renderer, "character_static.png");
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
		SDL_FRect rect = {pos_x, pos_y, width, height};
		SDL_RenderTexture(_renderer, texture, nullptr, &rect);
	}
}

void Character::Update(float dt, std::vector<SDL_Event>& events) {
	State newState = state;

	for (auto& event : events)
	{
		switch (state) {
		case CHSTATE_STATIC:
			if (event.type == SDL_EVENT_KEY_DOWN) {
				if (event.key.key == SDLK_D) {
					newState = CHSTATE_WALKING;
					speed = 40;
				}
				else if (event.key.key == SDLK_Q) {
					newState = CHSTATE_WALKING;
					speed = -40;
				}
				else if (event.key.key == SDLK_Z) {
					newState = CHSTATE_JUMPING;
				}
				/*else if (event.key.key == SDLK_S) {
					newState = CHSTATE_CARRYING;
				}*/
				/*else if () {
					newState = CHSTATE_FALLING;
				}*/
			}
			break;
		case CHSTATE_WALKING:
			if (event.type == SDL_EVENT_KEY_UP) {
				if ((speed < 0 && event.key.key == SDLK_Q) || (speed > 0 && event.key.key == SDLK_D)) {
					speed = 0;
					newState = CHSTATE_STATIC;
				}
				else if (event.key.key == SDLK_Z) {
					newState = CHSTATE_JUMPING;
				}
			}
			break;
		case CHSTATE_JUMPING:
			newState = CHSTATE_STATIC;
			break;
		case CHSTATE_FALLING:
			break;
		case CHSTATE_CARRYING:
			break;
		}
	}
	// Character update input independent
	if (state == CHSTATE_WALKING)
		pos_x += dt * speed;

	if (state != newState) {
		state = newState;
	}
}
// TODO: finir les deplacements et la table d etat (enum et switch)