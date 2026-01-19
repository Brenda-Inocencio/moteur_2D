#include "character.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

Character::Character(SDL_Renderer* _renderer) {
	pos_x = 692;
	pos_y = 610;
	state = CHSTATE_STATIC;
	width = 100;
	height = 145;
	speed = 0;
	jumpingTime = 0;
	isGround = false;
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

Character::State Character::processEvents(std::vector<SDL_Event>& events, float now)
{
	State newState = state;
	for (auto& event : events)
	{
		switch (state) {
		case CHSTATE_STATIC:
			if (event.type == SDL_EVENT_KEY_DOWN) {
				if (event.key.key == SDLK_D) {
					newState = CHSTATE_WALKING;
					speed = 100;
				}
				else if (event.key.key == SDLK_Q) {
					newState = CHSTATE_WALKING;
					speed = -100;
				}
				else if (event.key.key == SDLK_Z) {
					newState = CHSTATE_JUMPING;
					jumpingTime = now;
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
					jumpingTime = now;
				}
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
	return newState;
}

void Character::Update(float dt, std::vector<SDL_Event>& events, float now) {
	State newState = processEvents(events, now);

	switch (state) {
	case CHSTATE_STATIC:
		break;
	case CHSTATE_WALKING:
		break;
	case CHSTATE_JUMPING:
		pos_y -= 400 * dt;
		isGround = false;
		if (now - jumpingTime >= 0.25f) {
			newState = CHSTATE_FALLING;
			jumpingTime = now;
		}
		break;
	case CHSTATE_FALLING:
		if (pos_y >= 610 || isGround)
		{
			newState = CHSTATE_STATIC;
			speed = 0;
		}
		break;
	case CHSTATE_CARRYING:
		break;
	}

	pos_x += dt * speed;
	if (pos_x <= 225) {
		pos_x = 225;
	}
	if (pos_x >= 698) {
		pos_x = 698;
	}
	if (state != CHSTATE_JUMPING)
	{
		pos_y += 200 * dt;
		if (pos_y >= 610) {
			pos_y = 610;
		}
	}
	if (state != newState) {
		state = newState;
		std::cout << "state : " << newState << std::endl;
	}
}