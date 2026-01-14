#pragma once

struct SDL_Texture;
struct SDL_Renderer;

class Character {
	float pos_x;
	float pos_y;

public:
	SDL_Texture* texture;
	~Character();
	Character(SDL_Renderer* _renderer);
	void Render(SDL_Renderer* _renderer);
	void Moving(float dt, bool isLeft, bool isRight);
};

