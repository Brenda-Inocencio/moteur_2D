#include "character.h"
#include <SDL3_image/SDL_image.h>

Character::Character(SDL_Renderer* _renderer) {
	pos_x = 692;
	pos_y = 610;
	state = CHSTATE_STATIC;
	speed = 0;
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
		SDL_FRect rect = {pos_x, pos_y, 100, 145};
		SDL_RenderTexture(_renderer, texture, nullptr, &rect);
	}
}

void Character::Update(float dt, std::vector<SDL_Event>& events) {
	State newState = state;

	for (auto event = events.begin(); event != events.end(); event++)
	{
		switch (state) {
		case CHSTATE_STATIC:
			if (event->type == SDL_EVENT_KEY_DOWN) {
				if (event->key.key == SDLK_D) {
					newState = CHSTATE_WALKING;
					pos_x += 40 * dt;
					speed = 1;
				}
				else if (event->key.key == SDLK_Q) {
					newState = CHSTATE_WALKING;
					pos_x -= 40 * dt;
					speed = -1;
				}
				else if (event->key.key == SDLK_Z) {
					newState = CHSTATE_JUMPING;
					pos_y -= 40 * dt;
				}
				/*else if (event->key.key == SDLK_S) {
					newState = CHSTATE_CARRYING;
				}*/
				/*else if () {
					newState = CHSTATE_FALLING;
				}*/
			}
			break;
		case CHSTATE_WALKING:
			if ((speed < 0 && event->key.key != SDLK_Q) || (speed > 0 && event->key.key != SDLK_D)) {
				speed = 0;
				newState = CHSTATE_STATIC;
			}
			else if (event->key.key == SDLK_Z) {
				newState = CHSTATE_JUMPING;
				pos_y -= 40 * dt;
			}
			break;
		case CHSTATE_JUMPING:
			break;
		case CHSTATE_FALLING:
			break;
		case CHSTATE_CARRYING:
			break;
		}
	}
	if (state != newState) {
		state = newState;
	}
}

// TODO: finir les deplacements et la table d etat (enum et switch)