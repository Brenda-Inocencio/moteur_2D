#pragma once

struct SDL_Renderer;
struct SDL_Texture;

class Block {
	float cooldown;
	float pos_x;
	float pos_y;
	int width;
	int height;
	int blockType;
	int direction;
	SDL_Texture* texture;
public:
	Block(SDL_Texture* blockTexture);
	~Block();
	void Render(SDL_Renderer* renderer);
	int GetRandomNumber(int min, int max); // TODO: move in appropriate class
	void Update(float now);
};