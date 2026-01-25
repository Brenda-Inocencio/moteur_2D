#include "character.h"
#include "block.h"
#include "menu.h"
#include <SDL3/SDL.h>

#define IDLE 1
#define WALKING_LEFT 2
#define WALKING_RIGHT 3
#define JUMPING_LEFT 4
#define JUMPING_RIGHT 5
#define FALLING_LEFT 6
#define FALLING_RIGHT 7
#define CHARACTER_RECT_WIDTH 100
#define CHARACTER_RECT_HEIGHT 145
#define HEIGHT_WIN -1100
#define MIN_POSY 610
#define MIN_POSX 225
#define MAX_POSX 698
#define JUMP_TIME 0.3f
#define CHARACTER_SPEED 100

Character::Character(std::vector<SDL_Texture*>& _textures) {
	pos_x = 465;
	pos_y = 610;
	state = CHSTATE_STATIC;
	chWidth = 45;
	chHeight = 76;
	speed = 0;
	jumpSpeed = 400;
	fallSpeed = 200;
	jumpingTime = 0;
	textures = _textures;
	texture = textures[IDLE];
}

Character::~Character() {
}

void Character::Render(SDL_Renderer* _renderer) {
	if (texture) {
		SDL_FRect rect = {pos_x, pos_y, CHARACTER_RECT_WIDTH, CHARACTER_RECT_HEIGHT};
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
					speed = CHARACTER_SPEED;
				}
				else if (event.key.key == SDLK_Q) {
					newState = CHSTATE_WALKING;
					speed = -CHARACTER_SPEED;
				}
				else if (event.key.key == SDLK_Z) {
					newState = CHSTATE_JUMPING;
					jumpingTime = now;
				}
			}
			break;
		case CHSTATE_WALKING:
			if (event.type == SDL_EVENT_KEY_UP) {
				if ((speed < 0 && event.key.key == SDLK_Q) ||
					(speed > 0 && event.key.key == SDLK_D)) {
					speed = 0;
					newState = CHSTATE_STATIC;
				}
			}
			if (event.type == SDL_EVENT_KEY_DOWN){
				if (event.key.key == SDLK_Z) {
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

void Character::Update(float dt, float now, std::vector<SDL_Event>& events, std::vector<Block*> blocks, Menu& menu) {
	State newState = processEvents(events, now);

	switch (state) {
	case CHSTATE_STATIC:
		texture = textures[IDLE];
		break;
	case CHSTATE_WALKING:
		if (speed > 0)
			texture = textures[WALKING_RIGHT];
		else 
			texture = textures[WALKING_LEFT];
		if (!isGround(blocks)) {
			newState = CHSTATE_FALLING;
		}
		break;
	case CHSTATE_JUMPING:
		if (speed >= 0)
			texture = textures[JUMPING_RIGHT];
		else
			texture = textures[JUMPING_LEFT];
		pos_y -= jumpSpeed * dt;
		if (now - jumpingTime >= JUMP_TIME) {
			newState = CHSTATE_FALLING;
			jumpingTime = now;
		}
		break;
	case CHSTATE_FALLING:
		if (speed >= 0)
			texture = textures[FALLING_RIGHT];
		if (speed < 0)
			texture = textures[FALLING_LEFT];
		pos_y += fallSpeed * dt;
		if (pos_y >= MIN_POSY) {
			pos_y = MIN_POSY;
		}
		if (isGround(blocks)) {
			newState = CHSTATE_STATIC;
			speed = 0;
		}
		break;
	}

	pos_x += dt * speed;
	if (pos_x <= MIN_POSX) {
		pos_x = MIN_POSX;
	}
	else if (pos_x >= MAX_POSX) {
		pos_x = MAX_POSX;
	}
	else if (speed != 0) {
		CollideBlock(blocks);
	}
	if (CollideBlockUp(blocks)) {
		menu.SetGameOver();
	}
	
	if (pos_y + chHeight <= HEIGHT_WIN)
		menu.SetWin();
	if (state != newState) {
		state = newState;
	}
}

void Character::CollideBlock(std::vector<Block*> blocks) {
	for (auto* bl : blocks) {
		if (speed > 0) {
			if (pos_x + chWidth >= bl->GetPosX() && pos_x + chWidth <= bl->GetRightX() &&
				bl->GetPosY() >= pos_y && bl->GetBottomY() <= pos_y + chHeight) {
				pos_x = bl->GetPosX() - chWidth;
			}
		}
		else if (speed < 0) {
			if (pos_x <= bl->GetRightX() && pos_x >= bl->GetPosX() &&
				bl->GetPosY() >= pos_y && bl->GetBottomY() <= pos_y + chHeight) {
				pos_x = bl->GetRightX() + 5;
			}
		}
	}
}

bool Character::CollideBlockUp(std::vector<Block*> blocks) {
	for (auto* bl : blocks) {
		if (((bl->GetPosX() >= pos_x && bl->GetPosX() <= pos_x + chWidth) ||
			(bl->GetRightX() >= pos_x && bl->GetRightX() <= pos_x + chWidth)) &&
			!bl->collision) {

			if (bl->GetBottomY() >= pos_y && bl->GetBottomY() <= pos_y + chHeight) {
				return true;
			}
		}
	}
	return false;
}

bool Character::isGround(std::vector<Block*> blocks) {
	for (auto* bl : blocks) {
		if (bl->collision && bl->GetPosY() >= pos_y + chHeight) {
			if ((pos_x >= bl->GetPosX() && pos_x <= bl->GetRightX()) ||
				(pos_x + chWidth <= bl->GetRightX() && pos_x + chWidth >= bl->GetPosX())) {

				pos_y = bl->GetPosY() - chHeight;
				return true;
			}
		}
		else if (pos_y == MIN_POSY) {
			return true;
		}
	}
	return false;
}
