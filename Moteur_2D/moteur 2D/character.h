#pragma once

struct SDL_Texture;
struct SDL_Renderer;

class Character {
public:
	SDL_Texture* texture;
	~Character();
	Character(SDL_Renderer* _renderer);
	void Render(SDL_Renderer* _renderer);
};

