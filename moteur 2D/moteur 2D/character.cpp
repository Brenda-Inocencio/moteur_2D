#include "character.h"
#include "block.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

Character::Character(SDL_Renderer* _renderer) {
	pos_x = 692;
	pos_y = 610;
	state = CHSTATE_STATIC;
	width = 50;
	height = 70;
	speed = 0;
	jumpingTime = 0;
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
		SDL_FRect rect = {pos_x, pos_y, 100, 145};
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
				if ((speed < 0 && event.key.key == SDLK_Q) || 
					(speed > 0 && event.key.key == SDLK_D)) {
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

void Character::Update(float dt, std::vector<SDL_Event>& events, float now, std::vector<Block*> blocks) {
	State newState = processEvents(events, now);

	switch (state) {
	case CHSTATE_STATIC:
		break;
	case CHSTATE_WALKING:
		break;
	case CHSTATE_JUMPING:
		pos_y -= 400 * dt;
		if (now - jumpingTime >= 0.3f) {
			newState = CHSTATE_FALLING;
			jumpingTime = now;
		}
		break;
	case CHSTATE_FALLING:
		pos_y += 200 * dt;
		if (pos_y >= 610) {
			pos_y = 610;
		}
		if (pos_y == 610 || isGround(blocks)) {
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
	else if (pos_x >= 698) {
		pos_x = 698;
	}
	else if (speed != 0) {
		CollideBlock(blocks);
	}
/*	else if (speed > 0) {
		CollideBlockRight(blocks); // enumère les blocks, réajuste la position en cas de collision
	}
	else if(speed<0) {
		CollideBlockLeft(blocks);
	}*/
	
	if (state != newState) {
		state = newState;
		std::cout << "state : " << newState << std::endl;
	}
}
void Character::CollideBlockLeft(std::vector<Block*> blocks) {
	for (auto* bl : blocks) {
		if (pos_x <= bl->GetRightX() && pos_x >= bl->GetPosX() &&
			bl->GetPosY() >= pos_y && bl->GetBottomY() <= pos_y + height) {
			pos_x = bl->GetRightX();
		}
	}
}

void Character::CollideBlockRight(std::vector<Block*> blocks) {
	for (auto* bl : blocks) {
		if (pos_x + 100 >= bl->GetPosX() && pos_x + 100 >= bl->GetRightX() &&
			bl->GetPosY() >= pos_y && bl->GetBottomY() <= pos_y + height) {
			pos_x = bl->GetPosX() - width;
		}
	}
}

void Character::CollideBlock(std::vector<Block*> blocks) {
	for (auto* bl : blocks) {
		if (speed > 0) {
			if (pos_x + width >= bl->GetPosX() && pos_x + width <= bl->GetRightX() &&
				bl->GetPosY() >= pos_y && bl->GetBottomY() <= pos_y + height) {
				pos_x = bl->GetPosX() - width;
			}
		}
		else if (speed < 0) {
			if (pos_x <= bl->GetRightX() && pos_x >= bl->GetPosX() &&
				bl->GetPosY() >= pos_y && bl->GetBottomY() <= pos_y + height) {
				pos_x = bl->GetRightX() + 5;
			}
		}
	}
}

bool Character::isGround(std::vector<Block*> blocks) {
	for (auto* bl : blocks) {
		if (bl->collision && bl->GetPosY() <= pos_y + height && 
			((pos_x >= bl->GetPosX() && pos_x <= bl->GetRightX()) ||
				(pos_x + width <= bl->GetRightX() && pos_x + width >= bl->GetPosX()))) {
			pos_y = bl->GetPosY() - height;
			return true;
		}
	}
	return false;
}
