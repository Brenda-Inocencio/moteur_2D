#pragma once
#include <SDL3/SDL.h>
#include <vector>

struct SDL_Texture;
struct SDL_Renderer;
union SDL_EVENT;

class Character {
	float pos_x;
	float pos_y;
	int speed;
	enum State {
		CHSTATE_STATIC,
		CHSTATE_WALKING,
		CHSTATE_JUMPING,
		CHSTATE_FALLING,
		CHSTATE_CARRYING
	} state;
public:
	SDL_Texture* texture;
	~Character();
	Character(SDL_Renderer* _renderer);
	void Render(SDL_Renderer* _renderer);
	void Update(float dt, std::vector<SDL_Event>& events);
};